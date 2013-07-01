#include "stdafx.h"
#include "SetTest.h"
#include <iostream>
#include <set>

void SetTest()
{
	std::set<int, std::greater<int>> mySet;
	mySet.insert(10);
	mySet.insert(10);
	mySet.insert(50);
	mySet.insert(20);

	std::cout << mySet.count(10) << std::endl;
	std::cout << mySet.size() << std::endl;
	std::cout << mySet.max_size() << std::endl;

	std::set<int, std::greater<int>>::iterator iterMySet;

	iterMySet = mySet.find(15);
	if (iterMySet == mySet.end())
	{
		std::cout << "no found elem." << std::endl;
	}
	else
	{
		std::cout << *iterMySet << std::endl;
	}

	for (iterMySet = mySet.begin(); iterMySet != mySet.end(); iterMySet++)
	{
		std::cout << *iterMySet << std::endl;
	}
}

void MultiSetTest()
{
	std::multiset<int> myMultiSet;
	myMultiSet.insert(10);
	myMultiSet.insert(10);
	myMultiSet.insert(50);
	myMultiSet.insert(20);

	std::cout << myMultiSet.count(10) << std::endl;

	std::multiset<int>::iterator iterMyMultiSet;
	for (iterMyMultiSet = myMultiSet.begin(); iterMyMultiSet != myMultiSet.end(); iterMyMultiSet++)
	{
		std::cout << *iterMyMultiSet << std::endl;
	}

}