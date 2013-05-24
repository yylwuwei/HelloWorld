#include "StdAfx.h"
#include "Button.h"

#include <iostream>

Button::Button(Widget *pWidget, Topic topic) : Widget(pWidget, topic)
{
	//NULL;
}

void Button::HandleHelp()
{
	if (HasHelp())
	{
		//offter help on the button
		std::cout << "offter help on the button" << std::endl;
	}
	else
	{
		HelpHandler::HandleHelp();
	}
}