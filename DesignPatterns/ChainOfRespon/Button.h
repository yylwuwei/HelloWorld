#pragma once
#include "widget.h"

class Button : public Widget
{
public:
	Button(Widget* pWidget, Topic topic = NO_HELP_TOPIC);

	virtual void HandleHelp();
};
