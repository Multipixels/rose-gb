#pragma once

#include "rose.h"

class MemoryWindow
{
public:
	MemoryWindow(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};