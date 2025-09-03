#include "mmu.h"

namespace rose_core
{
	MMU::MMU(Timer& timer)
		: m_timer(timer)
	{
		m_memory = std::vector<u8>(0x10000, 0);
	}

	int MMU::loadCartridgeData(std::filebuf* p_cartData)
	{
		p_cartData->sgetn((char*)&m_memory[0], 0x8000);
		return 0;
	}

	u8 MMU::getU8(u16 p_address)
	{
		// Special addresses
		switch (p_address)
		{
		case 0xFF04: // DIV: Divider Register
			return m_timer.readDIV();
		case 0xFF05: // TIMA: Time counter
			return m_timer.readTIMA();
		case 0xFF06: // TMA: Time counter
			return m_timer.readTMA();
		case 0xFF07: // TAC: Timer control
			return m_timer.readTAC();
		default:
			return m_memory.at(p_address);
		}
	}

	int MMU::setU8(u16 p_address, u8 p_value)
	{ 
		// Special addresses
		switch (p_address)
		{
		case 0xFF04: // DIV: Divider Register
			m_timer.resetDIV();
			break;
		case 0xFF05: // TIMA: Time counter
			m_timer.setTIMA(p_value);
			break;
		case 0xFF06: // TMA: Time counter
			m_timer.setTMA(p_value);
			break;
		case 0xFF07: // TAC: Timer control
			m_timer.setTAC(p_value);
			break;
		default:
			m_memory[p_address] = p_value;
			break;
		}

		return 0;
	}

	const std::vector<u8>& MMU::getMemory() const
	{
		return m_memory;
	}

}