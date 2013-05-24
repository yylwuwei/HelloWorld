#pragma once

class HelpHandler
{
public:
	HelpHandler(HelpHandler* hander = NULL, Topic topic = NO_HELP_TOPIC);
	virtual bool HasHelp();
	virtual void SetHandler(HelpHandler* handler, Topic topic);
	virtual void HandleHelp();

private:
	HelpHandler* _Successor;
	Topic _topic;
};
