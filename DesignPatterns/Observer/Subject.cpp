#include "StdAfx.h"
#include "Subject.h"

#include <iterator>
using namespace std;

Subject::Subject(void)
{
	m_pObservers = new std::list<Observer*>();
}

Subject::~Subject(void)
{
	delete m_pObservers;
}

void Subject::Attach(Observer* pObserver)
{
	m_pObservers->push_back(pObserver);
}

void  Subject::Detach(Observer *pObserver)
{
	m_pObservers->remove(pObserver);
}

void Subject::Notify()
{
	list<Observer*>::iterator iterList;
	for (iterList = m_pObservers->begin(); iterList != m_pObservers->end(); iterList++ )
	{
		//notify observer to update
		(*iterList)->Update(this);
	}
	
}
