#pragma once
#include "equipmentvisitor.h"

class PricingVisitor : public EquipmentVisitor
{
public:
	PricingVisitor(void);
	virtual ~PricingVisitor(void);
	
	int& GetTotalPrice();

	virtual void VisitFloppyDisk(FloppyDisk* floppyDisk);
	virtual void VisitChassis(Chassis* chassis);

private:
	int m_totalPrice;
};
