// Visitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Equipment.h"
#include "FloppyDisk.h"
#include "PricingVisitor.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FloppyDisk* pComponent = new FloppyDisk();
	PricingVisitor* pPricingVisitor = new PricingVisitor();
	pComponent->Accept(pPricingVisitor);
	return 0;
}

