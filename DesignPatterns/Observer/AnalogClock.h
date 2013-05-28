#pragma once
#include "Widget.h"
#include "observer.h"
#include "ClockTimer.h"

class AnalogClock : public Widget, public Observer
{
public:
	AnalogClock(ClockTimer* pClockTimer);
	virtual ~AnalogClock(void);

	virtual void Update(Subject* pSubject);
	virtual void Draw();

private:
	ClockTimer* m_pClockTimer;
};
