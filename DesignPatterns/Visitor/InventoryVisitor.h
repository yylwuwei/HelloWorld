#pragma once
#include "equipmentvisitor.h"

class InventoryVisitor : public EquipmentVisitor
{
public:
	InventoryVisitor(void);
	virtual ~InventoryVisitor(void);

	int& GetInventory();

	virtual void VisitFloppyDisk(FloppyDisk* floppyDisk);
	virtual void VisitChassis(Chassis* chassis);

private:
	int m_inventory;

};
