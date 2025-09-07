#include "timer.h"

namespace rose_core
{
	Timer::Timer(InterruptHandler& p_ih)
		: m_ih(p_ih)
	{
	}

	void Timer::tick()
	{
		if (m_requestInterruptDelayTimer == 1)
		{
			m_requestInterruptDelayTimer--;
			requestInterrupt();
		}
		else if (m_requestInterruptDelayTimer > 1) m_requestInterruptDelayTimer--;

		m_systemCounter++;

		// Check for falling edge at TAC designated bit due to reset and increment TIMA.
		if (m_tac & 0b100) // If TAC (timer control) is enabled
		{
			int bit_shift = 9;
			if ((m_tac & 0b11) != 0) // Calculate bit shift for falling edge detection
				bit_shift -= (4 - (m_tac & 0b11)) * 2;

			if ((m_systemCounter & (0x3FF >> (9 - bit_shift))) == 0) // Falling edge detector
				incrementTIMA();
		}
	}

	u8 Timer::readDIV()
	{
		return m_div;
	}

	void Timer::resetDIV()
	{
		// Check for falling edge at TAC designated bit due to reset and increment TIMA.
		if (m_tac & 0b100) // If TAC (timer control) is enabled
		{
			int bit_shift = 9;
			if ((m_tac & 0b11) != 0) // Calculate bit shift for falling edge detection
				bit_shift -= (4 - (m_tac & 0b11)) * 2;

			if (m_systemCounter & (0b1 << (bit_shift - 1)))
				incrementTIMA();
		}
		
		m_systemCounter = 0;
	}

	u8 Timer::readTIMA()
	{
		return m_tima;
	}

	void Timer::setTIMA(u8 p_value)
	{
		m_tima = p_value;
		if (m_requestInterruptDelayTimer == 4) m_requestInterruptDelayTimer = 0;
	}

	u8 Timer::readTMA()
	{
		return m_tma;
	}

	void Timer::setTMA(u8 p_value)
	{
		m_tma = p_value;
	}

	u8 Timer::readTAC()
	{
		return m_tac;
	}

	void Timer::setTAC(u8 p_value)
	{
		u8 old_tac = m_tac;
		m_tac = p_value;

		// Check for "falling edge" from TAC designated bit to new bit due to TAC update.
		if (m_tac & 0b100) // If new TAC (timer control) is enabled
		{
			int bit_shift_old = 9;
			if ((old_tac & 0b11) != 0) // Calculate bit shift for falling edge detection
				bit_shift_old -= (4 - (old_tac & 0b11)) * 2;

			if (m_systemCounter & (0b1 << (bit_shift_old - 1)))
			{
				int bit_shift_new = 9;
				if ((m_tac & 0b11) != 0)
					bit_shift_new -= (4 - (m_tac & 0b11)) * 2;

				if ((m_systemCounter & (0b1 << (bit_shift_new - 1))) == 0) // Trigger TIMA increase if fall
				{
					incrementTIMA();
				}
			}
		}
		else // If new TAC (timer control) is disabled
		{
			int bit_shift_old = 9;
			if ((old_tac & 0b11) != 0) // Calculate bit shift for falling edge detection
				bit_shift_old -= (4 - (old_tac & 0b11)) * 2;

			if (m_systemCounter & (0b1 << (bit_shift_old - 1)))
			{
				incrementTIMA();
			}
		}
	}

	void Timer::incrementTIMA()
	{
		m_tima++;

		if (m_tima == 0)
			m_requestInterruptDelayTimer = 4;
	}
	
	void Timer::requestInterrupt()
	{
		m_tima = m_tma;
		m_ih.requestInterrupt(TIMER);
	}

}