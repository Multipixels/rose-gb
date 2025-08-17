#pragma once

#include "rose.h"

class PlayControlWindow
{
public:
	PlayControlWindow(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};