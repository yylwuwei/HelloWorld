#include "StdAfx.h"
#include "Dialog.h"

#include <iostream>

//why is widget(0)?
Dialog::Dialog(HelpHandler* pHelp, Topic topic /* = NO_HELP_TOPIC */):Widget(NULL)
{
	SetHandler(pHelp, topic);
}

void Dialog::HandleHelp()
{
	if (HasHelp())
	{
		//offer help on the dialog
		std::cout << "offer help on the dialog" << std::endl;
	}
	else
	{
		HelpHandler::HandleHelp();
	}
}

