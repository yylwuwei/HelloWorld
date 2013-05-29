// List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "YmList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "hello" << std::endl;

	YmList myList;
	YmType ym1 = 5;
	YmType ym2 = 10;
	YmType ym3 = 15;
	myList.Append(&ym1);
	myList.Append(&ym2);
	myList.Append(&ym3);
	myList.ShowAllElem();
	myList.Delele(&ym2);
	myList.ShowAllElem();

	return 0;
}

