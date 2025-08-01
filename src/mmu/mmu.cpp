#include "mmu.h"

namespace mmu
{
	MMU::MMU()
	{
		memory = std::vector<u16>(65536, 0);
	}

	int MMU::loadCartridgeData(std::filebuf* cartData)
	{
		cartData->sgetn((char*)&memory[0], 32768);
		return 0;
	}

}