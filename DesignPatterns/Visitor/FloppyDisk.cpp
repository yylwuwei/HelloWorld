#include "StdAfx.h"
#include "FloppyDisk.h"
#include "EquipmentVisitor.h"

FloppyDisk::FloppyDisk(void)
{
	m_price = 0;
}

FloppyDisk::~FloppyDisk(void)
{
}

void FloppyDisk::Accept(EquipmentVisitor* equipVisitor)
{
	equipVisitor->VisitFloppyDisk(this);
}
