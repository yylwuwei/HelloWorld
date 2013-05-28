#pragma once

class Subject;

class Observer
{
public:
	~Observer(void);
	virtual void Update(Subject* theChangedSubject) = 0;

protected:
	Observer(void);
};
