#include <gtest/gtest.h>

#include "timer-test.h"

TEST(TimerTest, DividerRegister)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);

	// Testing initial value of the divider register.
	EXPECT_EQ(timer.readDIV(), 0xAB);

	// Test writing to DIV resets it to 0
	timer.resetDIV();
	EXPECT_EQ(timer.readDIV(), 0x00);

	// Test if it increments correctly
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++) timer.tick();
		EXPECT_EQ(timer.readDIV(), (i+1) % 256);
	}

	// TODO: Test stop mode
}

TEST(TimerTest, TimerCounter)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);

	// Testing initial value of the timer counter.
	EXPECT_EQ(timer.readTIMA(), 0x00);



	// Test if it increments when TAC is turned off
	for (int i = 0; i < 1024; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x00);



	// Test if it increments correctly based on TAC clock choice
	timer.resetDIV();
	timer.setTIMA(0x00);
	timer.setTAC(0xFC); // enable the clock, mode 00
	for (int i = 0; i < 1024; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x01);

	timer.resetDIV();
	timer.setTIMA(0x00);
	timer.setTAC(0xFD); // enable the clock, mode 01
	for (int i = 0; i < 1024; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x40);

	timer.resetDIV();
	timer.setTIMA(0x00);
	timer.setTAC(0xFE); // enable the clock, mode 10
	for (int i = 0; i < 1024; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x10);

	timer.resetDIV();
	timer.setTIMA(0x00);
	timer.setTAC(0xFF); // enable the clock, mode 11
	for (int i = 0; i < 1024; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x04);



	// Check if it resets correctly after overflowing
	timer.resetDIV();
	timer.setTIMA(0xFF);
	timer.setTAC(0xFD);
	timer.setTMA(0x80);
	for (int i = 0; i < 16; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x00); 
	for (int i = 0; i < 4; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x80);
	for (int i = 0; i < 12; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x81);

	// Check if it requests an interrupt after overflowing
	ih.resetIFBit(rose_core::TIMER);
	timer.setTIMA(0xFF);
	timer.setTAC(0xFD);
	timer.setTMA(0x80);
	for (int i = 0; i < 16; i++) timer.tick();
	EXPECT_EQ(ih.readIF(), 0xE1);
	for (int i = 0; i < 4; i++) timer.tick();
	EXPECT_EQ(ih.readIF(), 0xE5);

}

TEST(TimerTest, TimerModulo)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);

	// Testing initial value of the timer modulo.
	EXPECT_EQ(timer.readTMA(), 0x00);
}

TEST(TimerTest, TimerControl)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);

	// Testing initial value of the timer control.
	EXPECT_EQ(timer.readTAC(), 0xF8);
}

/*
Changing which bit of the system counter is selected (by changing the “Clock select” bits of TAC) 
from a bit currently set to another that is currently unset, will send a “Timer tick” pulse. 
(For example: if the system counter is equal to $3FF0 and TAC to $FC, writing $05 or $06 to TAC 
will instantly send a “Timer tick”, but $04 or $07 won’t.)
https://gbdev.io/pandocs/Timer_Obscure_Behaviour.html
*/
TEST(TimerTest, ChangingClockSelect)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);

	// Should send a "timer tick"
	timer.resetDIV();
	timer.setTAC(0xFC);
	for (int i = 0; i < 0x3FF0; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x0F);
	timer.setTAC(0x05);
	EXPECT_EQ(timer.readTIMA(), 0x10);

	// Shouldn't send a "timer tick"
	timer.resetDIV();
	timer.setTIMA(0x00);
	timer.setTAC(0xFC);
	for (int i = 0; i < 0x3FF0; i++) timer.tick();
	EXPECT_EQ(timer.readTIMA(), 0x0F);
	timer.setTAC(0x04);
	EXPECT_EQ(timer.readTIMA(), 0x0F);
}


/*
On monochrome consoles, disabling the timer if the currently selected bit is set, will send 
a “Timer tick” once. This does not happen on Color models.
https://gbdev.io/pandocs/Timer_Obscure_Behaviour.html
*/
TEST(TimerTest, DisablingTimer)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);

	// Should send a "timer tick"
	timer.setTAC(0xFC);
	EXPECT_EQ(timer.readTIMA(), 0x00);
	timer.setTAC(0xF8);
	EXPECT_EQ(timer.readTIMA(), 0x01);

	// Shouldn't send a "timer tick"
	timer.setTAC(0xFD);
	timer.setTIMA(0x00);
	EXPECT_EQ(timer.readTIMA(), 0x00);
	timer.setTAC(0xF8);
	EXPECT_EQ(timer.readTIMA(), 0x00);
}

