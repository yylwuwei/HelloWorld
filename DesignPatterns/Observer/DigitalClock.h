#pragma once
#include "observer.h"
#include "Widget.h"
#include "ClockTimer.h"

class DigitalClock : public Widget, public Observer
{
public:
	DigitalClock(ClockTimer* pClockTimer); 
	virtual ~DigitalClock(void);

	virtual void Update(Subject* pSubject);
	virtual void Draw();

private:
	ClockTimer* m_pClockTimer;
	
};
