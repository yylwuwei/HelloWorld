#include "stdafx.h"
#include "MapTest.h"
#include <iostream>
#include <map>

typedef std::pair<int, int> Int_Pair;

void MapTest()
{
	std::map<int, int, std::less<int>> m1;
	m1.insert(Int_Pair(1, 101));
	m1.insert(Int_Pair(2, 102));
	m1.insert(Int_Pair(3, 103));
	
	std::cout << m1.count(5) << std::endl;

	std::map<int, int>::iterator iterM1;

	iterM1 = m1.find(4);
	if (iterM1 == m1.end())
	{
		std::cout << "No found." << std::endl;
	}
	else
	{
		std::cout << iterM1->second << std::endl;
	}

	for (iterM1 = m1.begin(); iterM1 != m1.end(); iterM1++)
	{
		std::cout << iterM1->first << "  " << iterM1->second << std::endl;
	}
}

void MultiMapTest()
{
	std::multimap<int, int, std::greater<int>> m1;
	m1.insert(Int_Pair(1, 101));
	m1.insert(Int_Pair(1, 111));
	m1.insert(Int_Pair(2, 102));
	m1.insert(Int_Pair(3, 103));

	std::cout << m1.count(1) << std::endl;

	std::multimap<int, int, std::greater<int>>::iterator iterM1;
	iterM1 = m1.find(1);
	if (iterM1 == m1.end())
	{
		std::cout << "No found." << std::endl;
	}
	else
	{
		std::cout << iterM1->second << std::endl;
		iterM1++;
		std::cout << iterM1->second << std::endl;
	}

	for (iterM1 = m1.begin(); iterM1 != m1.end(); iterM1++)
	{
		std::cout << iterM1->second << std::endl;
	}
		
}