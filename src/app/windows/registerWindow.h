#pragma once

#include "rose.h"

class RegisterWindow
{
public:
	RegisterWindow(rose::Rose* roseInstance);
	void Draw();
private:
	rose::Rose* roseInstance;
};