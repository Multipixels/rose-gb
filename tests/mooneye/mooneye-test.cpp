#include <gtest/gtest.h>

#include "mooneye-test.h"

TEST(Mooneye, AcceptanceMiscell)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/mooneye/acceptance/add_sp_e_timing.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/boot_div-dmgABCmgb.gb",		500000 }, // 396
		// { "../resources/mooneye/acceptance/boot_hwio-dmgABCmgb.gb",		500000 }, // 396
		// { "../resources/mooneye/acceptance/boot_regs-dmgABC.gb",			500000 }, // 396
		// { "../resources/mooneye/acceptance/call_cc_timing.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/call_cc_timing2.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/call_timing.gb",				1000000 }, // 0
		// { "../resources/mooneye/acceptance/call_timing2.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/div_timing.gb",				1000000 }, // Passed
		// { "../resources/mooneye/acceptance/di_timing-GS.gb",				500000 }, // 110
		// { "../resources/mooneye/acceptance/ei_sequence.gb",				1000000 }, // Passed
		// { "../resources/mooneye/acceptance/ei_timing.gb",				1000000 }, // Passed
		// { "../resources/mooneye/acceptance/halt_ime0_ei.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/halt_ime0_nointr_timing.gb", 1000000 }, // 0
		// { "../resources/mooneye/acceptance/halt_ime1_timing.gb",		1000000 }, // Passed
		// { "../resources/mooneye/acceptance/halt_ime1_timing2-GS.gb",	1000000 }, // 0
		// { "../resources/mooneye/acceptance/if_ie_registers.gb",			1000000 }, // Passed
		// { "../resources/mooneye/acceptance/intr_timing.gb",				500000 }, // 396
		// { "../resources/mooneye/acceptance/jp_cc_timing.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/jp_timing.gb",				1000000 }, // 0
		// { "../resources/mooneye/acceptance/ld_hl_sp_e_timing.gb",		1000000 }, // 0
		// { "../resources/mooneye/acceptance/oam_dma_restart.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/oam_dma_start.gb",			500000 }, // 323
		// { "../resources/mooneye/acceptance/oam_dma_timing.gb",			1000000 }, // 0
		// { "../resources/mooneye/acceptance/pop_timing.gb",				1000000 }, // Passed
		// { "../resources/mooneye/acceptance/push_timing.gb",				1000000 }, // 0
		// { "../resources/mooneye/acceptance/rapid_di_ei.gb",				1000000 }, // Passed
		// { "../resources/mooneye/acceptance/reti_intr_timing.gb",			500000 }, // 396
		// { "../resources/mooneye/acceptance/reti_timing.gb",				500000 }, // 420
		// { "../resources/mooneye/acceptance/ret_cc_timing.gb",			500000 }, // 418
		// { "../resources/mooneye/acceptance/ret_timing.gb",				500000 }, // 420
		// { "../resources/mooneye/acceptance/rst_timing.gb",				1000000 }, // 0
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		rose_core::u8 console = rose.tempReadConsole();
		while (instructionsRan < test.maxInstructions)
		{
			if (rose.tempReadConsole() != console)
			{
				console = rose.tempReadConsole();
				std::cout << (int)console << " ";
			}

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}
		
		auto reg = rose.viewCPU().viewRegisters();
		EXPECT_EQ(reg.b + reg.c + reg.d + reg.e + reg.h + reg.l, 84)
			<< "Failed: " << test.romFile;
		std::cout << std::endl;
	}
}