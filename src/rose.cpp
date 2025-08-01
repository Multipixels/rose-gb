#include <fstream>
#include <iostream>

#include "rose.h"

namespace rose
{
	Rose::Rose() 
	{
		cart = cartridge::Cartridge();
		cpu = cpu::CPU();
		mmu = mmu::MMU();
	}

	// Loads the cartridge and boots up the Game Boy
	int Rose::runGame()
	{
		loadCartridge("../tests/01-special.gb");
		return 0;
	}

	// Takes in a file path and attempts to load a .gb file into Rose's Cartridge
	int Rose::loadCartridge(std::string path)
	{
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

		return 0;
	}
}