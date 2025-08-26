#include <gtest/gtest.h>

#include "../mmu/mmu-test.h"
#include "cpu-test.h"

#include "rose.h"

std::string test_1 = "../resources/blargg/cpu_instrs/01-special.gb";

TEST(CPUTest, TestingTests)
{
	rose_core::MMU mmu;
	rose_core::CPU cpu(mmu);

	ASSERT_NO_FATAL_FAILURE(loadTestCartridge(test_1, mmu));

	EXPECT_TRUE(true);
}

TEST(CPUTest, LoadConstsIntoRegisters)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases {
		{ { 0x01, 0xAB, 0xCD }, BC, 0xCDAB },
		{ { 0x11, 0xAB, 0xCD }, DE, 0xCDAB },
		{ { 0x21, 0xAB, 0xCD }, HL, 0xCDAB },
		{ { 0x31, 0xAB, 0xCD }, SP, 0xCDAB },

		{ { 0x06, 0xAB }, B, 0xAB },
		{ { 0x0E, 0xAB }, C, 0xAB },
		{ { 0x16, 0xAB }, D, 0xAB },
		{ { 0x1E, 0xAB }, E, 0xAB },
		{ { 0x26, 0xAB }, H, 0xAB },
		{ { 0x2E, 0xAB }, L, 0xAB },
		{ { 0x3E, 0xAB }, A, 0xAB },
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}

}

