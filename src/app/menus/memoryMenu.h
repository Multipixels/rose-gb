#pragma once

#include "rose.h"

class MemoryMenu
{
public:
	MemoryMenu(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};