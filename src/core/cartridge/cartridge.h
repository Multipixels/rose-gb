#pragma once

#include <fstream>
#include <vector>

#include "../utility/definitions.h"

namespace rose_core
{
	class Cartridge
	{
	public:
		Cartridge();

		int loadIntoCartridge(std::filebuf* cartData);
	private:
		std::vector<u8> m_memory;
	};
}