TEST(CPUTest, LoadRegistersIntoRegisters)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x01, 0xAB, 0xCD, 0x40 }, B, 0xCD },
		{ { 0x01, 0xAB, 0xCD, 0x48 }, C, 0xCD },
		{ { 0x3E, 0xAB, 0x4F }, C, 0xAB },
		{ { 0x01, 0xAB, 0xCD, 0x78 }, A, 0xCD },
		{ { 0x01, 0xAB, 0xCD, 0x79 }, A, 0xAB },
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, IncrementDecrement)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x03 }, BC, 0x1 },
		{ { 0x03, 0x03 }, BC, 0x2 },
		{ { 0x03, 0x0B }, BC, 0x0 },
		{ { 0x23 }, HL, 0x1 },
		{ { 0x33 }, SP, 0x1 },
		{ { 0x0C }, C, 0x1 },
		{ { 0x0C, 0x0D }, C, 0x0 },
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, AddingAndFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x06, 0xAB, 0x80 }, A, 0xAB }, // set B to 0xAB and add B to A
		{ { 0x06, 0x02, 0x80, 0x80 }, A, 0x04 }, // set B to 0x02, add B to A, add B to A
		{ { 0x06, 0x02, 0x80, 0x80, 0x87 }, A, 0x08 }, // set B to 0x02, add B to A, add B to A, then add A to A.

		{ { 0x87 }, F, 0b10000000 }, // Add A to A (0), test 0 flag
		{ { 0x06, 0xAB, 0x80 }, F, 0b00000000 }, // Set B to 0xAB, add B to A, test 0 flag

		{ { 0x06, 0xFF, 0x80, 0x06, 0x01, 0x80 }, A, 0x00 }, // Set B to 0xFF, add B to A, set B to 0x01, add B to A, test A
		{ { 0x06, 0xFF, 0x80, 0x06, 0x01, 0x80 }, F, 0b10110000 }, // Set B to 0xFF, add B to A, set B to 0x01, add B to A, test flags

		{ { 0x06, 0x0F, 0x80, 0x80 }, A, 0x1E }, // Set B to 0x0F, add B to A, add B to A, test A
		{ { 0x06, 0x0F, 0x80, 0x80 }, F, 0b00100000 }, // Set B to 0xFF, add B to A, add B to A, test flags

		{ { 0xC6, 0xAB }, A, 0xAB }, // Add constant 0xAB to A

		{ { 0x87, 0x06, 0xAB, 0x80  }, F, 0b00000000 }, // Add A to A (0), set B to 0xAB, add B to A, test 0 flag

		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x8F }, A, 0x01 }, // Add 0xFF to A, Ad 0x01 to A, add A to itself and then add carry bit
		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x8F }, F, 0b00000000 }, // Add 0xFF to A, Add 0x01 to A, add A to itself and then add carry bit
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, SubtractingAndFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x06, 0xAB, 0x90 }, A, 0x55 }, // set B to 0xAB and subtract B from A
		{ { 0x06, 0x02, 0x80, 0x90 }, A, 0x00 }, // set B to 0x02, add B to A, subtract B from A
		{ { 0x06, 0x02, 0x80, 0x80, 0x97 }, A, 0x00 }, // set B to 0x02, add B to A, add B to A, then subtract A from A.

		{ { 0x97 }, F, 0b11000000 }, // Subtract A from A (0), test flags
		{ { 0x06, 0xAB, 0x90 }, F, 0b01110000 }, // Set B to 0xAB, subtract B from A, test flags

		{ { 0x06, 0xFF, 0x90, 0x06, 0x01, 0x90 }, A, 0x00 }, // Set B to 0xFF, subtract B from A, set B to 0x01, subtract B from A, test A
		{ { 0x06, 0xFF, 0x90, 0x06, 0x01, 0x90 }, F, 0b11000000 }, // Set B to 0xFF, subtract B from A, set B to 0x01, subtract B from A, test flags

		{ { 0xC6, 0x10, 0x06, 0x01, 0x90}, A, 0x0F }, // Set A to 0x10, Set B to 0x01, Subtract B from A, test A
		{ { 0xC6, 0x10, 0x06, 0x01, 0x90}, F, 0b01100000 }, // Set A to 0x10, Set B to 0x01, Subtract B from A, test flags

		{ { 0xD6, 0xAB }, A, 0x55 }, // Subtract constant 0xAB from A

		{ { 0x97, 0x06, 0xAB, 0x90  }, F, 0b01110000 }, // Subtract A from A (0), set B to 0xAB, subtract B from A, test 0 flag

		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x9F }, A, 0xFF }, // Add 0xFF to A, Add 0x01 to A, subtract A from itself and then subtract carry bit
		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x9F }, F, 0b01110000 }, // Add 0xFF to A, Add 0x01 to A, subtract A from itself and then subtract carry bit
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, LogicalAndWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases {
		{ { 0x3E, 0b10101010, 0x06, 0b01010101, 0xA0 }, A, 0x00 }, // Load 0b10101010 to A, 0b01010101 to B, and AND them together.
		{ { 0x3E, 0b10101010, 0x06, 0b01010101, 0xA0 }, F, 0b10100000 }, // Load 0b10101010 to A, 0b01010101 to B, and AND them together. Test flags.

		{ { 0x3E, 0b11110000, 0x06, 0b01010101, 0xA0 }, A, 0b01010000 }, // Load 0b11110000 to A, 0b01010101 to B, and AND them together.
		{ { 0x3E, 0b11110000, 0x06, 0b01010101, 0xA0 }, F, 0b00100000 }, // Load 0b11110000 to A, 0b01010101 to B, and AND them together. Test flags.

		{ { 0xA7, 0x3E, 0b10101010, 0xA7 }, A, 0b10101010 }, // And A with itself, load 0b10101010 into A, And A with itself
		{ { 0xA7, 0x3E, 0b10101010, 0xA7 }, F, 0b00100000 }, // And A with itself, load 0b10101010 into A, And A with itself, test flags
	
		{ { 0x3E, 0xFF, 0xE6, 0x0F }, A, 0x0F}, // Load 0xFF into A, AND with constant 0x0F.
		{ { 0x3E, 0xFF, 0xE6, 0x0F }, F, 0b00100000}, // Load 0xFF into A, AND with constant 0x0F. Test flags.
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, LogicalExclusiveOrWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x3E, 0b10101010, 0x06, 0b01010101, 0xA8 }, A, 0xFF }, // Load 0b10101010 to A, 0b01010101 to B, and XOR them together.
		{ { 0x3E, 0b10101010, 0x06, 0b01010101, 0xA8 }, F, 0b00000000 }, // Load 0b10101010 to A, 0b01010101 to B, and XOR them together. Test flags.

		{ { 0x3E, 0b11110000, 0x06, 0b01010101, 0xA8 }, A, 0b10100101 }, // Load 0b11110000 to A, 0b01010101 to B, and XOR them together.
		{ { 0x3E, 0b11110000, 0x06, 0b01010101, 0xA8 }, F, 0b00000000 }, // Load 0b11110000 to A, 0b01010101 to B, and XOR them together. Test flags.

		{ { 0xAF, 0x3E, 0b10101010, 0xAF }, A, 0x00 }, // XOR A with itself, load 0b10101010 into A, XOR A with itself
		{ { 0xAF, 0x3E, 0b10101010, 0xAF }, F, 0b10000000 }, // XOR A with itself, load 0b10101010 into A, XOR A with itself, test flags

		{ { 0x3E, 0xFF, 0xEE, 0x0F }, A, 0xF0}, // Load 0xFF into A, AND with constant 0x0F.
		{ { 0x3E, 0xFF, 0xEE, 0x0F }, F, 0b00000000}, // Load 0xFF into A, AND with constant 0x0F. Test flags.
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}


