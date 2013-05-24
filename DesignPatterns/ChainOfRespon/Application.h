#pragma once
#include "helphandler.h"

class Application :	public HelpHandler
{
public:

	//the last object to deal with help request
	Application(Topic topic):HelpHandler(NULL, topic)
	{

	}

	virtual void HandleHelp();
};