/*
M-cycle				A	B	
SYS	    AC	B0	B4	B8	BC	C0	34
TIMA	FE	FF	FF	00	23	24	24
TMA	    23	23	23	23	23	23	23
IF	    E0	E0	E0	E0	E4	E4	E4

Writing to TIMA during cycle A acts as if the overflow didn’t happen! TMA will not be copied to TIMA (the value written will therefore stay), and bit 2 of IF will not be set. Writing to DIV, TAC, or other registers won’t prevent the IF flag from being set or TIMA from being reloaded.
Writing to TIMA during cycle B will be ignored; TIMA will be equal to TMA at the end of the cycle anyway.
Writing to TMA during cycle B will have the same value copied to TIMA as well, on the same cycle.
https://gbdev.io/pandocs/Timer_Obscure_Behaviour.html
*/

TEST(TimerTest, TimerOverflowUnexpectedBehaviour)
{
	// Regular Behaviour
	{
		rose_core::InterruptHandler ih;
		rose_core::Timer timer(ih);

		for (int i = 0; i < 0xAC; i++) timer.tick();
		timer.setTAC(0xFD);
		timer.setTIMA(0xFE);
		timer.setTMA(0x23);
		ih.resetIFBit(rose_core::VBLANK);

		for (int i = 0; i < 16; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0xFF);
		
		for (int i = 0; i < 4; i++) timer.tick();    // "Cycle A"
		EXPECT_EQ(timer.readTIMA(), 0x00);
		EXPECT_EQ(ih.readIF(), 0xE0);
		
		for (int i = 0; i < 4; i++) timer.tick();    // "Cycle B"
		EXPECT_EQ(timer.readTIMA(), 0x23);
		EXPECT_EQ(ih.readIF(), 0xE4);
		
		for (int i = 0; i < 12; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0x24);
	}

	// Writing to TIMA on "Cycle A"
	{
		rose_core::InterruptHandler ih;
		rose_core::Timer timer(ih);

		for (int i = 0; i < 0xAC; i++) timer.tick();
		timer.setTAC(0xFD);
		timer.setTIMA(0xFE);
		timer.setTMA(0x23);
		ih.resetIFBit(rose_core::VBLANK);

		for (int i = 0; i < 16; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0xFF);
						
		for (int i = 0; i < 4; i++) timer.tick();	// "Cycle A"
		EXPECT_EQ(timer.readTIMA(), 0x00);
		EXPECT_EQ(ih.readIF(), 0xE0);
		timer.setTIMA(0x00);

		for (int i = 0; i < 4; i++) timer.tick();    // "Cycle B"
		EXPECT_EQ(timer.readTIMA(), 0x00);
		EXPECT_EQ(ih.readIF(), 0xE0);

		for (int i = 0; i < 12; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0x01);
	}

	// Writing to TIMA on "Cycle B"
	{
		rose_core::InterruptHandler ih;
		rose_core::Timer timer(ih);

		for (int i = 0; i < 0xAC; i++) timer.tick();
		timer.setTAC(0xFD);
		timer.setTIMA(0xFE);
		timer.setTMA(0x23);
		ih.resetIFBit(rose_core::VBLANK);

		for (int i = 0; i < 16; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0xFF);

		for (int i = 0; i < 4; i++) timer.tick();    // "Cycle A"
		EXPECT_EQ(timer.readTIMA(), 0x00);
		EXPECT_EQ(ih.readIF(), 0xE0);

		for (int i = 0; i < 3; i++) timer.tick();    // "Cycle B"
		timer.setTIMA(0x00);
		timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0x23);
		EXPECT_EQ(ih.readIF(), 0xE4);

		for (int i = 0; i < 12; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0x24);
	}

	// Writing to TMA on "Cycle B"
	{
		rose_core::InterruptHandler ih;
		rose_core::Timer timer(ih);

		for (int i = 0; i < 0xAC; i++) timer.tick();
		timer.setTAC(0xFD);
		timer.setTIMA(0xFE);
		timer.setTMA(0x23);
		ih.resetIFBit(rose_core::VBLANK);

		for (int i = 0; i < 16; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0xFF);

		for (int i = 0; i < 4; i++) timer.tick();    // "Cycle A"
		EXPECT_EQ(timer.readTIMA(), 0x00);
		EXPECT_EQ(ih.readIF(), 0xE0);

		for (int i = 0; i < 3; i++) timer.tick();    // "Cycle B"
		timer.setTMA(0x87);
		timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0x87);
		EXPECT_EQ(ih.readIF(), 0xE4);

		for (int i = 0; i < 12; i++) timer.tick();
		EXPECT_EQ(timer.readTIMA(), 0x88);
	}
}