#include "interruptHandler.h"

namespace rose_core
{
	void InterruptHandler::requestInterrupt(InterruptType it)
	{
		m_if |= 0b1 << (u8)it;
	}

	void InterruptHandler::setIME(bool p_value)
	{ 
		m_ime = p_value;
		if (!p_value)
		{
			m_setIMENextCycle = false;
		}
	}

	void InterruptHandler::setIMENextCycle()
	{
		m_setIMENextCycle = true;
	}

	void InterruptHandler::setIMEIfNextCycle()
	{
		if(m_setIMENextCycle) setIME(true);
	}

	Flag InterruptHandler::readIME()
	{
		return m_ime;
	}

	u8 InterruptHandler::readIE()
	{
		return m_ie;
	}

	void InterruptHandler::setIE(u8 p_value)
	{
		m_ie = p_value;
	}

	u8 InterruptHandler::readIF()
	{
		return m_if;
	}

	void InterruptHandler::setIF(u8 p_value)
	{
		m_if = p_value | 0xE0;
	}

}