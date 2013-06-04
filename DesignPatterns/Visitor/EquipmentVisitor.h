#pragma once

class FloppyDisk;
class Chassis;

class EquipmentVisitor
{
public:
	virtual ~EquipmentVisitor(void);

	virtual void VisitFloppyDisk(FloppyDisk* floppyDisk);
	virtual void VisitChassis(Chassis* chassis);
protected:
	EquipmentVisitor(void);

};
