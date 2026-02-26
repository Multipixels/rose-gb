#include <gtest/gtest.h>

#include "mooneye-test.h"

TEST(Mooneye, DISABLED_AcceptanceMiscell)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/mooneye/acceptance/add_sp_e_timing.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/boot_div-dmgABCmgb.gb",		 500000 }, // 396
		// { "../resources/mooneye/acceptance/boot_hwio-dmgABCmgb.gb",		 500000 }, // 396
		// { "../resources/mooneye/acceptance/boot_regs-dmgABC.gb",			 500000 }, // 396
		// { "../resources/mooneye/acceptance/call_cc_timing.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/call_cc_timing2.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/call_timing.gb",				1000000 }, // 0
		// { "../resources/mooneye/acceptance/call_timing2.gb",				1000000 }, // 0
		{ "../resources/mooneye/acceptance/div_timing.gb",						 -1 }, // Passed
		// { "../resources/mooneye/acceptance/di_timing-GS.gb",				 500000 }, // 110
		{ "../resources/mooneye/acceptance/ei_sequence.gb",						 -1 }, // Passed
		{ "../resources/mooneye/acceptance/ei_timing.gb",						 -1 }, // Passed
		// { "../resources/mooneye/acceptance/halt_ime0_ei.gb",				1000000 }, // 0
		// { "../resources/mooneye/acceptance/halt_ime0_nointr_timing.gb",	1000000 }, // 0
		{ "../resources/mooneye/acceptance/halt_ime1_timing.gb",				 -1 }, // Passed
		// { "../resources/mooneye/acceptance/halt_ime1_timing2-GS.gb",		1000000 }, // 0
		{ "../resources/mooneye/acceptance/if_ie_registers.gb",					 -1 }, // Passed
		// { "../resources/mooneye/acceptance/intr_timing.gb",				 500000 }, // 396
		// { "../resources/mooneye/acceptance/jp_cc_timing.gb",				1000000 }, // 0
		// { "../resources/mooneye/acceptance/jp_timing.gb",				1000000 }, // 0
		// { "../resources/mooneye/acceptance/ld_hl_sp_e_timing.gb",		1000000 }, // 0
		// { "../resources/mooneye/acceptance/oam_dma_restart.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/oam_dma_start.gb",			 500000 }, // 323
		// { "../resources/mooneye/acceptance/oam_dma_timing.gb",			1000000 }, // 0
		{ "../resources/mooneye/acceptance/pop_timing.gb",						 -1 }, // Passed
		// { "../resources/mooneye/acceptance/push_timing.gb",				1000000 }, // 0
		{ "../resources/mooneye/acceptance/rapid_di_ei.gb",						 -1 }, // Passed
		// { "../resources/mooneye/acceptance/reti_intr_timing.gb",			 500000 }, // 396
		// { "../resources/mooneye/acceptance/reti_timing.gb",				 500000 }, // 420
		// { "../resources/mooneye/acceptance/ret_cc_timing.gb",			 500000 }, // 418
		// { "../resources/mooneye/acceptance/ret_timing.gb",				 500000 }, // 420
		// { "../resources/mooneye/acceptance/rst_timing.gb",				1000000 }, // 0
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 1000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
				break;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}

TEST(Mooneye, DISABLED_AcceptanceBits)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		{ "../resources/mooneye/acceptance/bits/mem_oam.gb",				 -1 }, // passed
		{ "../resources/mooneye/acceptance/bits/reg_f.gb",					 -1 }, // passed
		// { "../resources/mooneye/acceptance/bits/unused_hwio-GS.gb",	1000000 }, // failed
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 1000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
				break;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}


TEST(Mooneye, DISABLED_AcceptanceInstr)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		{ "../resources/mooneye/acceptance/instr/daa.gb", -1 }, // passed
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 1000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
				break;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}

TEST(Mooneye, DISABLED_AcceptanceInterrupts)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/mooneye/acceptance/interrupts/ie_push.gb", 1000000 }, // failed
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 1000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
				break;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}



TEST(Mooneye, DISABLED_AcceptanceOamDma)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/mooneye/acceptance/oam_dma/basic.gb",		1000000 }, // failed
		{ "../resources/mooneye/acceptance/oam_dma/reg_read.gb",			 -1 }, // passed
		// { "../resources/mooneye/acceptance/oam_dma/sources-GS.gb",	1000000 }, // failed
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 1000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
				break;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}



TEST(Mooneye, AcceptancePPU)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/mooneye/acceptance/ppu/hblank_ly_scx_timing-GS.gb",		100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/intr_1_2_timing-GS.gb",			100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/intr_2_0_timing.gb",				100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/intr_2_mode0_timing.gb",			100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/intr_2_mode0_timing_sprites.gb",	100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/intr_2_mode3_timing.gb",			100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/intr_2_oam_ok_timing.gb",			100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/lcdon_timing-GS.gb",					100000000 }, // failed
		// { "../resources/mooneye/acceptance/ppu/lcdon_write_timing-GS.gb",		100000000 }, // failed
		{ "../resources/mooneye/acceptance/ppu/stat_irq_blocking.gb",					   -1 }, // passes
		{ "../resources/mooneye/acceptance/ppu/stat_lyc_onoff.gb",						   -1 }, // passes
		//{ "../resources/mooneye/acceptance/ppu/vblank_stat_intr-GS.gb",			1000000 }, // infinite loop???
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 10000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
				break;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}


TEST(Mooneye, DISABLED_AcceptanceSerial)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/mooneye/acceptance/serial/boot_sclk_align-dmgABCmgb.gb",	1000000 }, // failed
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 1000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}


TEST(Mooneye, DISABLED_AcceptanceTimer)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		{ "../resources/mooneye/acceptance/timer/div_write.gb",						 -1 }, // passed
		// { "../resources/mooneye/acceptance/timer/rapid_toggle.gb",			1000000 }, // failed
		{ "../resources/mooneye/acceptance/timer/tim00.gb",							 -1 }, // passed
		// { "../resources/mooneye/acceptance/timer/tim00_div_trigger.gb",		1000000 }, // failed
		{ "../resources/mooneye/acceptance/timer/tim01.gb",							 -1 }, // passed
		// { "../resources/mooneye/acceptance/timer/tim01_div_trigger.gb",		1000000 }, // failed
		// { "../resources/mooneye/acceptance/timer/tim10.gb",					1000000 }, // failed
		// { "../resources/mooneye/acceptance/timer/tim10_div_trigger.gb",		1000000 }, // failed
		{ "../resources/mooneye/acceptance/timer/tim11.gb",							 -1 }, // passed
		// { "../resources/mooneye/acceptance/timer/tim11_div_trigger.gb",		1000000 }, // failed
		// { "../resources/mooneye/acceptance/timer/tima_reload.gb",			1000000 }, // failed
		// { "../resources/mooneye/acceptance/timer/tima_write_reloading.gb",	1000000 }, // failed
		// { "../resources/mooneye/acceptance/timer/tma_write_reloading.gb",	1000000 }, // failed
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.readConsole();

		int outputCounter = 0;
		while (instructionsRan < 1000000)
		{
			if (rose.readConsole() != console)
			{
				console = rose.readConsole();
				EXPECT_EQ(mooneyeOutputExpected[outputCounter], console)
					<< "Failed: " << test.romFile;
				outputCounter++;
				break;
			}

			if (outputCounter == 6) break;

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		if (instructionsRan >= 1000000) ADD_FAILURE() << "Failed (timeout): " << test.romFile;
	}
}