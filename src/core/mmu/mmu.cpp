#include "mmu.h"

#include <iostream>

namespace rose_core
{
	MMU::MMU(InterruptHandler& p_ih, Timer& p_timer, PPU& p_ppu)
		: m_ih(p_ih), m_timer(p_timer), m_ppu(p_ppu)
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
		case 0xFF02: // SC (Temporary for Mooneye)
			return 0xFF;
		case 0xFF04: // DIV: Divider Register
			return m_timer.readDIV();
		case 0xFF05: // TIMA: Time counter
			return m_timer.readTIMA();
		case 0xFF06: // TMA: Time counter
			return m_timer.readTMA();
		case 0xFF07: // TAC: Timer control
			return m_timer.readTAC();
		case 0xFF0F: // IF: Interrupt Flag
			return m_ih.readIF();
		case 0xFF40: // LCDC: LCD Control
			return m_ppu.readLCDC();
		case 0xFF41: // STAT: LCD Status
		{
			u8 val = m_ppu.readSTAT();
			std::cout << (int)val << std::endl;
			return val;
		}
			return m_ppu.readSTAT();
		case 0xFF42: // SCY: Viewport Y Position
			return m_ppu.readSCY();
		case 0xFF43: // SCX: Viewport X Position
			return m_ppu.readSCX();
		case 0xFF44: // LY: LCD Y Position
			return m_ppu.readLY();
		case 0xFF45: // LYC: LY Compare
			return m_ppu.readLYC();
		case 0xFF47: // BGP: BG Palette Data
			return m_ppu.readBGP();
		case 0xFF48: // OBP0: OBJ Palette 0 Data
			return m_ppu.readOBP0();
		case 0xFF49: // OBP1: OBJ Palette 1 Data
			return m_ppu.readOBP1();
		case 0xFF4A: // WY: Window Y Position
			return m_ppu.readWY();
		case 0xFF4B: // WX: Window X Position
			return m_ppu.readWX();
		case 0xFFFF: // IE: Interrupt Enable
			return m_ih.readIE();
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
		case 0xFF0F: // IF: Interrupt Flag
			m_ih.setIF(p_value);
			break;
		case 0xFF40: // LCDC: LCD Control
			m_ppu.setLCDC(p_value);
			break;
		case 0xFF41: // STAT: LCD Status
			m_ppu.setSTAT(p_value);
			break;
		case 0xFF42: // SCY: Viewport Y Position
			m_ppu.setSCY(p_value);
			break;
		case 0xFF43: // SCX: Viewport X Position
			m_ppu.setSCX(p_value);
			break;
		case 0xFF44: // LY: LCD Y Position
			m_ppu.setLY(p_value);
			break;
		case 0xFF45: // LYC: LY Compare
			m_ppu.setLYC(p_value);
			break;
		case 0xFF47: // BGP: BG Palette Data
			m_ppu.setBGP(p_value);
			break;
		case 0xFF48: // OBP0: OBJ Palette 0 Data
			m_ppu.setOBP0(p_value);
			break;
		case 0xFF49: // OBP1: OBJ Palette 1 Data
			m_ppu.setOBP1(p_value);
			break;
		case 0xFF4A: // WY: Window Y Position
			m_ppu.setWY(p_value);
			break;
		case 0xFF4B: // WX: Window X Position
			m_ppu.setWX(p_value);
			break;
		case 0xFFFF: // IE: Interrupt Enable
			m_ih.setIE(p_value);
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