#include "StdAfx.h"
#include "Link.h"

#include <iostream>

Link::Link(Widget* pWidget, Topic topic /* = NO_HELP_TOPIC */) : Widget(pWidget, topic)
{

}

void Link::HandleHelp()
{
	if (HasHelp())
	{
		std::cout << "Link offer help" << std::endl;
	}
	else
	{
		HelpHandler::HandleHelp();
	}
}