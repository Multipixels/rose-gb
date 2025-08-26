#pragma once

#include "rose.h"

class InstructionWindow
{
public:
	InstructionWindow(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};