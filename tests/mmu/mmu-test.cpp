#include <gtest/gtest.h>

#include "mmu-test.h"

std::string testingCartridge = "../resources/blargg/cpu_instrs.gb";

TEST(MMUTest, Getters)
{
	rose_core::MMU mmu;
	ASSERT_NO_FATAL_FAILURE(loadTestCartridge(testingCartridge, mmu));

	EXPECT_EQ(mmu.getU8(0x00), 0x3C);
	EXPECT_EQ(mmu.getU8(0x01), 0xC9);
	EXPECT_EQ(mmu.getU8(0x133), 0x3E);
	EXPECT_EQ(mmu.getU8(0x656), 0xFE);
	EXPECT_EQ(mmu.getU8(0x744B), 0xF5);
	EXPECT_EQ(mmu.getU8(0xE742), 0x0); // we only load 0x0000 to 0x7FFF at bootup, expect rest to be 0

	EXPECT_EQ(mmu.getU16(0x00), 0xC93C);
	EXPECT_EQ(mmu.getU16(0x01), 0x00C9);
	EXPECT_EQ(mmu.getU16(0x697), 0x6C61);
	EXPECT_EQ(mmu.getU16(0x7542), 0x83F0);
}

TEST(MMUTest, Setters)
{
	rose_core::MMU mmu;
	ASSERT_NO_FATAL_FAILURE(loadTestCartridge(testingCartridge, mmu));

	ASSERT_NO_FATAL_FAILURE(mmu.setU8(0x00, 0x3D));
	EXPECT_EQ(mmu.getU8(0x00), 0x3D);

	//mmu.setU8(0x10000, 0x3D); // TODO: Find way to do error checking more elegantly

	ASSERT_NO_FATAL_FAILURE(mmu.setU16(0x01, 0xDA34));
	EXPECT_EQ(mmu.getU8(0x01), 0xDA);
	EXPECT_EQ(mmu.getU8(0x02), 0x34);
	EXPECT_EQ(mmu.getU16(0x01), 0x34DA);
}

// Takes in a file path and attempts to load a .gb file into Rose's Cartridge
void loadTestCartridge(std::string path, rose_core::MMU& mmu)
{
	// Load into Cartridge construct
	std::ifstream istr;
	std::filebuf* cartridgeBuffer = istr.rdbuf();
	auto errorChk = cartridgeBuffer->open(path, std::ios_base::in | std::ios_base::binary);

	if (!errorChk)
	{
		std::cerr << "Could not read file.";
		FAIL();
	}

	mmu.loadCartridgeData(cartridgeBuffer);
	cartridgeBuffer->close();
}