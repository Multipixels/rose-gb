#pragma once

#include "../mmu/mmu.h"
#include "../utility/definitions.h"

namespace rose_core
{
	/*                    Hz
	00	256 M-cycles	4096	
	01	4 M-cycles		262144
	10	16 M-cycles		65536
	11	64 M-cycles		16384
	
	DIV increments every 64 M-Cycles, 0xFF04
	TIMA increments based on TAC's clock selector, 0xFF05
	TMA: when TIMA overflows, reset to TMA and request interrupt.
		If a TMA write is executed on the same M-cycle as the content of TMA is transferred to TIMA due to a timer overflow, the old value is transferred to TIMA.
	*/

	class Timer
	{
	public:
		Timer();

		void tick();

		u8 readDIV();
		void resetDIV();

		u8 readTIMA();
		void setTIMA(u8 value);

		u8 readTMA();
		void setTMA(u8 value);

		u8 readTAC();
		void setTAC(u8 value);
	private:
		Register16 m_systemCounter = 0xAB00;

		Register8& m_div = *((Register8*)(&m_systemCounter) + 1);
		Register8 m_tima = 0x00;
		Register8 m_tma = 0x00;
		Register8 m_tac = 0xF8;

		void incrementTIMA();
	};
}