#include "mmu.h"

namespace mmu
{
	MMU::MMU()
	{
		memory = std::vector<u8>(0x10000, 0);
	}

	int MMU::loadCartridgeData(std::filebuf* cartData)
	{
		cartData->sgetn((char*)&memory[0], 0x8000);
		return 0;
	}

	u16 MMU::getU16(int address)
	{
		if (address > 0xFFFE)
		{
			throw;
		}

		return (memory.at(address) << 8) | memory.at(address + 1);
	}

	int MMU::setU16(int address, u16 value)
	{
		if (address > 0xFFFE)
		{
			throw;
		}
		memory[address] = value >> 8;
		memory[address + 1] = value & 0x00FF;
		return 0;
	}

	u8 MMU::getU8(int address)
	{
		if (address > 0xFFFF)
		{
			throw;
		}

		return memory.at(address);
	}

	int MMU::setU8(int address, u8 value)
	{ 
		if (address > 0xFFFF)
		{
			throw; // TODO: replace with actual error checking
		}
		
		memory[address] = value;
		return 0;
	}

}