#include "StdAfx.h"
#include "YmList.h"

#include <iostream>
#include <iterator>
using namespace std;

YmList::YmList(void)
{
}

YmList::~YmList(void)
{
}

void YmList::Append(const YmType* pElem)
{
	m_list.push_front(*pElem);
}

void YmList::Delele(YmType* pElem)
{
	m_list.remove(*pElem);
}

void YmList::ShowAllElem()
{
	list<YmType>::iterator iterList;
	for (iterList = m_list.begin(); iterList != m_list.end(); iterList++)
	{
		cout << *iterList << endl;
	}
}
