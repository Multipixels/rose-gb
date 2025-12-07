#pragma once

#include "rose.h"

class RegisterMenu
{
public:
	RegisterMenu(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};