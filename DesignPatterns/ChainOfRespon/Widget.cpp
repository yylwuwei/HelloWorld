#include "StdAfx.h"
#include "Widget.h"

Widget::Widget(Widget* parent, Topic topic /* = NO_HELP_TOPIC */):HelpHandler(parent, topic)
{
	_parent = parent;
}