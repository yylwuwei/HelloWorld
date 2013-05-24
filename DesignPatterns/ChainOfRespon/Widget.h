#pragma once
#include "helphandler.h"

//Widget is abstract class
class Widget :	public HelpHandler
{
public:
	Widget(Widget* parent, Topic topic = NO_HELP_TOPIC);

private:
	Widget* _parent;
};
