#pragma once

#include <array>
#include <string>

#include "cartridge/cartridge.h"
#include "cpu/cpu.h"
#include "mmu/mmu.h"
#include "timer/timer.h"

namespace rose_core
{
	class Rose
	{
	public:
		Rose();

		int loadGame();
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

	private:
		Cartridge m_cart;
		CPU m_cpu;
		MMU m_mmu;
		Timer m_timer;

		bool m_paused = true;

		// TODO: Figure out a better way/location to store instruction and game state history
		std::array<u16, 10> m_tempInstrHistory{};
		int m_tempInstrHistoryHead = 0;
		int m_tempInstrRan = 0;
	};
}