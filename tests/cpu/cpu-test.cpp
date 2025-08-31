#include <gtest/gtest.h>

#include "../mmu/mmu-test.h"
#include "cpu-test.h"

#include "rose.h"

std::string test_1 = "../resources/blargg/cpu_instrs/01-special.gb";

/*

Untested Instructions:
- 0x00 NOP
- 0x10 STOP
- 0x76 HALT
- 0xF3 DI
- 0xFB EI
- All RET
- All CALL
- All RST
*/


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
		rose_core::u16 expectedValue;
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}

}

TEST(CPUTest, LoadRegistersIntoRegisters)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x01, 0xAB, 0xCD, 0x40 }, B, 0xCD },
		{ { 0x01, 0xAB, 0xCD, 0x48 }, C, 0xCD },
		{ { 0x3E, 0xAB, 0x4F }, C, 0xAB },
		{ { 0x01, 0xAB, 0xCD, 0x78 }, A, 0xCD },
		{ { 0x01, 0xAB, 0xCD, 0x79 }, A, 0xAB },
		
		{ { 0x21, 0xCD, 0xAB, 0xF9 }, SP, 0xABCD }, // Load 0xABCD into HL, copy HL into SP
		{ { 0x21, 0xCD, 0xAB, 0xF9, 0xF8, 0x08 }, HL, 0xABD5 }, // the above + (loading SP + constant signed 0x08 into HL)
		{ { 0x21, 0xCD, 0xAB, 0xF9, 0xF8, 0x08 },  F, 0b00000000 }, // the above + (loading SP + constant signed 0x08 into HL), check flags
		{ { 0x21, 0xCD, 0xAB, 0xF9, 0xF8, 0xFF }, HL, 0xABCC }, // the above + (loading SP - constant signed 0x01 into HL)  
		{ { 0x21, 0xCD, 0xAB, 0xF9, 0xF8, 0xFF },  F, 0b00000000 }, // the above + (loading SP - constant signed 0x01 into HL), check flags
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, LoadRegistersIntoAddress)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		rose_core::u16 addressToCheck;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x01, 0xCD, 0xAB, 0x3E, 0x56, 0x02 }, 0xABCD, 0x56 }, // Load 0xABCD to BC, load 0x56 into A, copy A into address stored by B

		{ { 0x21, 0xCD, 0xAB, 0x3E, 0x56, 0x22 }, 0xABCD, 0x56 }, // Load 0xABCD to HL, load 0x56 into A, copy A into address stored by HL and increment HL
		{ { 0x21, 0xCD, 0xAB, 0x3E, 0x56, 0x22, 0x22 }, 0xABCE, 0x56 }, // Load 0xABCD to HL, load 0x56 into A, copy A into address stored by HL and increment HL twice
	
		{ { 0x21, 0xCD, 0xAB, 0x3E, 0x56, 0x32 }, 0xABCD, 0x56 }, // Load 0xABCD to HL, load 0x56 into A, copy A into address stored by HL and decrement HL
		{ { 0x21, 0xCD, 0xAB, 0x3E, 0x56, 0x32, 0x32 }, 0xABCC, 0x56 }, // Load 0xABCD to HL, load 0x56 into A, copy A into address stored by HL and decrement HL twice

		{ { 0x21, 0xCD, 0xAB, 0x3E, 0x56, 0x77 }, 0xABCD, 0x56 }, // Load 0xABCD to HL, load 0x56 into A, copy A into address stored by HL
		{ { 0x21, 0xCD, 0xAB, 0x36, 0x77 }, 0xABCD, 0x77 }, // Load 0xABCD to HL, copy constant 0x77 to address of HL

		{ { 0x3E, 0x56, 0xEA, 0x01, 0x23 }, 0x2301, 0x56 }, // Load 0x56 into A, then copy contents of A into constant address 0x2301

		{ { 0x3E, 0x56, 0xE0, 0x67 }, 0xFF67, 0x56 }, // Load 0x56 into A, then copy contents of A into 0xFF00 + constant 0x0067
		{ { 0x3E, 0x56, 0x0E, 0x67, 0xE2 }, 0xFF67, 0x56 }, // Load 0x56 into A, Load 0x67 into C, then copy contents of A into 0xFF00 + C

		{ { 0x21, 0xCD, 0xAB, 0xF9, 0x08, 0x00, 0x00 }, 0x0000, 0xCD }, // Load 0xABCD into HL, copy HL into SP, copy SP into address 0x0000
		{ { 0x21, 0xCD, 0xAB, 0xF9, 0x08, 0x00, 0x00 }, 0x0001, 0xAB }, // Load 0xABCD into HL, copy HL into SP, copy SP into address 0x0000
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
		EXPECT_EQ(test.expectedValue, mmu.getU8(test.addressToCheck));
	}
}

