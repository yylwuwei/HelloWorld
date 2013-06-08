#pragma once

#include "YView.h"

class YDialog
{
public:
	YDialog(void);
	~YDialog(void);
private:
	YView* pView;
	YCommon* pCommon;
};
