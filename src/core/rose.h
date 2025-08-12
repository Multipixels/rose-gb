#pragma once

#include <string>

#include "cartridge/cartridge.h"
#include "cpu/cpu.h"
#include "mmu/mmu.h"

namespace rose_core
{
	class Rose
	{
	public:
		Rose();

		int loadGame();
		int runGame();
		int loadCartridge(std::string path);

		const mmu::MMU& getMMU() const;

	private:
		cartridge::Cartridge m_cart;
		cpu::CPU m_cpu;
		mmu::MMU m_mmu;
	};
}