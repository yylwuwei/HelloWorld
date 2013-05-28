#pragma once
#include "subject.h"

class ClockTimer :	public Subject
{
public:
	ClockTimer(void);
	~ClockTimer(void);

	virtual int GetHour();
	virtual int GetMinute();
	virtual int GetSecond();
	
	void Tick();

private:
	int m_testValue;

};
