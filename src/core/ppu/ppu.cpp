#include "ppu.h"

namespace rose_core
{
	PPU::PPU()
	{
		m_frameBuffer = std::array<u8, PPU::WIDTH* PPU::HEIGHT>{};
	}

	void PPU::tick()
	{
		// On each dot during mode 3 either 
		//	- the PPU outputs a pixel; or
		//	- the fetcher is stalling the FIFOs.

		// LYC == LC Check
			// If equal, the LYC = LC flag in the STAT register is set.
			// If enabled, request STAT interrupt.

		m_dot++;
	}

	const bool PPU::isFrameReady() const
	{
		return m_frameReady;
	}

	const std::array<u8, PPU::WIDTH * PPU::HEIGHT>& PPU::getFrameBuffer() const
	{
		return m_frameBuffer;
	}

	const u8 PPU::readLCDC() const
	{
		return m_lcdc;
	}

	const u8 PPU::readSTAT() const
	{
		u8 stat = 0x80;					// bit 7: always 1
		stat |= m_stat & 0b01111000;		// bit 3-6: store stat values
		stat |= (u8)(m_lyc == m_ly) << 2;	// bit 2: LYC == LY
		stat |= (u8)m_mode;					// bit 0-1: PPU mode
		return m_stat;
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
		u8 m_stat = 0x80;					// bit 7: always 1
		m_stat |= p_value & 0b01111000;		// bit 3-6: store stat values
		m_stat |= (u8)(m_lyc == m_ly) << 2;	// bit 2: LYC == LY
		m_stat |= (u8)m_mode;				// bit 0-1: PPU mode

		// TODO: Trigger STAT interrupt when any of bits 3-6 go from 0 to 1. 
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
}