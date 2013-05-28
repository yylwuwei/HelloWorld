#pragma once

#include <list>

#include "Observer.h"

class Subject
{
public:
	virtual ~Subject(void);

	virtual void Attach(Observer* pObserver);
	virtual void Detach(Observer* pObserver);
	virtual void Notify();

protected:
	Subject(void);

private:
	std::list<Observer*>* m_pObservers;
};