TEST(CPUTest, LoadAddressIntoRegister)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x01, 0x03, 0x00, 0x0A }, A, 0x0A }, // Load 0x0003 to BC, copy value in address stored by BC into A

		{ { 0x21, 0x03, 0x00, 0x2A }, A, 0x2A }, // Load 0x0003 to HL, copy value in address stored by HL into A and increment HL
		{ { 0x21, 0x03, 0x00, 0x2A }, HL, 0x0004 }, // Load 0x0003 to HL, copy value in address stored by HL into A and increment HL
		{ { 0x21, 0x03, 0x00, 0x3A }, HL, 0x0002 }, // Load 0x0003 to HL, copy value in address stored by HL into A and decrement HL

		{ { 0x21, 0x03, 0x00, 0x46 }, B, 0x46 }, // Load 0x0003 to HL, copy value in address stored by HL into B

		{ { 0xFA, 0x00, 0x00 }, A, 0xFA }, // Load contents of address 0x0000 into A
		{ { 0xFA, 0x01, 0x00 }, A, 0x01 }, // Load contents of address 0x0001 into A
		{ { 0xFA, 0x02, 0x00 }, A, 0x00 }, // Load contents of address 0x0002 into A

		{ { 0x3E, 0x56, 0xE0, 0x67, 0x3E, 0x00, 0xF0, 0x67 }, A, 0x56 }, // Load 0x56 into A, then copy contents of A into 0xFF00 + constant 0x0067, load 0x00 into A, then load contents of 0xFF67 back into A
		{ { 0x3E, 0x56, 0x0E, 0x67, 0xE2, 0x3E, 0x00, 0xF2 }, A, 0x56 }, // Load 0x56 into A, Load 0x67 into C, then copy contents of A into 0xFF00 + C, load 0x00 into A, then load contents of 0xFF00 + C back into A
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, IncrementDecrement)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x03 }, BC, 0x1 },
		{ { 0x03, 0x03 }, BC, 0x2 },
		{ { 0x03, 0x0B }, BC, 0x0 },
		{ { 0x23 }, HL, 0x1 },
		{ { 0x33 }, SP, 0x1 },
		{ { 0x0C }, C, 0x1 },
		{ { 0x0C, 0x0D }, C, 0x0 },

		{ { 0x21, 0xCD, 0xAB, 0x34, 0xFA, 0xCD, 0xAB }, A, 0x1 }, // Load 0xABCD into HL, increment value at address of HL by 1, copy value at 0xABCD into A.
		{ { 0x21, 0xCD, 0xAB, 0x34, 0xFA, 0xCD, 0xAB }, F, 0x00 }, // Load 0xABCD into HL, increment value at address of HL by 1, copy value at 0xABCD into A. Check flags

		{ { 0x21, 0xCD, 0xAB, 0x35, 0xFA, 0xCD, 0xAB }, A, 0xFF }, // Load 0xABCD into HL, decrement value at address of HL by 1, copy value at 0xABCD into A.
		{ { 0x21, 0xCD, 0xAB, 0x35, 0xFA, 0xCD, 0xAB }, F, 0b01100000 }, // Load 0xABCD into HL, decrement value at address of HL by 1, copy value at 0xABCD into A. Check flags
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, AddingAndFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
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

		{ { 0x21, 0x00, 0x00, 0x29 }, HL, 0x0 }, // Load 0x0000 into HL, add HL to itself
		{ { 0x21, 0x00, 0x00, 0x29 },  F, 0b00000000 }, // Load 0x0000 into HL, add HL to itself, check flags

		{ { 0x21, 0xF0, 0x00, 0x29 }, HL, 0x1E0 }, // Load 0x00F0 into HL, add HL to itself
		{ { 0x21, 0xF0, 0x00, 0x29 },  F, 0b00000000 }, // Load 0x0000 into HL, add HL to itself, check flags

		{ { 0x21, 0x00, 0x0F, 0x29 }, HL, 0x1E00 }, // Load 0x0F00 into HL, add HL to itself
		{ { 0x21, 0x00, 0x0F, 0x29 },  F, 0b00100000 }, // Load 0x0F00 into HL, add HL to itself, check flags

		{ { 0x21, 0x00, 0x00, 0x86 }, A, 0x21 }, // Load 0x0000 into HL, add value of address stored by HL to A.
		{ { 0x21, 0x00, 0x00, 0x86 },  F, 0b00000000 }, // Load 0x0000 into HL, add value of address stored by HL to A, check flags

		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x8E }, A, 0xC7 }, // Add 0xFF to A, add 0x01 to A, add value in HL's address to A and then add carry bit
		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x8E }, F, 0b00000000 }, // Add 0xFF to A, add 0x01 to A, add value in HL's address to A and then add carry bit. flag check
	
		{ { 0xE8, 0x08 }, SP, 0x0008 }, // Add constant signed 8 to SP
		{ { 0xE8, 0x08 }, F, 0b00000000 }, // Add constant signed 8 to SP, check flags

		{ { 0xE8, 0x08, 0xE8, 0xF8 }, SP, 0x0000 }, //Add constant signed 8 to SP, then add signed -8 to SP
		{ { 0xE8, 0x08, 0xE8, 0xF8 }, F, 0b00000000 }, //Add constant signed 8 to SP, then add signed -8 to SP, check flags
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, SubtractingAndFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
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


		{ { 0x21, 0x01, 0x00, 0x96 }, A, 0xFF }, // Load 0x0001 into HL, sub value of address stored by HL from A.
		{ { 0x21, 0x01, 0x00, 0x96 },  F, 0b01110000 }, // Load 0x0001 into HL, sub value of address stored by HL from A, check flags

		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x9E }, A, 0x39 }, // Add 0xFF to A, add 0x01 to A, sub value in HL's address from A and then sub carry bit
		{ { 0xC6, 0xFF, 0xC6, 0x01, 0x9E }, F, 0b01110000 }, // Add 0xFF to A, add 0x01 to A, sub value in HL's address from A and then sub carry bit. flag check
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, LogicalAndWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
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

		{ { 0x21, 0x01, 0x00, 0xA6 }, A, 0x00 }, // Load 0x0001 into HL, AND value of address stored by HL from A.
		{ { 0x21, 0x01, 0x00, 0xA6 }, F, 0b10100000 }, // Load 0x0001 into HL, AND value of address stored by HL from A. Flags
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, LogicalExclusiveOrWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
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

		{ { 0x21, 0x00, 0x00, 0xAE }, A, 0b00100001 }, // Load 0x0000 into HL, XOR value of address stored by HL from A.
		{ { 0x21, 0x00, 0x00, 0xAE }, F, 0b00000000 }, // Load 0x0000 into HL, XOR value of address stored by HL from A. Flags
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}


