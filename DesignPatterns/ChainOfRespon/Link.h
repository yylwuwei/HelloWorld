#pragma once
#include "widget.h"

class Link : public Widget
{
public:
		
	Link(Widget* pWidget, Topic topic = NO_HELP_TOPIC);

	void HandleHelp();
};
