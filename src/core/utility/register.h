#pragma once

#include "definitions.h"

class Register
{
public:
	u16 getValue();
	u8 getLeftValue();
	u8 getRightValue();

	void setValue(u16 p_value);
	void setLeftValue(u8 p_value);
	void setRightValue(u8 p_value);
private:
	u16 m_value;
};