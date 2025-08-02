#include "cartridge.h"

namespace cartridge
{
	Cartridge::Cartridge()
	{
		memory = std::vector<u8>(65536, 0); // May change, depends on header: https://gbdev.io/pandocs/The_Cartridge_Header.html#0148--rom-size
	}

	int Cartridge::loadIntoCartridge(std::filebuf* cartData)
	{
		cartData->sgetn((char*)&memory[0], memory.size() * sizeof(memory[0]));
		return 0;
	}
}