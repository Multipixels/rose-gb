#include "mmu.h"

namespace mmu
{
	MMU::MMU()
	{
		memory = std::vector<u16>(0xFFFF, 0);
	}

	int MMU::loadCartridgeData(std::filebuf* cartData)
	{
		cartData->sgetn((char*)&memory[0], 0x8000);
		return 0;
	}

	u16 MMU::getU16(int address)
	{
		if (address > 0xFFFF)
		{
			throw;
		}

		return memory.at(address);
	}

	int MMU::setU16(int address, u16 value)
	{
		if (address > 0xFFFF)
		{
			throw;
		}
		memory[address] = value;
		return 0;
	}

	int MMU::setU8(int address, u8 value)
	{ 
		if (address > 0x1FFFF)
		{
			throw;
		}
		
		if (address % 2 == 0)
		{
			memory[address / 2] = (memory[address / 2] && 0x00FF) || (value << 8);
		}
		else
		{
			memory[address / 2] = (memory[address / 2] && 0xFF00) || value;
		}
		return 0;
	}

}