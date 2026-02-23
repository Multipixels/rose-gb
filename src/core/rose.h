#pragma once

#include <array>
#include <string>

#include "cartridge/cartridge.h"
#include "cpu/cpu.h"
#include "mmu/mmu.h"
#include "ppu/ppu.h"
#include "timer/timer.h"
#include "utility/types/circular_buffer.h"

namespace rose_core
{
	class Rose
	{
	public:
		Rose();

		int loadGame(std::string p_str);
		int runGame();
		int stepForward();
		int togglePause();
		int loadCartridge(std::string path);

		const MMU& viewMMU() const;
		const CPU& viewCPU() const;
		const CircularBuffer<u16, 16>& viewInstructionHistory() const;

		const int viewInstructionsRan() const;

		u8 readConsole();
		u8 readConsole(u16 p_addr);

	private:
		int tick();

		Cartridge m_cart;
		CPU m_cpu;
		InterruptHandler m_ih;
		MMU m_mmu;
		PPU m_ppu;
		Timer m_timer;

		CircularBuffer<u16, 16> m_instructionHistory;
		unsigned int m_instructionsRan = 0;
		bool m_paused = true;
	};
}