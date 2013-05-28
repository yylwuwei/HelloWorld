#include "StdAfx.h"
#include "DigitalClock.h"

DigitalClock::DigitalClock(ClockTimer* pClockTimer)
{
	m_pClockTimer = pClockTimer;
	m_pClockTimer->Attach(this);
}

DigitalClock::~DigitalClock(void)
{
	m_pClockTimer->Detach(this);
}

void DigitalClock::Update(Subject* pSubject)
{
	if (pSubject == m_pClockTimer)
	{
		Draw();
	}
}

void DigitalClock::Draw()
{
	int hour = m_pClockTimer->GetHour();
	int minute = m_pClockTimer->GetMinute();
	int second = m_pClockTimer->GetSecond();

	//draw the digital clocl
	printf("digital clock show: %d : %d : %d\n", hour, minute, second);
}