TEST(CPUTest, LogicalOrWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
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

		{ { 0x21, 0x00, 0x00, 0xB6 }, A, 0b00100001 }, // Load 0x0000 into HL, OR value of address stored by HL from A.
		{ { 0x21, 0x00, 0x00, 0xB6 }, F, 0b00000000 }, // Load 0x0000 into HL, OR value of address stored by HL from A. Flags
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}

TEST(CPUTest, LogicalCmpWithFlags)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
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

		{ { 0x21, 0x00, 0x00, 0xBE }, A, 0b00000000 }, // Load 0x0000 into HL, OR value of address stored by HL from A.
		{ { 0x21, 0x00, 0x00, 0xBE }, F, 0b01110000 }, // Load 0x0000 into HL, OR value of address stored by HL from A. Flags
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}


TEST(CPUTest, RotateRegisters)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x3E, 0b10101010, 0x07 }, A, 0b01010101}, // Set A to 0b10101010 and then rotate left.
		{ { 0x3E, 0b10101010, 0x07 }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left. Flag check.

		{ { 0x3E, 0b10101010, 0x07, 0x07 }, A, 0b10101010}, // Set A to 0b10101010 and then rotate left twice.
		{ { 0x3E, 0b10101010, 0x07, 0x07 }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left twice. Flag check.

		{ { 0x3E, 0b10101010, 0x17 }, A, 0b01010100}, // Set A to 0b10101010 and then rotate left w/ carry.
		{ { 0x3E, 0b10101010, 0x17 }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left w/ carry. Flag check.

		{ { 0x3E, 0b10101010, 0x17, 0x17 }, A, 0b10101001}, // Set A to 0b10101010 and then rotate left w/ carry twice.
		{ { 0x3E, 0b10101010, 0x17, 0x17 }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left w/ carry twice. Flag check.


		{ { 0x3E, 0b10101010, 0x0F }, A, 0b01010101}, // Set A to 0b10101010 and then rotate left.
		{ { 0x3E, 0b10101010, 0x0F }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left. Flag check.

		{ { 0x3E, 0b10101010, 0x0F, 0x0F }, A, 0b10101010}, // Set A to 0b10101010 and then rotate left twice.
		{ { 0x3E, 0b10101010, 0x0F, 0x0F }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left twice. Flag check.

		{ { 0x3E, 0b10101010, 0x1F }, A, 0b01010101}, // Set A to 0b10101010 and then rotate left w/ carry.
		{ { 0x3E, 0b10101010, 0x1F }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left w/ carry. Flag check.

		{ { 0x3E, 0b10101010, 0x1F, 0x1F }, A, 0b00101010}, // Set A to 0b10101010 and then rotate left w/ carry twice.
		{ { 0x3E, 0b10101010, 0x1F, 0x1F }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left w/ carry twice. Flag check.

		// CB test cases
		{ { 0x3E, 0b10101010, 0xCB, 0x07 }, A, 0b01010101}, // Set A to 0b10101010 and then rotate left.
		{ { 0x3E, 0b10101010, 0xCB, 0x07 }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x07, 0xCB, 0x07 }, A, 0b10101010}, // Set A to 0b10101010 and then rotate left twice.
		{ { 0x3E, 0b10101010, 0xCB, 0x07, 0xCB, 0x07 }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left twice. Flag check.

		{ { 0x3E, 0b10000000, 0xCB, 0x17 }, A, 0b00000000}, // Set A to 0b10101010 and then rotate left w/ carry.
		{ { 0x3E, 0b10000000, 0xCB, 0x17 }, F, 0b10010000}, // Set A to 0b10101010 and then rotate left w/ carry. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x17 }, A, 0b01010100}, // Set A to 0b10101010 and then rotate left w/ carry.
		{ { 0x3E, 0b10101010, 0xCB, 0x17 }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left w/ carry. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x17, 0xCB, 0x17 }, A, 0b10101001}, // Set A to 0b10101010 and then rotate left w/ carry twice.
		{ { 0x3E, 0b10101010, 0xCB, 0x17, 0xCB, 0x17 }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left w/ carry twice. Flag check.


		{ { 0x3E, 0b10101010, 0xCB, 0x0F }, A, 0b01010101}, // Set A to 0b10101010 and then rotate left.
		{ { 0x3E, 0b10101010, 0xCB, 0x0F }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x0F, 0xCB, 0x0F }, A, 0b10101010}, // Set A to 0b10101010 and then rotate left twice.
		{ { 0x3E, 0b10101010, 0xCB, 0x0F, 0xCB, 0x0F }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left twice. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x1F }, A, 0b01010101}, // Set A to 0b10101010 and then rotate left w/ carry.
		{ { 0x3E, 0b10101010, 0xCB, 0x1F }, F, 0b00000000}, // Set A to 0b10101010 and then rotate left w/ carry. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x1F, 0xCB, 0x1F }, A, 0b00101010}, // Set A to 0b10101010 and then rotate left w/ carry twice.
		{ { 0x3E, 0b10101010, 0xCB, 0x1F, 0xCB, 0x1F }, F, 0b00010000}, // Set A to 0b10101010 and then rotate left w/ carry twice. Flag check.


		{ { 0x21, 0x00, 0x00, 0xCB, 0x06, 0xFA, 0x00, 0x00 }, A, 0b01000010 }, // Load 0x0000 into HL. Rotate contents of address 0x00 left. Copy contents of 0x0000 to A.
		{ { 0x21, 0x00, 0x00, 0xCB, 0x06 }, F, 0x00 }, // Load 0x0000 into HL. Rotate contents of address 0x00 left. Copy contents of 0x0000 to A. sFlag check.
		// Assuming 0x16, 0x0E, and 0x1E will also work.  
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}


TEST(CPUTest, ShiftRegisters)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x3E, 0b10101010, 0xCB, 0x27 }, A, 0b01010100}, // Set A to 0b10101010 and then shift left.
		{ { 0x3E, 0b10101010, 0xCB, 0x27 }, F, 0b00010000}, // Set A to 0b10101010 and then shift left. Flag check.

		{ { 0x21, 0x00, 0x00, 0xCB, 0x26, 0x7E }, A, 0b01000010}, // Set HL to 0x0000, shift left value in address of HL, copy to A.
		{ { 0x21, 0x00, 0x00, 0xCB, 0x26 }, F, 0b00000000}, // Set HL to 0x0000, shift left value in address of HL, copy to A. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x2F }, A, 0b11010101}, // Set A to 0b10101010 and then shift right arithmetically.
		{ { 0x3E, 0b10101010, 0xCB, 0x2F }, F, 0b00000000}, // Set A to 0b10101010 and then shift right arithmetically. Flag check.

		{ { 0x21, 0x00, 0x00, 0xCB, 0x2E, 0x7E }, A, 0b00010000}, // Set HL to 0x0000, shift right arithmetically value in address of HL, copy to A.
		{ { 0x21, 0x00, 0x00, 0xCB, 0x2E }, F, 0b00010000}, // Set HL to 0x0000, shift right arithmetically value in address of HL, copy to A. Flag check.

		{ { 0x3E, 0b10101010, 0xCB, 0x3F }, A, 0b01010101}, // Set A to 0b10101010 and then shift right logically.
		{ { 0x3E, 0b10101010, 0xCB, 0x3F }, F, 0b00000000}, // Set A to 0b10101010 and then shift right logically. Flag check.

		{ { 0x21, 0x00, 0x00, 0xCB, 0x3E, 0x7E }, A, 0b00010000}, // Set HL to 0x0000, shift right logically value in address of HL, copy to A.
		{ { 0x21, 0x00, 0x00, 0xCB, 0x3E }, F, 0b00010000}, // Set HL to 0x0000, shift right logically value in address of HL, copy to A. Flag check.

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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}



TEST(CPUTest, SwapRegisters)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x3E, 0xAB, 0xCB, 0x37 }, A, 0xBA}, // Set A to 0xAB and then swap high and low.
		{ { 0x3E, 0xAB, 0xCB, 0x37 }, F, 0b00000000}, // Set A to 0xAB and then swap high and low. Flag check.

		{ { 0x21, 0x00, 0x00, 0xCB, 0x36, 0x7E }, A, 0x12}, // Set HL to 0x0000 and then swap high and low of address stored in HL.

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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}


