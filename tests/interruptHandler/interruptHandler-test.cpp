#include <gtest/gtest.h>

#include "interruptHandler-test.h"

TEST(InterruptHandlerTest, RequestingInterrupts)
{
	rose_core::InterruptHandler ih;

	// Test if initial value of IF is correct
	EXPECT_EQ(ih.readIF(), 0xE1);

	// Make sure first 3 bits can't be overwritten
	ih.setIF(0xFF);
	EXPECT_EQ(ih.readIF(), 0xFF);
	ih.setIF(0x00);
	EXPECT_EQ(ih.readIF(), 0xE0);

	// Test if each interrupt request enabled the right bit
	ih.requestInterrupt(rose_core::VBLANK);
	EXPECT_EQ(ih.readIF(), 0xE1);
	ih.requestInterrupt(rose_core::STAT);
	EXPECT_EQ(ih.readIF(), 0xE3);
	ih.requestInterrupt(rose_core::TIMER);
	EXPECT_EQ(ih.readIF(), 0xE7);
	ih.requestInterrupt(rose_core::SERIAL);
	EXPECT_EQ(ih.readIF(), 0xEF);
	ih.requestInterrupt(rose_core::JOYPAD);
	EXPECT_EQ(ih.readIF(), 0xFF);

	// Making sure that requesting an interrupt again won't change it.
	ih.requestInterrupt(rose_core::VBLANK);
	ih.requestInterrupt(rose_core::STAT);
	ih.requestInterrupt(rose_core::TIMER);
	ih.requestInterrupt(rose_core::SERIAL);
	ih.requestInterrupt(rose_core::JOYPAD);
	EXPECT_EQ(ih.readIF(), 0xFF);

	// Resetting specific flags of IF
	ih.resetIFBit(rose_core::VBLANK);
	EXPECT_EQ(ih.readIF(), 0xFE);
	ih.resetIFBit(rose_core::STAT);
	EXPECT_EQ(ih.readIF(), 0xFC);
	ih.resetIFBit(rose_core::TIMER);
	EXPECT_EQ(ih.readIF(), 0xF8);
	ih.resetIFBit(rose_core::SERIAL);
	EXPECT_EQ(ih.readIF(), 0xF0);
	ih.resetIFBit(rose_core::JOYPAD);
	EXPECT_EQ(ih.readIF(), 0xE0);

}

TEST(InterruptHandlerTest, SettingIME)
{
	rose_core::InterruptHandler ih;

	// Test if initial value of IME flag is correct
	EXPECT_EQ(ih.readIME(), false);

	// Checking if setting IME directly works
	ih.setIME(true);
	EXPECT_EQ(ih.readIME(), true);
	ih.setIME(false);
	EXPECT_EQ(ih.readIME(), false);

	// Testing delay of EI
	ih.setIMENextCycle();
	EXPECT_EQ(ih.readIME(), false);
	ih.setIMEIfNextCycle();
	EXPECT_EQ(ih.readIME(), true);
	ih.setIME(false);

	// Testing cancelling the delay of EI
	ih.setIMENextCycle();
	ih.setIME(false);
	ih.setIMEIfNextCycle();
	EXPECT_EQ(ih.readIME(), false);
}

TEST(InterruptHandlerTest, SettingIE)
{
	rose_core::InterruptHandler ih;

	// Test if initial value of IE is correct
	EXPECT_EQ(ih.readIE(), 0x00);

	// All bits are writeable (surprisingly)
	ih.setIE(0xFF);
	EXPECT_EQ(ih.readIE(), 0xFF);
}