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
	}

	// Takes in a file path and attempts to load a .gb file into Rose's Cartridge
	int Rose::loadCartridge(std::string path)
	{
		FILE* gbFile;
		gbFile = fopen(path.c_str(), "rb");
		if (gbFile==NULL)
		{
			std::cerr << "Could not read file.";
			return 1;
		}

		fread(cart.memory, 2, 32768, gbFile);
		fclose(gbFile);

		return 0;
	}
}