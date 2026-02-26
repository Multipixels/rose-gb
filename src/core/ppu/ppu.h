#pragma once

#include <array>

#include "../interruptHandler/interruptHandler.h"
#include "../utility/definitions.h"

namespace rose_core
{
	class PPU
	{
	public:
		static constexpr int WIDTH = 160;
		static constexpr int HEIGHT = 144;

		PPU(InterruptHandler& ih);

		void tick();

		const bool isFrameReady() const;
		const std::array<u8, WIDTH * HEIGHT>& getFrameBuffer() const;

		const bool isPPUEnabled() const;

		const u8 readLCDC() const;
		const u8 readSTAT() const;
		const u8 readSCY() const;
		const u8 readSCX() const;
		const u8 readLY() const;
		const u8 readLYC() const;
		const u8 readBGP() const;
		const u8 readOBP0() const;
		const u8 readOBP1() const;
		const u8 readWY() const;
		const u8 readWX() const;

		void setLCDC(u8 value);
		void setSTAT(u8 value);
		void setSCY(u8 value);
		void setSCX(u8 value);
		void setLY(u8 value);
		void setLYC(u8 value);
		void setBGP(u8 value);
		void setOBP0(u8 value);
		void setOBP1(u8 value);
		void setWY(u8 value);
		void setWX(u8 value);

		void createMode3Penalty();
	private:
		InterruptHandler& m_ih;

		// 4560 dots per line, 70224 per fram
		unsigned int m_lineDot = 0;
		unsigned int m_modeDot = 0;
		/*
		Mode 2: OAM Cycle (dots 0-79, 80 dots)
		Mode 3: Drawing Pixels (dots 80 to dots 251-368, 172 to 289 dots)
		Mode 0: HBlank (from dots 252-369 to 455, 87 to 204 dots)
		Mode 1: VBlank (from dots 456 to 5015, 4560 dots)
		*/
		unsigned int m_mode = 2;
		bool m_mode3Penalty = false;

		bool m_frameReady = false;
		std::array<u8, WIDTH * HEIGHT> m_frameBuffer;

		// Registers
		u8 m_lcdc = 0x91;	// 0xFF40 - LCD Control
		u8 m_stat = 0x85;	// 0xFF41 - LCD Status
		u8 m_scy = 0x00;	// 0xFF42 - Viewport Y Position
		u8 m_scx = 0x00;	// 0xFF43 - Viewport X Position
		u8 m_ly = 0x00;		// 0xFF44 - LCD Y Position
		u8 m_lyc = 0x91;	// 0xFF45 - LY Compare
		u8 m_bgp = 0xFC;	// 0xFF47 - BG Palette Data
		u8 m_obp0 = 0;		// 0xFF48 - OBJ Palette 0 Data - Most often 0x00 or 0xFF but unreliable
		u8 m_obp1 = 0;		// 0xFF49 - OBJ Palette 1 Data - Most often 0x00 or 0xFF but unreliable
		u8 m_wy = 0x00;		// 0xFF4A - Window Y Position
		u8 m_wx = 0x00;		// 0xFF4B - Window X Position + 7

		void checkLYC();

		void setMode(int mode);
		bool m_setMode2NextTick = true;

		void checkStatIrqLine();
		bool m_statIrqLine = false;
	};
}