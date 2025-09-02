#pragma once

#include <fstream>
#include <vector>

#include "../utility/definitions.h"

namespace rose_core
{
	class MMU 
	{
	public:
		MMU();

		int loadCartridgeData(std::filebuf* cartData);

		u16 getU16(u16 address);
		int setU16(u16 address, u16 value);

		u8 getU8(u16 address);
		int setU8(u16 address, u8 value);

		const std::vector<u8>& getMemory() const;
	private:
		std::vector<u8> m_memory; // 0-65535
		
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