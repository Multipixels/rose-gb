#include <gtest/gtest.h>

#include "blargg-test.h"

TEST(Blargg, CpuInstr)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/blargg/cpu_instrs/01-special.gb", 2000000 }, // passed
		// { "../resources/blargg/cpu_instrs/02-interrupts.gb", 1000000}, // passed
		// { "../resources/blargg/cpu_instrs/03-op sp,hl.gb", 2000000 }, // passed
		// { "../resources/blargg/cpu_instrs/04-op r,imm.gb", 2000000 }, // passed
		// { "../resources/blargg/cpu_instrs/05-op rp.gb", 2000000}, // passed
		// { "../resources/blargg/cpu_instrs/06-ld r,r.gb", 1000000}, // passed
		// { "../resources/blargg/cpu_instrs/07-jr,jp,call,ret,rst.gb", 1000000 }, // passed
		// { "../resources/blargg/cpu_instrs/08-misc instrs.gb", 1000000 },// passed
		// { "../resources/blargg/cpu_instrs/09-op r,r.gb", 10000000 }, // passed
		// { "../resources/blargg/cpu_instrs/10-bit ops.gb", 7500000 }, // passed
		// { "../resources/blargg/cpu_instrs/11-op a,(hl).gb", 7500000 }, // passed
		// { "../resources/blargg/cpu_instrs.gb", 20000000 }, // TODO: unimplemented stop
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
				std::cout << console;
			}

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		std::cout << std::endl;
	}
}


TEST(Blargg, InstrTiming)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/blargg/instr_timing.gb", 500000 }, // passed
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
				std::cout << console;
			}

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		std::cout << std::endl;
	}
}


TEST(Blargg, MemTiming)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/blargg/mem_timing/01-read_timing.gb", 400000 }, // passed
		// { "../resources/blargg/mem_timing/02-write_timing.gb", 400000 }, // passed
		// { "../resources/blargg/mem_timing/03-modify_timing.gb", 400000 }, // passed
		// { "../resources/blargg/mem_timing.gb", 1000000 }, // passed
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
				std::cout << console;
			}

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		std::cout << std::endl;
	}
}


TEST(Blargg, MemTiming2)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases{
		// { "../resources/blargg/mem_timing-2/01-read_timing.gb", 1000000 }, // passed
		// { "../resources/blargg/mem_timing-2/02-write_timing.gb", 1000000 }, // passed
		// { "../resources/blargg/mem_timing-2/03-modify_timing.gb", 1000000 }, // passed
		// { "../resources/blargg/mem_timing-2.gb", 1500000 }, // passed
	};

	for (TestCase test : testCases)
	{
		rose_core::Rose rose;
		rose.loadGame(test.romFile);

		int instructionsRan = 0;
		bool finished = false;
		while (instructionsRan < test.maxInstructions)
		{
			if (!finished && rose.tempReadConsole(0xA000) != 0x80)
			{
				rose_core::u8 console = rose.tempReadConsole(0xA004);
				int i = 0;
				while (console != 0x00)
				{
					finished = true;
					std::cout << console;
					i++;
					console = rose.tempReadConsole(0xA004 + i);
				}
			}

			ASSERT_NO_FATAL_FAILURE(rose.stepForward());
			instructionsRan++;
		}

		std::cout << std::endl;
	}
}