TEST(CPUTest, LogicalOrWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x3E, 0b10101010, 0x06, 0b01010101, 0xB0 }, A, 0xFF }, // Load 0b10101010 to A, 0b01010101 to B, and OR them together.
		{ { 0x3E, 0b10101010, 0x06, 0b01010101, 0xB0 }, F, 0b00000000 }, // Load 0b10101010 to A, 0b01010101 to B, and OR them together. Test flags.

		{ { 0x3E, 0b11110000, 0x06, 0b01010101, 0xB0 }, A, 0b11110101 }, // Load 0b11110000 to A, 0b01010101 to B, and OR them together.
		{ { 0x3E, 0b11110000, 0x06, 0b01010101, 0xB0 }, F, 0b00000000 }, // Load 0b11110000 to A, 0b01010101 to B, and OR them together. Test flags.

		{ { 0xAF, 0x3E, 0b10101010, 0xB7 }, A, 0b10101010 }, // OR A with itself, load 0b10101010 into A, XOR A with itself
		{ { 0xAF, 0x3E, 0b10101010, 0xB7 }, F, 0b00000000 }, // OR A with itself, load 0b10101010 into A, XOR A with itself, test flags

		{ { 0x3E, 0xFF, 0xF6, 0x0F }, A, 0xFF}, // Load 0xFF into A, OR with constant 0x0F.
		{ { 0x3E, 0xFF, 0xF6, 0x0F }, F, 0b00000000}, // Load 0xFF into A, OR with constant 0x0F. Test flags.
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, LogicalCmpWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expected_value;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x3E, 0xFF, 0x06, 0xFF, 0xB8 }, A, 0xFF }, // Load 0xFF into A and B, and compare them.
		{ { 0x3E, 0xFF, 0x06, 0xFF, 0xB8 }, F, 0b11000000 }, // Load 0xFF into A and B, and compare them. Test flags

		{ { 0x3E, 0xFF, 0x06, 0xFE, 0xB8 }, A, 0xFF }, // Load 0xFF into A, 0xFE into B, and compare them.
		{ { 0x3E, 0xFF, 0x06, 0xFE, 0xB8 }, F, 0b01000000 }, // Load 0xFF into A, 0xFE into B, and compare them. Test flags

		{ { 0x3E, 0xFE, 0x06, 0xFF, 0xB8 }, A, 0xFE }, // Load 0xFE into A, 0xFF into B, and compare them.
		{ { 0x3E, 0xFE, 0x06, 0xFF, 0xB8 }, F, 0b01110000 }, // Load 0xFE into A, 0xFF into B, and compare them. Test flags

		{ { 0x3E, 0xFE, 0xFE, 0xFF }, A, 0xFE }, // Load 0xFE into A, compare to constant 0xFF
		{ { 0x3E, 0xFE, 0xFE, 0xFF }, F, 0b01110000 }, // Load 0xFE into A, compare to constant 0xFF. Test flags
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expected_value, getERegister(cpu, test.eRegister));
	}
}

rose_core::u16 getERegister(rose_core::CPU& p_cpu, ERegister p_eRegister)
{
	const rose_core::CPU::Registers& registers = p_cpu.viewRegisters();
	switch (p_eRegister) {
	case AF: return registers.af;
	case BC: return registers.bc;
	case DE: return registers.de;
	case HL: return registers.hl;
	case SP: return registers.stackPointer;
	case PC: return registers.programCounter;
	case A:  return registers.a;
	case F:	 return registers.f;
	case B:	 return registers.b;
	case C:	 return registers.c;
	case D:	 return registers.d;
	case E:	 return registers.e;
	case H:	 return registers.h;
	case L:	 return registers.l;
	}
	return 0xFFFF;
}