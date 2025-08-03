#include <gtest/gtest.h>

#include "cpu-test.h"
#include "cpu.h"


TEST(CPUTest, TestingTests)
{
	mmu::MMU mmu;
	cpu::CPU cpu(&mmu);
	EXPECT_TRUE(true);
}