TEST(CPUTest, StackControl)
{
	typedef struct TestCaseAddress
	{
		std::vector<rose_core::u8> instructions;
		rose_core::u16 addressToCheck;
		rose_core::u16 expectedValue;
	} TestCaseAddress;

	std::vector<TestCaseAddress> testCasesAddress{
		{ { 0xE8, 0x64, 0x01, 0xCD, 0xAB, 0xC5 }, 0x62, 0xCD }, // Set stack pointer to 100, then BC to 0xABCD. Push 0xABCD to stack.
		{ { 0xE8, 0x64, 0x01, 0xCD, 0xAB, 0xC5 }, 0x63, 0xAB }, // Set stack pointer to 100, then BC to 0xABCD. Push 0xABCD to stack. 
	};

	for (TestCaseAddress test : testCasesAddress)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expectedValue, mmu.getU8(test.addressToCheck));
	}

	typedef struct TestCaseRegister
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCaseRegister;

	std::vector<TestCaseRegister> testCasesRegister{
		{ { 0xE8, 0x64, 0x01, 0xCD, 0xAB, 0xC5 }, SP, 0x62 }, // Set stack pointer to 100, then BC to 0xABCD. Push 0xABCD to stack. 

		{ { 0xE8, 0x64, 0x01, 0xCD, 0xAB, 0xC5, 0xD1 }, DE, 0xABCD }, // Set stack pointer to 100, then BC to 0xABCD. Push 0xABCD to stack. Pop into DE.
		{ { 0xE8, 0x64, 0x01, 0xCD, 0xAB, 0xC5, 0xD1 }, SP, 0x64 }, // Set stack pointer to 100, then BC to 0xABCD. Push 0xABCD to stack. Pop into DE.
	};

	for (TestCaseRegister test : testCasesRegister)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu, 0x0);

		loadVectorToMemory(test.instructions, mmu);

		while (cpu.viewRegisters().programCounter < test.instructions.size())
		{
			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
		}
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
	
}


