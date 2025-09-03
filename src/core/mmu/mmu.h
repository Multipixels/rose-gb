#pragma once

#include <fstream>
#include <vector>

#include "../interruptHandler/interruptHandler.h"
#include "../timer/timer.h"
#include "../utility/definitions.h"

namespace rose_core
{
	class MMU 
	{
	public:
		MMU(InterruptHandler& ih, Timer& timer);

		int loadCartridgeData(std::filebuf* cartData);

		u16 getU16(u16 address);
		int setU16(u16 address, u16 value);

		u8 getU8(u16 address);
		int setU8(u16 address, u8 value);

		const std::vector<u8>& getMemory() const;
	private:
		InterruptHandler& m_ih;
		Timer& m_timer;

		std::vector<u8> m_memory;
	};
}