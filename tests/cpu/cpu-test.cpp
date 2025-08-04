#include <gtest/gtest.h>

#include "cpu-test.h"

std::string test_1 = "../resources/blargg/cpu_instrs/01-special.gb";

TEST(CPUTest, TestingTests)
{
	mmu::MMU mmu;
	cpu::CPU cpu(&mmu);

	ASSERT_NO_FATAL_FAILURE(loadTestCartridge(test_1, &mmu));

	EXPECT_TRUE(true);
}

// Takes in a file path and attempts to load a .gb file into Rose's Cartridge
void loadTestCartridge(std::string path, mmu::MMU* mmu)
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

	mmu->loadCartridgeData(cartridgeBuffer);
	cartridgeBuffer->close();
}