TEST(CPUTest, Jumps)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x18, 0x10 }, PC, 0x12}, // Jump forward 10
		{ { 0x18, 0x02, 0x18, 0x02, 0x18, 0xFC }, PC, 0x06}, // Jump forward 2, then jump back 4, then jump forward 4

		{ { 0x20, 0x10 }, PC, 0x12}, // Jump forward 10 if Z is 0
		{ { 0x28, 0x10 }, PC, 0x02}, // Jump forward 10 if Z is 1


		{ { 0xC3, 0xCD, 0xAB }, PC, 0xABCD}, // Jump to 0xABCD
		{ { 0xC2, 0xCD, 0xAB }, PC, 0xABCD}, // Jump to 0xABCD if Z is 0
		{ { 0xCA, 0xCD, 0xAB }, PC, 0x3},    // Jump to 0xABCD if Z is 1

		{ { 0x21, 0xCD, 0xAB, 0xE9 }, PC, 0xABCD},    // Set HL to 0xABCD and then jump to the value of HL.
		
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}




TEST(CPUTest, BitResSet)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{

		{ { 0x21, 0x01, 0x00, 0xCB, 0x45 }, F, 0b00100000 }, // Set HL to 0x0001, copy complement of bit 0 of L to Z flag
		{ { 0x21, 0x00, 0x00, 0xCB, 0x45 }, F, 0b10100000 }, // Set HL to 0x0000, copy complement of bit 0 of L to Z flag

		{ { 0x21, 0x00, 0x00, 0xCB, 0x46 }, F, 0b00100000 }, // Set HL to 0x0000, copy complement of bit 0 of value at HL to Z flag
		{ { 0x21, 0x02, 0x00, 0xCB, 0x46 }, F, 0b10100000 }, // Set HL to 0x0002, copy complement of bit 0 of value at HL to Z flag

		{ { 0xCB, 0xC0, 0xCB, 0x80 }, B, 0x00 }, // Set bit 0 of B to 1, then reset bit 0 of B to 0
		{ { 0x21, 0x01, 0x00, 0xCB, 0x86, 0xFA, 0x01, 0x00 }, A, 0x00 }, // Set HL to 0x0001, reset bit 0 of 0x0001 to 0, copy value at 0x1 to A

		{ { 0xCB, 0xC0 }, B, 0x01 }, // Set bit 0 of B to 1
		{ { 0x21, 0x01, 0x00, 0xCB, 0xE6, 0xFA, 0x01, 0x00 }, A, 0x11 }, // Set HL to 0x0001, set bit 4 of 0x0001 to 1, copy value at 0x1 to A
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}


