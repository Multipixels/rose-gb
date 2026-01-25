#include <fstream>
#include <iostream>

#include "rose.h"

namespace rose_core
{
	Rose::Rose() 
		: m_ih(InterruptHandler())
		, m_cart(Cartridge())
		, m_timer(Timer(m_ih))
		, m_mmu(MMU(m_ih, m_timer))
		, m_cpu(CPU(m_ih, m_mmu))
	{
	}

	int Rose::loadGame(std::string p_str)
	{
		//if (loadCartridge("../resources/blargg/cpu_instrs/01-special.gb") == 1)
		if (loadCartridge(p_str) == 1)
		{
			return 1;
		};
		return 0;
	}

	// Loads the cartridge and boots up the Game Boy
	int Rose::runGame()
	{
		while (true)
		{
			if (!m_paused)
			{
				stepForward();
			}
		}

		return 0;
	}

	// Executes a single instruction
	int Rose::stepForward()
	{
		while (true)
		{
			bool timeToEscape = m_cpu.tick();
			for (int i = 0; i < 4; i++) m_timer.tick();
			if (timeToEscape) break;
		}
		m_instructionHistory.enqueue(m_cpu.viewRegisters().programCounter - 1);
		m_instructionsRan++;
		return 0;
	}

	int Rose::togglePause()
	{
		m_paused = !m_paused;
		return 0;
	}

	// Takes in a file path and attempts to load a .gb file into Rose's Cartridge
	int Rose::loadCartridge(std::string p_path)
	{
		// Load into Cartridge construct
		std::ifstream istr;
		std::filebuf* cartridgeBuffer = istr.rdbuf();
		auto errorChk = cartridgeBuffer->open(p_path, std::ios_base::in | std::ios_base::binary);

		if (!errorChk)
		{
			std::cerr << "Could not read file.";
			return 1;
		}

		m_cart.loadIntoCartridge(cartridgeBuffer);
		cartridgeBuffer->close();


		// Load into MMU
		cartridgeBuffer = istr.rdbuf();
		errorChk = cartridgeBuffer->open(p_path, std::ios_base::in | std::ios_base::binary);

		if (!errorChk)
		{
			std::cerr << "Could not read file.";
			return 1;
		}

		m_mmu.loadCartridgeData(cartridgeBuffer);
		cartridgeBuffer->close();

		return 0;
	}

	const MMU& Rose::viewMMU() const
	{
		return m_mmu;
	}

	const CPU& Rose::viewCPU() const
	{
		return m_cpu;
	}

	const CircularBuffer<u16, 16>& Rose::viewInstructionHistory() const
	{
		return m_instructionHistory;
	}

	const int Rose::viewInstructionsRan() const
	{
		return m_instructionsRan;
	}

	u8 Rose::readConsole()
	{
		return m_mmu.getU8(0xFF01);
	}

	u8 Rose::readConsole(u16 p_addr)
	{
		return m_mmu.getU8(p_addr);
	}

	int Rose::tick()
	{
		m_cpu.tick();
		for (int i = 0; i < 4; i++) m_timer.tick();
		return 0;
	}
}