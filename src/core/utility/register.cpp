#include "register.h"


u16 Register::getValue()
{
	return m_value;
}

u8 Register::getLeftValue()
{
	return m_value >> 8;
}

u8 Register::getRightValue()
{
	return m_value & 0x00FF;
}

void Register::setValue(u16 p_value)
{
	m_value = p_value;
}

void Register::setLeftValue(u8 p_value)
{
	m_value = (m_value & 0x00FF) | (p_value << 8);
}

void Register::setRightValue(u8 p_value)
{
	m_value = (m_value & 0xFF00) | p_value;
}