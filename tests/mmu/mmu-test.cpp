#include <gtest/gtest.h>

#include "mmu-test.h"

std::string testingCartridge = "../resources/blargg/cpu_instrs.gb";

TEST(MMUTest, Getters)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);
	rose_core::PPU ppu(ih);
	rose_core::MMU mmu(ih, timer, ppu);
	ASSERT_NO_FATAL_FAILURE(loadTestCartridge(testingCartridge, mmu));

	EXPECT_EQ(mmu.getU8(0x00), 0x3C);
	EXPECT_EQ(mmu.getU8(0x01), 0xC9);
	EXPECT_EQ(mmu.getU8(0x133), 0x3E);
	EXPECT_EQ(mmu.getU8(0x656), 0xFE);
	EXPECT_EQ(mmu.getU8(0x744B), 0xF5);
	EXPECT_EQ(mmu.getU8(0xE742), 0x0); // we only load 0x0000 to 0x7FFF at bootup, expect rest to be 0
}

TEST(MMUTest, Setters)
{
	rose_core::InterruptHandler ih;
	rose_core::Timer timer(ih);
	rose_core::PPU ppu(ih);
	rose_core::MMU mmu(ih, timer, ppu);
	ASSERT_NO_FATAL_FAILURE(loadTestCartridge(testingCartridge, mmu));

	ASSERT_NO_FATAL_FAILURE(mmu.setU8(0x00, 0x3D));
	EXPECT_EQ(mmu.getU8(0x00), 0x3D);
}

// Takes in a file path and attempts to load a .gb file into Rose's Cartridge and then memory
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

// Takes in an array of bytes and loads it into Rose's memory
void loadVectorToMemory(std::vector<rose_core::u8>& values, rose_core::MMU& mmu)
{
	for (size_t i = 0; i < values.size(); ++i)
	{
		mmu.setU8(i, values[i]);
	}
}