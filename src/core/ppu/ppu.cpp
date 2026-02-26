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
		if (m_setMode2NextTick)
		{
			setMode(2);
			m_setMode2NextTick = false;
		}

		if (!isPPUEnabled())
		{
			return;
		}

		m_lineDot++;
		m_modeDot++;

		if (m_ly < 144)
		{
			// Mode 2: OAM Cycle (dots 0-79, 80 dots)
			if (m_lineDot == 80)
			{
				setMode(3);
				m_modeDot = 0;
			}

			// Mode 3: Drawing Pixels (dots 80 to dots 251-368, 172 to 289 dots)
			if (m_lineDot == 252)
			{
				setMode(0);
				m_modeDot = 0;
			}

			// Mode 0: HBlank (from dots 252-369 to 455, 87 to 204 dots)
			if (m_lineDot == 456)
			{
				m_modeDot = 0;
				m_lineDot = 0;
				m_ly++;
				if (m_ly == 144)
				{
					setMode(1);
					m_ih.requestInterrupt(VBLANK);
				}
				else
				{
					setMode(2);
				}
				checkLYC();
			}
		}
		else
		{
			// Mode 1: VBlank (from lines 144-153, 456 dots each)
			if (m_modeDot == 456)
			{
				m_ly++;
				m_modeDot = 0;
				m_lineDot = 0;

				if (m_ly == 154)
				{
					m_ly = 0;
					setMode(2);
				}

				checkLYC();
			}
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
		return (bool)(m_lcdc & 0b10000000);
	}	

	const u8 PPU::readLCDC() const
	{
		return m_lcdc;
	}

	const u8 PPU::readSTAT() const
	{
		u8 stat = m_stat & 0b11111100;
		if (isPPUEnabled()) stat |= m_mode;
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
		bool ppuEnabled0 = m_lcdc & 0x80;
		bool ppuEnabled1 = p_value & 0x80;
		m_lcdc = p_value;

		if (!ppuEnabled0 && ppuEnabled1)
		{
			checkLYC();
		}

		if (ppuEnabled0 && !ppuEnabled1)
		{
			m_ly = 0;
			m_mode = 0;
			m_lineDot = 0;
			m_modeDot = 0;
		}
	}

	void PPU::setSTAT(u8 p_value)
	{
		u8 prev_stat = m_stat;

		m_stat = 0x80;						// bit 7: always 1
		m_stat |= p_value & 0b01111000;		// bit 3-6: store stat values
		m_stat |= (u8)(m_lyc == m_ly) << 2;	// bit 2: LYC == LY
		m_stat |= (u8)m_mode;				// bit 0-1: PPU mode

		bool lycEnable0 = prev_stat & 0x40;
		bool lycEnable1 = m_stat & 0x40;
		if (!lycEnable0 && lycEnable1)
		{
			checkLYC();
		}
		else
		{
			checkStatIrqLine();
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
		m_stat = (m_stat & 0b11111011) | ((m_lyc == m_ly) << 2);

		checkStatIrqLine();
	}

	void PPU::setMode(int p_mode)
	{
		if (m_mode == p_mode) return;

		m_mode = p_mode;
		m_stat = (m_stat & 0b11111100) | m_mode;

		checkStatIrqLine();
	}

	void PPU::checkStatIrqLine()
	{
		bool currentStatIrqLine = 
			( ((m_stat & 0b11) == 0) && (m_stat & 0b1000)   ) ||
			( ((m_stat & 0b11) == 1) && (m_stat & 0b10000)  ) ||
			( ((m_stat & 0b11) == 2) && (m_stat & 0b100000) ) ||
			(  (m_stat & 0b100)      && (m_stat & 0b1000000));

		if (!m_statIrqLine && currentStatIrqLine)
		{
			m_ih.requestInterrupt(STAT);
		}

		m_statIrqLine = currentStatIrqLine;
	}
}