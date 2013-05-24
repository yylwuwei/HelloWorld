#include "StdAfx.h"
#include "HelpHandler.h"

HelpHandler::HelpHandler(HelpHandler* hander, Topic topic)
{
	_Successor = hander;
	_topic = topic;
}

bool HelpHandler::HasHelp()
{
	return NO_HELP_TOPIC != _topic;
}

void HelpHandler::HandleHelp()
{
	if (NULL != _Successor)
	{
		_Successor->HandleHelp();
	}
}

void HelpHandler::SetHandler(HelpHandler* handler, Topic topic)
{
	_Successor = handler;
	_topic = topic;
}
