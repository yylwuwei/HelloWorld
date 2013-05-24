// ChainOfRespon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Application.h"
#include "Button.h"
#include "Dialog.h"
#include "Link.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "hello,world" << std::endl;

	const Topic PRINT_TOPIC = 1;
	const Topic PAPER_ORIENTATION_TOPIC = 2;
	const Topic APPLICATION_TOPIC = 3;

	Application* pApp = new Application(APPLICATION_TOPIC);
	Dialog* pDialog = new Dialog(pApp, PRINT_TOPIC);
	Button* pBtn = new Button(pDialog, PAPER_ORIENTATION_TOPIC);
	Link* pLink = new Link(pBtn, NO_HELP_TOPIC);

	pApp->HandleHelp();
	pDialog->HandleHelp();
	pBtn->HandleHelp();
	pLink->HandleHelp();

	return 0;
}

