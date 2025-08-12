#include "cartridge.h"

namespace rose_core
{
	Cartridge::Cartridge()
	{
		m_memory = std::vector<u8>(65536, 0); // May change, depends on header: https://gbdev.io/pandocs/The_Cartridge_Header.html#0148--rom-size
	}

	int Cartridge::loadIntoCartridge(std::filebuf* cartData)
	{
		cartData->sgetn((char*)&m_memory[0], m_memory.size() * sizeof(m_memory[0]));
		return 0;
	}
}