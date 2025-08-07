#pragma once

#include "rose.h"

class MemoryWindow
{
public:
	MemoryWindow(rose::Rose* roseInstance);
	void Draw();
private:
	rose::Rose* roseInstance;
};