TEST(CPUTest, Miscellaneous)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases{
		{ { 0x37 }, F, 0b00010000}, // Set carry flag SCF

		{ { 0xC6, 0x54, 0xC6, 0x28}, A, 0x7C}, // https://blog.ollien.com/posts/gb-daa/ Without DAA.
		{ { 0xC6, 0x54, 0xC6, 0x28, 0x27 }, A, 0x82}, // https://blog.ollien.com/posts/gb-daa/ Testing DAA.

		{ { 0x3F }, F, 0b00010000}, // Flip carry flag CCF
		{ { 0x3F, 0x3F }, F, 0b00000000}, // Flip carry flag twice CCF

		{ { 0x2F }, A, 0xFF}, // One's complement register A CPL
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}



TEST(CPUTest, EdgeCases)
{
	typedef struct TestCase
	{
		std::vector<rose_core::u8> instructions;
		ERegister eRegister;
		rose_core::u16 expectedValue;
	} TestCase;

	std::vector<TestCase> testCases {
		// POP AF should not affect lower 4 bits. This is from 01-special of BLARGG.
		{ { 0x01, 0x00, 0x12,   0xC5, 0xF1, 0xF5, 0xD1,    0x79,   0xE6,   0xF0,    0xBB,   0xC2, 0xF0, 0xFF,   0x04, 0x0C, 0x20, 0xF1 }, PC, 0x12},


		{ { 0xDE, 0x00 }, A, 0x00 },
		{ { 0xDE, 0x00 }, F, 0b11000000 },
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
		EXPECT_EQ(test.expectedValue, getERegister(cpu, test.eRegister));
	}
}


