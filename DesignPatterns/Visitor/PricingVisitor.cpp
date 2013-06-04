#include "StdAfx.h"
#include "PricingVisitor.h"
#include "FloppyDisk.h"

PricingVisitor::PricingVisitor(void)
{
}

PricingVisitor::~PricingVisitor(void)
{
}

void PricingVisitor::VisitFloppyDisk(FloppyDisk* floppyDisk)
{
	floppyDisk->SetPrice(50);
	printf("FloppyDisk Price: %d\n", floppyDisk->GetPrice());
}

void PricingVisitor::VisitChassis(Chassis* chassis)
{

}
