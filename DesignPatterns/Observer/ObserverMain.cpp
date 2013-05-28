// Observer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>

#include "ClockTimer.h"
#include "DigitalClock.h"
#include "AnalogClock.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ClockTimer* pTimer = new ClockTimer();
	DigitalClock* pDigitalClock = new DigitalClock(pTimer);
	AnalogClock* pAnalogClock = new AnalogClock(pTimer);

	while(1)
	{
		Sleep(1000);
		pTimer->Tick();
	}

	/*
	while (getchar() != 'q')
	{
		getchar();
		pDigitalClock->Draw();
		pAnalogClock->Draw();
	}*/

	return 0;
}

