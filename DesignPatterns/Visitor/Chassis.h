#pragma once
#include "equipment.h"

class Chassis :	public Equipment
{
public:
	Chassis(void);
	virtual ~Chassis(void);

	virtual void Accept(EquipmentVisitor* equipVisitor);
};
