#pragma once

#include <fstream>
#include <vector>

#include "../utility/definitions.h"

namespace cartridge
{
	class Cartridge
	{
	public:
		Cartridge();

		void loadIntoCartridge(std::filebuf* cartData);
		std::vector<u8> memory;
	private:
	};
}