TEST(CPUTest, BlarggTests)
{
	typedef struct TestCase
	{
		std::string romFile;
		int maxInstructions;
	} TestCase;

	std::vector<TestCase> testCases {
		//{ "../resources/blargg/cpu_instrs/01-special.gb", 2000000 }, // passed
		// {"../resources/blargg/cpu_instrs/02-interrupts.gb", 1000000}, // requires timer set up
		// { "../resources/blargg/cpu_instrs/03-op sp,hl.gb", 2000000 }, // confused
		//{ "../resources/blargg/cpu_instrs/04-op r,imm.gb", 2000000 }, // passed
		//{"../resources/blargg/cpu_instrs/05-op rp.gb", 2000000}, // passed
		/*{"../resources/blargg/cpu_instrs/06-ld r,r.gb", 1000000},
		{ "../resources/blargg/cpu_instrs/07-jr,jp,call,ret,rst.gb", 1000000 },
		{ "../resources/blargg/cpu_instrs/08-misc instrs.gb", 1000000 },
		{ "../resources/blargg/cpu_instrs/09-op r,r.gb", 10000000 },
		{ "../resources/blargg/cpu_instrs/10-bit ops.gb", 7500000 },
		{ "../resources/blargg/cpu_instrs/11-op a,(hl).gb", 7500000 },*/
	};

	for (TestCase test : testCases)
	{
		rose_core::MMU mmu;
		rose_core::CPU cpu(mmu);
		ASSERT_NO_FATAL_FAILURE(loadTestCartridge(test.romFile, mmu));

		int instructionsRan = 0;
		rose_core::u8 console = mmu.getU8(0xFF01);
		while (instructionsRan < test.maxInstructions)
		{
			if (mmu.getU8(0xFF01) != console)
			{
				console = mmu.getU8(0xFF01);
				std::cout << console;
			}

			ASSERT_NO_FATAL_FAILURE(cpu.executeInstruction());
			instructionsRan++;
		}

		std::cout << std::endl;
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