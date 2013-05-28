#include "StdAfx.h"
#include "ClockTimer.h"

ClockTimer::ClockTimer(void)
{
	m_testValue = 1;
}

ClockTimer::~ClockTimer(void)
{
}

int ClockTimer::GetHour()
{
	return m_testValue;
}

int ClockTimer::GetMinute()
{
	return m_testValue+2;
}

int ClockTimer::GetSecond()
{
	return m_testValue+5;
}

void ClockTimer::Tick()
{
	m_testValue += 1;
	if (m_testValue%5 == 0)
	{
		Notify();
	}
}