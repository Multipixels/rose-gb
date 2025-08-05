#include <fstream>
#include <iostream>

#include "rose.h"

namespace rose
{
	Rose::Rose() 
		: cart(cartridge::Cartridge())
		, mmu(mmu::MMU())
		, cpu(cpu::CPU(&mmu))
	{
	}

	// Loads the cartridge and boots up the Game Boy
	int Rose::runGame()
	{
		if (loadCartridge("../resources/blargg/cpu_instrs/01-special.gb") == 1) 
		{
			return 1;
		};

		while (true)
		{
			cpu.executeInstruction();
			if (mmu.getU8(0xFF02) & 0xE0)
			{
				std::cout << "test";
			};
		}

		return 0;
	}

	// Takes in a file path and attempts to load a .gb file into Rose's Cartridge
	int Rose::loadCartridge(std::string path)
	{
		// Load into Cartridge construct
		std::ifstream istr;
		std::filebuf* cartridgeBuffer = istr.rdbuf();
		auto errorChk = cartridgeBuffer->open(path, std::ios_base::in | std::ios_base::binary);

		if (!errorChk)
		{
			std::cerr << "Could not read file.";
			return 1;
		}

		cart.loadIntoCartridge(cartridgeBuffer);
		cartridgeBuffer->close();


		// Load into MMU
		cartridgeBuffer = istr.rdbuf();
		errorChk = cartridgeBuffer->open(path, std::ios_base::in | std::ios_base::binary);

		if (!errorChk)
		{
			std::cerr << "Could not read file.";
			return 1;
		}

		mmu.loadCartridgeData(cartridgeBuffer);
		cartridgeBuffer->close();

		return 0;
	}
}