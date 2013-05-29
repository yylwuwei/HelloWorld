#pragma once

#include <list>

typedef int YmType;

class YmList
{
public:
	YmList(void);
	virtual ~YmList(void);
	void Append(const YmType* pElem);
	void Delele(YmType* pElem);
	void ShowAllElem();
private:
	std::list<YmType> m_list;
};
