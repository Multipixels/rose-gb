#include <fstream>
#include <iostream>

#include "rose.h"

namespace rose_core
{
	Rose::Rose() 
		: m_cart(Cartridge())
		, m_mmu(MMU())
		, m_cpu(CPU(m_mmu))
	{
	}

	int Rose::loadGame()
	{
		if (loadCartridge("../resources/blargg/cpu_instrs.gb") == 1)
		{
			return 1;
		};
	}

	// Loads the cartridge and boots up the Game Boy
	int Rose::runGame()
	{
		while (true)
		{
			m_cpu.executeInstruction();
			if (m_mmu.getU8(0xFF02) & 0xE0)
			{
				std::cout << "test";
			};
		}

		return 0;
	}

	// Takes in a file path and attempts to load a .gb file into Rose's Cartridge
	int Rose::loadCartridge(std::string p_path)
	{
		// Load into Cartridge construct
		std::ifstream istr;
		std::filebuf* cartridgeBuffer = istr.rdbuf();
		auto errorChk = cartridgeBuffer->open(p_path, std::ios_base::in | std::ios_base::binary);

		if (!errorChk)
		{
			std::cerr << "Could not read file.";
			return 1;
		}

		m_cart.loadIntoCartridge(cartridgeBuffer);
		cartridgeBuffer->close();


		// Load into MMU
		cartridgeBuffer = istr.rdbuf();
		errorChk = cartridgeBuffer->open(p_path, std::ios_base::in | std::ios_base::binary);

		if (!errorChk)
		{
			std::cerr << "Could not read file.";
			return 1;
		}

		m_mmu.loadCartridgeData(cartridgeBuffer);
		cartridgeBuffer->close();

		return 0;
	}

	const MMU& Rose::getMMU() const
	{
		return m_mmu;
	}

	const CPU& Rose::viewCPU() const
	{
		return m_cpu;
	}
}