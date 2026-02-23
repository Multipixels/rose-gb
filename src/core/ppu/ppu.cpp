#include <iostream>

#include "ppu.h"

namespace rose_core
{
	PPU::PPU(InterruptHandler& p_ih)
		: m_ih(p_ih)
	{
		m_frameBuffer = std::array<u8, PPU::WIDTH* PPU::HEIGHT>{};
	}

	void PPU::tick()
	{
		if (!isPPUEnabled())
		{
			return;
		}

		switch (m_mode)
		{ 
		case 2: // Mode 2: OAM Cycle (dots 0-79, 80 dots)
			if (m_modeDot >= 79)
			{
				m_mode = 3;
				m_modeDot = 0;
			}
			else
			{
				m_modeDot++;
			}
			m_lineDot++;
			break;
		case 3: // Mode 3: Drawing Pixels (dots 80 to dots 251-368, 172 to 289 dots)
			if (m_modeDot >= 171 && !m_mode3Penalty)
			{
				m_mode = 0;
				m_mode3Penalty = false;
				m_modeDot = 0;
			}

			// If we reach dot 368 (max we can stay in mode 3) and we haven't finished drawing pixels
			else if (m_lineDot >= 368 && m_modeDot <= 171 && !m_mode3Penalty)
			{
				m_mode = 0;
				m_mode3Penalty = false;
				m_modeDot = 0;
			}

			else if (!m_mode3Penalty)
			{
				m_modeDot++;
			}

			m_lineDot++;
			break;
		case 0: // Mode 0: HBlank (from dots 252-369 to 455, 87 to 204 dots)
			if (m_lineDot >= 455)
			{
				if (m_ly >= 143)
				{
					m_mode = 1;
					m_modeDot = 0;
					m_lineDot++;
					m_ly++;
					checkLYC();
					m_frameReady = true;
					m_ih.requestInterrupt(VBLANK);
				}
				else
				{
					m_mode = 2;
					m_modeDot = 0;
					m_lineDot = 0;
					m_ly++;
					checkLYC();
					break;
				}
			}
			m_lineDot++;
			break;
		case 1: // Mode 1: VBlank (from lines 144-153, 456 dots each)
			if (m_modeDot >= 455)
			{
				if (m_ly >= 153)
				{
					m_mode = 2;
					m_modeDot = 0;
					m_lineDot = 0;
					m_ly = 0;
					checkLYC();
					break;
				}
				else
				{
					m_modeDot = 0;
					m_lineDot++;
					m_ly++;
					checkLYC();
					break;
				}
			}
			m_modeDot++;
			break;
		default:
			throw;
		}
	}

	const bool PPU::isFrameReady() const
	{
		return m_frameReady;
	}

	const std::array<u8, PPU::WIDTH * PPU::HEIGHT>& PPU::getFrameBuffer() const
	{
		return m_frameBuffer;
	}

	const bool PPU::isPPUEnabled() const
	{
		return (bool)(m_lcdc & 0x10000000);
	}

	const u8 PPU::readLCDC() const
	{
		return m_lcdc;
	}

	const u8 PPU::readSTAT() const
	{
		u8 stat = 0x80;							// bit 7: always 1
		stat |= m_stat & 0b01111000;			// bit 3-6: store stat values
		stat |= (u8)(m_lyc == m_ly) << 2;		// bit 2: LYC == LY
		if(isPPUEnabled()) stat |= (u8)m_mode;	// bit 0-1: PPU mode
		return stat;
	}

	const u8 PPU::readSCY() const
	{
		return m_scy;
	}

	const u8 PPU::readSCX() const
	{
		return m_scx;
	}

	const u8 PPU::readLY() const 
	{ 
		return m_ly;
	}

	const u8 PPU::readLYC() const
	{
		return m_lyc;
	}

	const u8 PPU::readBGP() const
	{
		return m_bgp;
	}

	const u8 PPU::readOBP0() const
	{
		return m_obp0;
	}

	const u8 PPU::readOBP1() const
	{
		return m_obp1;
	}

	const u8 PPU::readWY() const
	{
		return m_wy;
	}

	const u8 PPU::readWX() const
	{
		return m_wx;
	}

	void PPU::setLCDC(u8 p_value)
	{
		m_lcdc = p_value;
	}

	void PPU::setSTAT(u8 p_value)
	{
		u8 prev_stat = m_stat;

		m_stat = 0x80;					// bit 7: always 1
		m_stat |= p_value & 0b01111000;		// bit 3-6: store stat values
		m_stat |= (u8)(m_lyc == m_ly) << 2;	// bit 2: LYC == LY
		m_stat |= (u8)m_mode;				// bit 0-1: PPU mode

		if (   ((prev_stat & (1 << 6)) == 0) && ((m_stat & (1 << 6)) == 1)   )
		{
			m_ih.requestInterrupt(STAT);
		}
	}

	void PPU::setSCY(u8 p_value)
	{
		m_scy = p_value;
	}

	void PPU::setSCX(u8 p_value)
	{
		m_scx = p_value;
	}

	void PPU::setLY(u8 p_value)  // Read-only
	{ 
		throw; 
	}
	
	void PPU::setLYC(u8 p_value) 
	{
		m_lyc = p_value;
		if (isPPUEnabled()) checkLYC();
	}

	void PPU::setBGP(u8 p_value)
	{
		m_bgp = p_value;
	}

	void PPU::setOBP0(u8 p_value)
	{
		m_obp0 = p_value;
	}

	void PPU::setOBP1(u8 p_value)
	{
		m_obp1 = p_value;
	}

	void PPU::setWY(u8 p_value)
	{
		m_wy = p_value;
	}

	void PPU::setWX(u8 p_value)
	{
		m_wx = p_value;
	}

	void PPU::createMode3Penalty()
	{
		m_mode3Penalty = true;
	}

	void PPU::checkLYC()
	{
		bool lycCondition = (m_ly == m_lyc) && (m_stat & (1 << 6));

		if (lycCondition && !m_lycPrevious)
		{
			m_ih.requestInterrupt(STAT);
		}

		m_lycPrevious = lycCondition;
	}
}