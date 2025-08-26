#include <gtest/gtest.h>

#include "../mmu/mmu-test.h"
#include "cpu-test.h"

std::string test_1 = "../resources/blargg/cpu_instrs/01-special.gb";

TEST(CPUTest, TestingTests)
{
	rose_core::MMU mmu;
	rose_core::CPU cpu(mmu);

	ASSERT_NO_FATAL_FAILURE(loadTestCartridge(test_1, mmu));

	EXPECT_TRUE(true);
}