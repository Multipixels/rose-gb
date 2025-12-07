#pragma once

#include "rose.h"

class InstructionMenu
{
public:
	InstructionMenu(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};