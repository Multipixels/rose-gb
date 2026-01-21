#pragma once

#include <array>
#include <string>

#include "cartridge/cartridge.h"
#include "cpu/cpu.h"
#include "mmu/mmu.h"
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
		int tick();
		int stepForward();
		int togglePause();
		int loadCartridge(std::string path);

		const MMU& viewMMU() const;
		const CPU& viewCPU() const;

		const std::array<u16, 10>& tempViewInstrHistory() const;
		int tempViewInstrHistoryHead();
		int tempViewInstrRan();
		u8 tempReadConsole();
		u8 tempReadConsole(u16 p_addr);

	private:
		Cartridge m_cart;
		CPU m_cpu;
		InterruptHandler m_ih;
		MMU m_mmu;
		Timer m_timer;

		bool m_paused = true;

		CircularBuffer<u16, 100> m_instructionHistory;

		// TODO: Figure out a better way/location to store instruction and game state history
		std::array<u16, 10> m_tempInstrHistory{};
		int m_tempInstrHistoryHead = 0;
		int m_tempInstrRan = 0;
	};
}