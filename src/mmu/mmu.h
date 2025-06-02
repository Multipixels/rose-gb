#pragma once

#include <vector>

#include "../utility/definitions.h"

namespace mmu 
{
	class MMU 
	{
	public:
		u16 memory[65536];
	private:
		/*u16* bankZero = &memory;
		u16* bankOne = &memory[16384];
		u16* vRAM = &memory[32768];
		u16* externalRAM = &memory[40960];
		u16* wRAMZero = &memory[49152];
		u16* wRAMOne = &memory[53248];
		u16* echoRAM = &memory[57344];
		u16* oam = &memory[65024];
		u16* ioRegisters = &memory[65280];
		u16* hRAM = &memory[65408];
		u16* ieRegister = &memory[65535];*/
	};
}