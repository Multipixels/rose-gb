#pragma once

#include "../utility/definitions.h"

namespace rose_core
{
	class InterruptHandler
	{
	public:
		void requestInterrupt(InterruptType it);

		void setIME(bool value);
		void setIMENextCycle();
		void setIMEIfNextCycle();

		u8 readIE();
		void setIE(u8 value);

		u8 readIF();
		void setIF(u8 value);

	private:
		// Can only be set, not read. When set, set with a delay of 1 instruction.
		Flag m_ime = false;
		bool m_setIMENextCycle = false; // Set in EI

		Register8 m_ie = 0x00;
		Register8 m_if = 0x00;
	};
}