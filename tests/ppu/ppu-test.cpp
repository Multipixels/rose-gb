#include <gtest/gtest.h>

#include "ppu-test.h"

TEST(PPUTest, Tick)
{
	rose_core::InterruptHandler ih;
	rose_core::PPU ppu(ih);

	for (int i = 1; i < 61; i++)
	{
		for (int j = 0; j < 144; j++)
		{
			for (int k = 0; k < 80; k++)
			{
				rose_core::u8 stat = ppu.readSTAT();
				ASSERT_EQ(stat & 0b11, 2) << "Expected Mode 2, got Mode " << (stat & 0b11) << " on frame " << i << ", line " << j << ", dot " << k << ".";
				ppu.tick();
			}

			for (int k = 0; k < 172; k++)
			{
				rose_core::u8 stat = ppu.readSTAT();
				ASSERT_EQ(stat & 0b11, 3) << "Expected Mode 3, got Mode " << (stat & 0b11) << " on frame " << i << ", line " << j << ", dot " << k << ".";
				ppu.tick();
			}

			for (int k = 0; k < 204; k++)
			{
				rose_core::u8 stat = ppu.readSTAT();
				ASSERT_EQ(stat & 0b11, 0) << "Expected Mode 0, got Mode " << (stat & 0b11) << " on frame " << i << ", line " << j << ", dot " << k << ".";
				ppu.tick();
			}
		}

		for (int j = 144; j < 154; j++)
		{
			for (int k = 0; k < 456; k++)
			{
				rose_core::u8 stat = ppu.readSTAT();
				ASSERT_EQ(stat & 0b11, 1) << "Expected Mode 1, got Mode " << (stat & 0b11) << " on frame " << i << ", line " << j << ", dot " << k << ".";
				ppu.tick();
			}
		}
	}
}