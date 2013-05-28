#include "StdAfx.h"
#include "AnalogClock.h"

AnalogClock::AnalogClock(ClockTimer* pClockTimer)
{
	m_pClockTimer = pClockTimer;
	m_pClockTimer->Attach(this);
}

AnalogClock::~AnalogClock(void)
{
	m_pClockTimer->Detach(this);
}

void AnalogClock::Update(Subject* pSubject)
{
	if (m_pClockTimer == pSubject)
	{
		Draw();
	}
}

void AnalogClock::Draw()
{
	int hour = m_pClockTimer->GetHour();
	int minute = m_pClockTimer->GetMinute();
	int second = m_pClockTimer->GetSecond();

	//draw analog clock
	printf("analog clock show: %d : %d : %d\n", hour, minute, second);
}
