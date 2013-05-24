#pragma once
#include "widget.h"

class Dialog :	public Widget
{
public:
	Dialog(HelpHandler* pHelp, Topic topic = NO_HELP_TOPIC);
	virtual void HandleHelp();
};
