#pragma once

#include <string>

#include "cartridge/cartridge.h"
#include "cpu/cpu.h"
#include "mmu/mmu.h"

namespace rose
{
	class Rose
	{
	public:
		Rose();

		int runGame();
		int loadCartridge(std::string path);
	private:
		cartridge::Cartridge cart;
		cpu::CPU cpu;
		mmu::MMU mmu;
	};
}