#pragma once

#include "rose.h"

class RegisterWindow
{
public:
	RegisterWindow(rose_core::Rose* roseInstance);
	void Draw();
private:
	rose_core::Rose* roseInstance;
};