#pragma once

//#include "YDialog.h"
#include "YCommon.h"

class YDialog;

class YView
{
public:
	YView(void);
	~YView(void);
private:
	YDialog* pDialog;
	YCommon* pCommon;
};
