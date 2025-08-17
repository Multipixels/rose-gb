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

		const MMU& getMMU() const;
		const CPU& viewCPU() const;

	private:
		Cartridge m_cart;
		CPU m_cpu;
		MMU m_mmu;
	};
}