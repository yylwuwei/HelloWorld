
// TimeManageWin.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTimeManageWinApp:
// �йش����ʵ�֣������ TimeManageWin.cpp
//

class CTimeManageWinApp : public CWinAppEx
{
public:
	CTimeManageWinApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTimeManageWinApp theApp;