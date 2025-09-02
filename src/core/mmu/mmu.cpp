#include "mmu.h"

namespace rose_core
{
	MMU::MMU()
	{
		m_memory = std::vector<u8>(0x10000, 0);
	}

	int MMU::loadCartridgeData(std::filebuf* p_cartData)
	{
		p_cartData->sgetn((char*)&m_memory[0], 0x8000);
		return 0;
	}

	u16 MMU::getU16(u16 p_address)
	{
		if (p_address > 0xFFFE)
		{
			throw;
		}

		return (m_memory.at(p_address + 1) << 8) | m_memory.at(p_address);
	}

	int MMU::setU16(u16 p_address, u16 p_value)
	{
		if (p_address > 0xFFFE)
		{
			throw;
		}
		m_memory[p_address] = p_value >> 8;
		m_memory[p_address + 1] = p_value & 0x00FF;
		return 0;
	}

	u8 MMU::getU8(u16 p_address)
	{
		if (p_address > 0xFFFF)
		{
			throw;
		}

		return m_memory.at(p_address);
	}

	int MMU::setU8(u16 p_address, u8 p_value)
	{ 
		if (p_address > 0xFFFF)
		{
			throw; // TODO: replace with actual error checking
		}
		
		m_memory[p_address] = p_value;
		return 0;
	}

	const std::vector<u8>& MMU::getMemory() const
	{
		return m_memory;
	}

}