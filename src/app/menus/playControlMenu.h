#pragma once

#include "rose.h"

class PlayControlMenu
{
public:
	PlayControlMenu(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};