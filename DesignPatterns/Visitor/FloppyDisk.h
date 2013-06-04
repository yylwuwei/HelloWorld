#pragma once

#include "Equipment.h"

class FloppyDisk : public Equipment
{
public:
	FloppyDisk(void);
	virtual ~FloppyDisk(void);

	virtual void Accept(EquipmentVisitor* equipVisitor);

	void SetPrice(int price)
	{
		m_price = price;
	}

	int GetPrice()
	{
		return m_price;
	}

private:
	int m_price;
};
