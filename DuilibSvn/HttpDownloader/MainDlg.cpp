#include "stdafx.h"
#include "MainDlg.h"
#include <ShellAPI.h>

void Thread_TextPrint(void *vpPtr);


//�̺߳���
void Thread_Progress(void *vpPtr)
{
	_Nv_Download_Ex *pdlg = (_Nv_Download_Ex*)vpPtr;

	while (TRUE)
	{
		if (pdlg->m_bClose == TRUE)
		{
			_endthreadex(Thread_OutCode_Sleep);
			return;
		}
		if (pdlg->m_pWndPtr->m_nTaskCount < 4)
		{
			pdlg->m_pWndPtr->m_nTaskCount++;
			break;
		}
		Sleep(500);
	}
	
	//����
	pdlg->Nv_Download_ = new _Nv_Download;

	pdlg->m_Handle_Print = (HANDLE)_beginthreadex(
		NULL, 
		0, 
		(unsigned int (__stdcall *)(void *))Thread_TextPrint, 
		vpPtr, 
		0, 
		NULL
		);

	//�����߳���
	pdlg->Nv_Download_->set_ThreadCount(6);
	pdlg->m_pWndPtr->m_dwLinkCount += 12;
	//����������
	pdlg->Nv_Download_->set_HttpLinkCount(pdlg->m_pWndPtr->m_dwLinkCount);
	//����ÿ���߳���Ҫ���ص��ֽ� ������
	pdlg->m_pProgRess->SetMinValue(0);
	pdlg->Nv_Download_->set_DownloadTaskCnt(205000);
	pdlg->Nv_Download_->Download(pdlg->m_strUrl.c_str(), pdlg->m_strFileSavePath.c_str(), NULL);

	pdlg->m_pProgRess->SetMaxValue(pdlg->Nv_Download_->n64FileSize_);

	while (TRUE)
	{
		Sleep(100);
		tag_Download_Data  tag_Data;
		tag_Data.pProgress = pdlg->m_pProgRess;
		tag_Data.Nv_Download_ = pdlg->Nv_Download_;
		COPYDATASTRUCT tagSend;
		tagSend.cbData = sizeof(tag_Download_Data);
		tagSend.lpData = &tag_Data;

		pdlg->m_pWndPtr->SendMessage(WM_USER_PROG, 0, (LPARAM)&tagSend);

		if (pdlg->Nv_Download_->get_StopPrintf() == TRUE)
		{
			DegMsg("������ˢ���˳�..");
			_endthreadex(Thread_OutCode_ProgRess);
			return;
		}
	}
}


//�̺߳���
void Thread_TextPrint(void *vpPtr)
{
	_Nv_Download_Ex *pdlg = (_Nv_Download_Ex*)vpPtr;

	while (TRUE)
	{
		Sleep(1000);
		tag_Download_Data  tag_Data;
		tag_Data.pTextPrint = pdlg->m_pTextPrint;
		tag_Data.Nv_Download_ = pdlg->Nv_Download_;
		COPYDATASTRUCT tagSend;
		tagSend.cbData = sizeof(tag_Download_Data);
		tagSend.lpData = &tag_Data;

		pdlg->m_pWndPtr->SendMessage(WM_USER_TEXTPRINT, 0, (LPARAM)&tagSend);

		if (pdlg->Nv_Download_->get_StopPrintf() == TRUE)
		{
			DegMsg("������ʾ�˳�..");

			pdlg->m_pWndPtr->SendMessage(WM_USER_TEXTPRINT, 0, (LPARAM)&tagSend);

			pdlg->m_pWndPtr->m_dwLinkCount -= 12;
			pdlg->m_pWndPtr->m_nTaskCount -= 1;
			
			//��ѯ�Լ�����λ��
			DWORD dwSize = pdlg->m_pWndPtr->m_vt_Nv_Download.size();
			for (int i=0; i<dwSize; ++i)
			{
				if (pdlg->m_pWndPtr->m_vt_Nv_Download[i]->m_pBtnIco == pdlg->m_pBtnIco)
				{
					pdlg->m_ListItemPos = i;
					break;
				}
			}
			//��¼
			pdlg->m_pWndPtr->mod_DownloadFileIni(
				pdlg->m_ListItemPos,
				pdlg->m_strUrl.c_str(),
				pdlg->m_strFileSavePath.c_str(),
				pdlg->m_pTextFile->GetText(),
				NULL,
				pdlg->Nv_Download_->n64FileSize_,
				pdlg->Nv_Download_->get_DownloadCount(),
				pdlg->m_pTextPrint->GetText(),
				pdlg->m_bOpenFile
				);

			//�ر��߳� ���ô���
			_endthreadex(Thread_OutCode_Print);
			return;
		}
	}
}


//�̺߳���
void Thread_StopTask(void *vpPtr)
{
	_Nv_Download_Ex *pdlg = (_Nv_Download_Ex*)vpPtr;

	pdlg->Nv_Download_->thread_SecurityCloseTask();

	//�ж�ֹͣ�ɹ�
	DWORD dwOutCode_ProgRess = 0;

	while (TRUE)
	{
		Sleep(10);
		::GetExitCodeThread(pdlg->m_Handle_ProgRess, &dwOutCode_ProgRess);
		if ((dwOutCode_ProgRess == Thread_OutCode_ProgRess) || (dwOutCode_ProgRess == Thread_OutCode_Sleep))
		{
			pdlg->m_Handle_ProgRess = NULL;
			break;
		}
	}

	if (dwOutCode_ProgRess == Thread_OutCode_ProgRess)
	{
		while (TRUE)
		{
			Sleep(10);
			DWORD dwOutCode = 0;
			::GetExitCodeThread(pdlg->m_Handle_Print, &dwOutCode);
			if (dwOutCode == Thread_OutCode_Print)
			{
				pdlg->m_Handle_Print = NULL;
				break;
			}
		}
	}

	//��¼
	pdlg->m_pWndPtr->mod_DownloadFileIni(
				pdlg->m_ListItemPos,
				pdlg->m_strUrl.c_str(),
				pdlg->m_strFileSavePath.c_str(),
				pdlg->m_pTextFile->GetText(),
				NULL,
				pdlg->Nv_Download_->n64FileSize_,
				pdlg->Nv_Download_->get_DownloadCount(),
				pdlg->m_pTextPrint->GetText(),
				pdlg->m_bOpenFile
			);

}


//�̺߳���
void Thread_CloseTask(void *vpPtr)
{
	_Nv_Download_Ex *pdlg = (_Nv_Download_Ex*)vpPtr;
	
	//��ɾ���б�
	tag_Download_Data tag_Data;
	tag_Data.nPos = pdlg->m_ListItemPos;
	tag_Data.pList = pdlg->m_pList;
	tag_Data.pDownloadEx = pdlg;

	COPYDATASTRUCT tagSend;
	tagSend.cbData = sizeof(tag_Download_Data);
	tagSend.lpData = &tag_Data;

	pdlg->m_pWndPtr->SendMessage(WM_USER_DELETE_ITEM, 0, (LPARAM)&tagSend);

	//����ǵȴ������� ����Ҫֹͣ�߳�
	if (pdlg->Nv_Download_ != NULL)
	{
		//��ֹͣ������
		pdlg->Nv_Download_->thread_SecurityCloseTask();
	
		DWORD dwOutCode_ProgRess = 0;

		while (TRUE)
		{
			Sleep(10);
			::GetExitCodeThread(pdlg->m_Handle_ProgRess, &dwOutCode_ProgRess);
			if ((dwOutCode_ProgRess == Thread_OutCode_ProgRess) || (dwOutCode_ProgRess == Thread_OutCode_Sleep))
			{
				pdlg->m_Handle_ProgRess = NULL;
				break;
			}
		}
		
		if (dwOutCode_ProgRess == Thread_OutCode_ProgRess)
		{
			while (TRUE)
			{
				Sleep(10);
				DWORD dwOutCode = 0;
				::GetExitCodeThread(pdlg->m_Handle_Print, &dwOutCode);
				if (dwOutCode == Thread_OutCode_Print)
				{
					pdlg->m_Handle_Print = NULL;
					break;
				}
			}
		}
	}

	while(TRUE)
	{
		Sleep(50);
		if ((pdlg->Nv_Download_ == NULL) || (TRUE == pdlg->Nv_Download_->detect_DownlaodIsClose()))
		{
			if (pdlg->Nv_Download_ != NULL)
			{
				//�������ٸ�����
				delete pdlg->Nv_Download_;
				pdlg->Nv_Download_ = NULL;
			}


			//��ɾ���б�
			tag_Download_Data tag_Data;
			tag_Data.nPos = pdlg->m_ListItemPos;
			tag_Data.pList = pdlg->m_pList;
			tag_Data.pDownloadEx = pdlg;
			tag_Data.bMode = TRUE;

			COPYDATASTRUCT tagSend;
			tagSend.cbData = sizeof(tag_Download_Data);
			tagSend.lpData = &tag_Data;

			pdlg->m_pWndPtr->SendMessage(WM_USER_DELETE_ITEM, 0, (LPARAM)&tagSend);

			break;
		}
	}

}

//����
CMainDlg::CMainDlg()
{
	m_hinstance = NULL;
	m_vt_Nv_Download.clear();
	m_nTaskCount = 0;
	m_vtDownLoadFileData.clear();
}


LRESULT CMainDlg::OnCopyData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	COPYDATASTRUCT *tag = (COPYDATASTRUCT*)lParam;

	struct tagData{
		CHAR strUrl[1024];
		CHAR strSaveFilePath[1024];
		CHAR strFileName[1024];
		CHAR strCoolie[1024];
		__int64 n64FileSize;
		BOOL bRunMode;
	};

	tagData tagDwondData;

	//���������ڷ��͹��������ݳ������
	memcpy(&tagDwondData, tag->lpData, tag->cbData);

	FILE *fp = fopen(tagDwondData.strSaveFilePath, "w+");

	if (fp == NULL)
	{
		DegMsg("�����ļ�ʧ��!");
	}
	else
	{
		fclose(fp);
	}

	_Nv_Download_Ex *pdlg = new _Nv_Download_Ex;
	
	pdlg->get_WndPtr(this);

	//����list item
	add_ListItem(NULL, NULL, TRUE, pdlg);
	//����ļ���¼
	add_DownloadFileIni(tagDwondData.strUrl, tagDwondData.strSaveFilePath, tagDwondData.strFileName, tagDwondData.n64FileSize);
	
	//���ݻ�ȡ
	pdlg->m_strUrl = tagDwondData.strUrl;
	pdlg->m_strFileSavePath = tagDwondData.strSaveFilePath;
	pdlg->m_bOpenFile = tagDwondData.bRunMode;
	pdlg->m_strCoolie = "";
	
	//�ļ���
	pdlg->m_pTextFile->SetText(tagDwondData.strFileName);

	//׷������
	vector<_Nv_Download_Ex*>::iterator it;
	it = m_vt_Nv_Download.begin();
	m_vt_Nv_Download.insert(it, pdlg);

	//��ʼ����
	pdlg->m_Handle_ProgRess = (HANDLE)_beginthreadex(
		NULL, 
		0, 
		(unsigned int (__stdcall *)(void *))Thread_Progress, 
		pdlg, 
		0, 
		NULL
		);

	return 0;
}


LRESULT CMainDlg::OnUserProg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	COPYDATASTRUCT *tag = (COPYDATASTRUCT*)lParam;

	//�����������ݿ����Ľṹ
	tag_Download_Data tag_Data;
	//���������ڷ��͹��������ݳ������
	memcpy(&tag_Data, tag->lpData, tag->cbData);

	tag_Data.pProgress->SetValue(tag_Data.Nv_Download_->get_DownloadCount());

	return 0;
}


LRESULT CMainDlg::OnUserPrint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	COPYDATASTRUCT *tag = (COPYDATASTRUCT*)lParam;

	//�����������ݿ����Ľṹ
	tag_Download_Data tag_Data;
	//���������ڷ��͹��������ݳ������
	memcpy(&tag_Data, tag->lpData, tag->cbData);

	if (tag_Data.Nv_Download_->get_StopPrintf() == TRUE)
	{
		if (tag_Data.Nv_Download_->get_TaskStop() == TRUE)
		{
			CHAR strData[1024] = {0};
			sprintf(strData, "%0.2fMB - %0.2fMB, ����ֹͣ..",
				(float)tag_Data.Nv_Download_->n64FileSize_ / (float)1024 / (float)1024,
				(float)tag_Data.Nv_Download_->get_DownloadCount() / (float)1024 / (float)1024
				);
			tag_Data.pTextPrint->SetText(strData);
		}
		else
		{
			CHAR strData[1024] = {0};
			sprintf(strData, "%0.2fMB - �������..",
				(float)tag_Data.Nv_Download_->n64FileSize_ / (float)1024 / (float)1024
				);
			tag_Data.pTextPrint->SetText(strData);
		}
		return 0;
	}

	CHAR strCnt[1024] = {0};
	sprintf(strCnt, "%0.2fMB, %0.2fMB, %lld/KBs, %s",
		(float)((float)tag_Data.Nv_Download_->n64FileSize_ / (float)1024 / (float)1024),
		(float)((float)tag_Data.Nv_Download_->get_DownloadCount() / (float)1024 / (float)1024),
		tag_Data.Nv_Download_->get_DownloadSpeed(),
		tag_Data.Nv_Download_->get_SurplusDownloadTime()
		);
	tag_Data.pTextPrint->SetText(strCnt);

	return 0;
}


LRESULT CMainDlg::OnUserCloseListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	COPYDATASTRUCT *tag = (COPYDATASTRUCT*)lParam;

	//�����������ݿ����Ľṹ
	tag_Download_Data tag_Data;
	//���������ڷ��͹��������ݳ������
	memcpy(&tag_Data, tag->lpData, tag->cbData);
	
	if (tag_Data.bMode == FALSE)
	{
		tag_Data.pDownloadEx->m_pListElement->SetVisible(false);
		return 0;
	}

	//ɾ�����ص��ļ� �Լ���ʱ�ļ�
	DeleteFile(tag_Data.pDownloadEx->m_strFileSavePath.c_str());
	DeleteFile(string(tag_Data.pDownloadEx->m_strFileSavePath + ".NatureVirusDownloadFile").c_str());

	//����vt
	if (m_vt_Nv_Download[tag_Data.nPos] != NULL)
	{
		delete	m_vt_Nv_Download[tag_Data.nPos];
		m_vt_Nv_Download[tag_Data.nPos] = NULL;
	}
	
	if (m_vt_Nv_Download.size() >= tag_Data.nPos)
	{
		m_vt_Nv_Download.erase(m_vt_Nv_Download.begin() + tag_Data.nPos);
		//��¼�ļ�
		m_vtDownLoadFileData.erase(m_vtDownLoadFileData.begin() + tag_Data.nPos);
		//��д
		null_DownloadFileIni();
	}

	//ɾ���ڵ�
	tag_Data.pList->RemoveAt(tag_Data.nPos);

	
	return 0;
}


//��Ϣѭ��
LRESULT CMainDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg )
	{
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_COPYDATA:	   lRes = OnCopyData(uMsg, wParam, lParam, bHandled); break;
	case WM_USER_PROG:	   lRes = OnUserProg(uMsg, wParam, lParam, bHandled); break;
	case WM_USER_TEXTPRINT:lRes = OnUserPrint(uMsg, wParam, lParam, bHandled); break;
	case WM_USER_DELETE_ITEM: lRes = OnUserCloseListItem(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

//��Ϣ����
LRESULT CMainDlg::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
	if( wParam == SC_CLOSE ) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed ) {
		if( !bZoomed )
		{
			//˫�����
		}
		else
		{
			//˫����С��
		}
	}
	return lRes;
}

//��Ϣ����
LRESULT CMainDlg::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-rcWork.left, -rcWork.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

//��Ϣ����
LRESULT CMainDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}

//��Ϣ����
LRESULT CMainDlg::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_pm.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
			if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
				_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
				_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 )
				return HTCAPTION;
	}

	return HTCLIENT;
}

//������Ϣ
LRESULT CMainDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("skin.xml"), (UINT)0,  NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	init_BindControls();
	init_ControlsData();

	return 0;
}



void CMainDlg::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		//�����������ť
		if( msg.pSender == m_pBtnClose ) 
		{ 
			PostQuitMessage(0); // ��Ϊactivex��ԭ��ʹ��close���ܻ���ִ���
			return; 
		}else if( msg.pSender == m_pBtnMin ) 
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
			return; 
		}else if( msg.pSender->GetName() == _T("quitbtn") ) {
			/*Close()*/PostQuitMessage(0); // ��Ϊactivex��ԭ��ʹ��close���ܻ���ִ���
		}else if(msg.pSender->GetName() == _T("stop"))
		{
			CControlUI *find_ctrl = m_pm.FindSubControlByName(msg.pSender->GetParent()->GetParent(), _T("ico"));
			int nPos = get_DownloadPtrPos(find_ctrl);
			if (nPos != -1)
			{
				if (m_vt_Nv_Download.size() != 0)
					if (m_vt_Nv_Download[nPos]->Nv_Download_->deetct_ThreadMode() == TRUE)
					{
						//���߳����� ��ʾ�û�
						if (IDYES != ::MessageBox(0, "������֧�ֶϵ�����,ֹͣ�����ٴ����ؽ���ȫ��������, �Ƿ���Ȼֹͣ���أ�", "����", MB_YESNO))
						{
							return;
						}
					}
					m_vt_Nv_Download[nPos]->m_ListItemPos = nPos;
					(HANDLE)_beginthreadex(
						NULL, 
						0, 
						(unsigned int (__stdcall *)(void *))Thread_StopTask, 
						m_vt_Nv_Download[nPos], 
						0, 
						NULL
						);
				return;
			}
		}else if(msg.pSender->GetName() == _T("down"))
		{
			CControlUI *find_ctrl = m_pm.FindSubControlByName(msg.pSender->GetParent()->GetParent(), _T("ico"));
			int nPos = get_DownloadPtrPos(find_ctrl);
			if (nPos != -1)
			{
				if (m_vt_Nv_Download.size() != 0)
				{
					//��������
					//ɾ��֮ǰ���� ����һ���µ���
					delete m_vt_Nv_Download[nPos]->Nv_Download_;
					m_vt_Nv_Download[nPos]->Nv_Download_ = new _Nv_Download;

					m_vt_Nv_Download[nPos]->m_Handle_ProgRess = (HANDLE)_beginthreadex(
						NULL, 
						0, 
						(unsigned int (__stdcall *)(void *))Thread_Progress, 
						m_vt_Nv_Download[nPos], 
						0, 
						NULL
						);
				}
				return;
			}
		}else if(msg.pSender->GetName() == _T("open"))
		{
			//������� �򿪸��ļ�
			CControlUI *find_ctrl = m_pm.FindSubControlByName(msg.pSender->GetParent()->GetParent(), _T("ico"));
			int nPos = get_DownloadPtrPos(find_ctrl);
			if (nPos != -1)
			{
				if (m_vt_Nv_Download.size() != 0)
				{
					ShellExecute(NULL, _T("open"), m_vt_Nv_Download[nPos]->m_strFileSavePath.c_str(), _T(""), _T(""), SW_SHOWNORMAL);
					return;
				}
			}
		}else if(msg.pSender->GetName() == _T("dele"))
		{
			if (IDYES == ::MessageBox(0, "�Ƿ�Ҫɾ��������?, ������� ��������,  ������ǡ� ɾ�������� ", "��ʾ", MB_YESNO))
			{
				//ɾ����list
				CControlUI *find_ctrl = m_pm.FindSubControlByName(msg.pSender->GetParent()->GetParent(), _T("ico"));
				int nPos = get_DownloadPtrPos(find_ctrl);
				if (nPos != -1)
				{
					if (m_vt_Nv_Download.size() != 0)
					{
						//ʹ���̴߳���
						m_vt_Nv_Download[nPos]->m_ListItemPos = nPos;
						m_vt_Nv_Download[nPos]->m_bClose = TRUE;

						_beginthreadex(
							NULL, 
							0, 
							(unsigned int (__stdcall *)(void *))Thread_CloseTask, 
							m_vt_Nv_Download[nPos], 
							0, 
							NULL
							);
						return;
					}
				}
			}
		}else if (msg.pSender == m_pBtnAddTask)
		{
			if (m_hinstance != NULL)
			{
				FreeLibrary(m_hinstance);
				m_hinstance = NULL;
			}

			m_hinstance = LoadLibraryEx(_T("OpenUrl.dll"), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

			if (m_hinstance != NULL)
			{
				m_FunSetUrL		= (DLL_SetUrL)GetProcAddress(m_hinstance, "DLL_SetUrL");
				m_FunSetCoolie	= (DLL_SetCoolie)GetProcAddress(m_hinstance, "DLL_SetCoolie");
				m_FunSetClassStr = (DLL_SetClassStr)GetProcAddress(m_hinstance, "DLL_SetClassStr");

				if (m_FunSetUrL != NULL || m_FunSetCoolie != NULL)
				{
					m_FunSetUrL("http://dl_dir.qq.com/qqfile/qq/QQ2012/QQ2012.exe");
					m_FunSetCoolie(NULL);
					m_FunSetClassStr(NULL);
				}
			}
		}
	}
}

//��ʼ�� ��ť �ȵ�
void CMainDlg::init_BindControls() 
{
	//����xml������ַ�������
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
	m_pBtnAddTask = static_cast<CButtonUI*>(m_pm.FindControl(_T("add")));
	m_pBtnMin = static_cast<CButtonUI*>(m_pm.FindControl(_T("min")));

	rand_DownloadFileIni();
}


//��ʼ����Ϣ ����
void CMainDlg::init_ControlsData(void)
{

}

void CMainDlg::set_WidthPos(IN CRichEditUI *pdlg, IN int nWidth)
{
	RECT rc = pdlg->GetPos();
	RECT rect;
	rect.top  = rc.top;
	rect.left = nWidth;

	//��� ����
	rect.bottom = pdlg->GetFixedHeight() + rect.top;
	rect.right = pdlg->GetFixedWidth() + rect.left;
	pdlg->SetPos(rect);
}


void CMainDlg::set_WidthPos(IN CButtonUI *pdlg, IN int nWidth)
{
	RECT rc = pdlg->GetPos();
	RECT rect;
	rect.top  = rc.top;
	rect.left = nWidth;

	//��� ����
	rect.bottom = pdlg->GetFixedHeight() + rect.top;
	rect.right = pdlg->GetFixedWidth() + rect.left;
	pdlg->SetPos(rect);
}

void CMainDlg::set_WidthPos(IN CTextUI *pdlg, IN int nWidth)
{
	RECT rc = pdlg->GetPos();
	RECT rect;
	rect.top  = rc.top;
	rect.left = nWidth;

	//��� ����
	rect.bottom = pdlg->GetFixedHeight() + rect.top;
	rect.right = pdlg->GetFixedWidth() + rect.left;
	pdlg->SetPos(rect);
}


void CMainDlg::set_Width(IN CRichEditUI *pdlg, IN int nWidth)
{
	RECT rc = pdlg->GetPos();
	RECT rect;
	rect.top  = rc.top;
	rect.left = rc.left;

	//��� ����
	rect.bottom = pdlg->GetFixedHeight() + rect.top;
	rect.right = pdlg->GetFixedWidth() + nWidth;
	pdlg->SetPos(rect);
}

void CMainDlg::set_Width(IN CHorizontalLayoutUI *pdlg, IN int nWidth)
{
	RECT rc = pdlg->GetPos();
	RECT rect;
	rect.top  = rc.top;
	rect.left = rc.left;

	//��� ����
	rect.bottom = pdlg->GetFixedHeight() + rect.top;
	rect.right = pdlg->GetFixedWidth() + nWidth;
	pdlg->SetPos(rect);
}


BOOL CMainDlg::add_ListItem(const char *strUrl, const char *strFilePath, BOOL bOpenMode, _Nv_Download_Ex *pdlg)
{
	//��ȡlistָ��
	CListUI *cList_Item = static_cast<CListUI*>(m_pm.FindControl(_T("down_list_tab")));
	if(NULL == cList_Item)
	{
		return FALSE;
	}
	pdlg->m_pList = cList_Item;
	//����list item�ڵ�ָ��
	CListContainerElementUI *new_node = new CListContainerElementUI;
	new_node->ApplyAttributeList(_T("height=\"60\""));
	pdlg->m_pListElement = new_node;
	
	//����һ�����沼���� ���򲼾� �߶� 60
	CVerticalLayoutUI *new_v_lay = new CVerticalLayoutUI;
	new_v_lay->ApplyAttributeList(_T("height=\"60\""));
	pdlg->m_pVerticalLayout = new_v_lay;
	
	//////////////////////////////////////////////////////////////////////////
	//�������ֿؼ�
	CButtonUI *cBtn_Ico = new CButtonUI;
	cBtn_Ico->ApplyAttributeList(
		_T("name=\"ico\" float=\"true\" pos=\"5,10,0,0\" width=\"48\" height=\"38\" tooltip=\"ͼ��..\" bkimage=\"file='exe_file.png'\"")
		);
	pdlg->m_pBtnIco = cBtn_Ico;

	CTextUI *cText_file = new CTextUI;
	cText_file->ApplyAttributeList(
		_T("name=\"file\" float=\"true\" pos=\"55,15,0,0\" width=\"300\" height=\"20\" tooltip=\"�ļ���..\" font=\"0\" textcolor=\"#ffffffff\"")
	);
	pdlg->m_pTextFile = cText_file;
	
	CTextUI *cText_Print = new CTextUI;
	cText_Print->ApplyAttributeList(
		_T("name=\"print\" float=\"true\" pos=\"55,35,0,0\" width=\"300\" height=\"20\" text=\"����׼������..\" tooltip=\"������ʾ..\"  font=\"0\" textcolor=\"#ffddd333\"")
		);
	pdlg->m_pTextPrint = cText_Print;

	CTextUI *cText_jdtbk = new CTextUI;
	cText_jdtbk->ApplyAttributeList(
		_T("name=\"jdtbk\" float=\"true\" pos=\"300,15,0,0\" width=\"210\" height=\"7\" bkimage=\"file='progress_back.png'\"")
		);
	pdlg->m_pTextJdtBk = cText_jdtbk;

	CProgressUI *cProgress = new CProgressUI;
	cProgress->ApplyAttributeList(
		_T("name=\"jdt\" float=\"true\" pos=\"300,15,0,0\" width=\"210\" height=\"7\" foreimage=\"file='progress_fore.png'\"")
		);
	pdlg->m_pProgRess = cProgress;
	cProgress->SetMaxValue(100);
	cProgress->SetMinValue(0);

	CButtonUI *cBtn_Stop = new CButtonUI;
	cBtn_Stop->ApplyAttributeList(
		_T("name=\"stop\" float=\"true\" pos=\"400,25,0,0\" width=\"30\" height=\"30\" tooltip=\"��ͣ����..\" normalimage=\"file='stop.png'\"")
		);
	pdlg->m_pBtnStop = cBtn_Stop;

	CButtonUI *cBtn_Down = new CButtonUI;
	cBtn_Down->ApplyAttributeList(
		_T("name=\"down\" float=\"true\" pos=\"440,25,0,0\" width=\"30\" height=\"30\" tooltip=\"��ʼ����..\" normalimage=\"file='go.png'\"")
		);
	pdlg->m_pBtnGo = cBtn_Down;

	CButtonUI *cBtn_Open = new CButtonUI;
	cBtn_Open->ApplyAttributeList(
		_T("name=\"open\" float=\"true\" pos=\"480,25,0,0\" width=\"30\" height=\"30\" tooltip=\"���ļ�..\" normalimage=\"file='ok.png'\"")
		);
	pdlg->m_pBtnOK = cBtn_Open;

	CButtonUI *cBtn_Dele = new CButtonUI;
	cBtn_Dele->ApplyAttributeList(
		_T("name=\"dele\" float=\"true\" pos=\"520,5,0,0\" width=\"20\" height=\"20\" tooltip=\"ɾ������..\" normalimage=\"file='close.png'\"")
		);
	pdlg->m_pBtnClose = cBtn_Dele;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//�������õĿؼ���ӵ����沼������
	new_v_lay->Add(cBtn_Ico);
	new_v_lay->Add(cText_file);
	new_v_lay->Add(cText_Print);
	new_v_lay->Add(cText_jdtbk);
	new_v_lay->Add(cProgress);
	new_v_lay->Add(cBtn_Stop);
	new_v_lay->Add(cBtn_Down);
	new_v_lay->Add(cBtn_Open);
	new_v_lay->Add(cBtn_Dele);

	//�����沼������ӵ�list item�ڵ���
	new_node->Add(new_v_lay);
	//����list�ڵ���뵽list��
	cList_Item->AddAt(new_node,0);

	return TRUE;
}



//����list item
BOOL CMainDlg::create_ListItem(tag_Donwload_File_Ini_Data tag_File_Data)
{
	//��ȡlistָ��
	CListUI *cList_Item = static_cast<CListUI*>(m_pm.FindControl(_T("down_list_tab")));
	if(NULL == cList_Item)
	{
		return FALSE;
	}

	//����list item�ڵ�ָ��
	CListContainerElementUI *new_node = new CListContainerElementUI;
	new_node->ApplyAttributeList(_T("height=\"60\""));
	

	//����һ�����沼���� ���򲼾� �߶� 60
	CVerticalLayoutUI *new_v_lay = new CVerticalLayoutUI;
	new_v_lay->ApplyAttributeList(_T("height=\"60\""));


	//////////////////////////////////////////////////////////////////////////
	//�������ֿؼ�
	CButtonUI *cBtn_Ico = new CButtonUI;
	cBtn_Ico->ApplyAttributeList(
		_T("name=\"ico\" float=\"true\" pos=\"5,10,0,0\" width=\"48\" height=\"38\" tooltip=\"ͼ��..\" bkimage=\"file='exe_file.png'\"")
		);


	CTextUI *cText_file = new CTextUI;
	cText_file->ApplyAttributeList(
		_T("name=\"file\" float=\"true\" pos=\"55,15,0,0\" width=\"300\" height=\"20\" tooltip=\"�ļ���..\" font=\"0\" textcolor=\"#ffffffff\"")
		);
	cText_file->SetText(tag_File_Data.strFileName.c_str());

	CTextUI *cText_Print = new CTextUI;
	cText_Print->ApplyAttributeList(
		_T("name=\"print\" float=\"true\" pos=\"55,35,0,0\" width=\"300\" height=\"20\" text=\"����׼������..\" tooltip=\"������ʾ..\"  font=\"0\" textcolor=\"#ffddd333\"")
		);
	cText_Print->SetText(tag_File_Data.strDataPrint.c_str());

	CTextUI *cText_jdtbk = new CTextUI;
	cText_jdtbk->ApplyAttributeList(
		_T("name=\"jdtbk\" float=\"true\" pos=\"300,15,0,0\" width=\"210\" height=\"7\" bkimage=\"file='progress_back.png'\"")
		);
	

	CProgressUI *cProgress = new CProgressUI;
	cProgress->ApplyAttributeList(
		_T("name=\"jdt\" float=\"true\" pos=\"300,15,0,0\" width=\"210\" height=\"7\" foreimage=\"file='progress_fore.png'\"")
		);
	cProgress->SetMaxValue(tag_File_Data.n64FileSize);
	cProgress->SetMinValue(0);
	cProgress->SetValue(tag_File_Data.n64ProgRessPos);

	CButtonUI *cBtn_Stop = new CButtonUI;
	cBtn_Stop->ApplyAttributeList(
		_T("name=\"stop\" float=\"true\" pos=\"400,25,0,0\" width=\"30\" height=\"30\" tooltip=\"��ͣ����..\" normalimage=\"file='stop.png'\"")
		);
	

	CButtonUI *cBtn_Down = new CButtonUI;
	cBtn_Down->ApplyAttributeList(
		_T("name=\"down\" float=\"true\" pos=\"440,25,0,0\" width=\"30\" height=\"30\" tooltip=\"��ʼ����..\" normalimage=\"file='go.png'\"")
		);
	

	CButtonUI *cBtn_Open = new CButtonUI;
	cBtn_Open->ApplyAttributeList(
		_T("name=\"open\" float=\"true\" pos=\"480,25,0,0\" width=\"30\" height=\"30\" tooltip=\"���ļ�..\" normalimage=\"file='ok.png'\"")
		);
	

	CButtonUI *cBtn_Dele = new CButtonUI;
	cBtn_Dele->ApplyAttributeList(
		_T("name=\"dele\" float=\"true\" pos=\"520,5,0,0\" width=\"20\" height=\"20\" tooltip=\"ɾ������..\" normalimage=\"file='close.png'\"")
		);
	
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//�������õĿؼ���ӵ����沼������
	new_v_lay->Add(cBtn_Ico);
	new_v_lay->Add(cText_file);
	new_v_lay->Add(cText_Print);
	new_v_lay->Add(cText_jdtbk);
	new_v_lay->Add(cProgress);
	new_v_lay->Add(cBtn_Stop);
	new_v_lay->Add(cBtn_Down);
	new_v_lay->Add(cBtn_Open);
	new_v_lay->Add(cBtn_Dele);

	//�����沼������ӵ�list item�ڵ���
	new_node->Add(new_v_lay);
	//����list�ڵ���뵽list��
	cList_Item->Add(new_node);
	
	_Nv_Download_Ex		*Nv_Task_ = new _Nv_Download_Ex;

	Nv_Task_->m_pList = cList_Item;
	Nv_Task_->m_pListElement = new_node;
	Nv_Task_->m_pVerticalLayout = new_v_lay;
	Nv_Task_->m_pBtnIco = cBtn_Ico;
	Nv_Task_->m_pTextFile = cText_file;
	Nv_Task_->m_pTextPrint = cText_Print;
	Nv_Task_->m_pTextJdtBk = cText_jdtbk;
	Nv_Task_->m_pProgRess = cProgress;
	Nv_Task_->m_pBtnStop = cBtn_Stop;
	Nv_Task_->m_pBtnGo = cBtn_Down;
	Nv_Task_->m_pBtnOK = cBtn_Open;
	Nv_Task_->m_pBtnClose = cBtn_Dele;

	Nv_Task_->get_WndPtr(this);

	//���ݻ�ȡ
	Nv_Task_->m_strUrl = tag_File_Data.strUrl;
	Nv_Task_->m_strFileSavePath = tag_File_Data.strPath;
	Nv_Task_->m_bOpenFile = tag_File_Data.bOpenFile;
	Nv_Task_->m_strCoolie = tag_File_Data.strCoolie;
	
	//vector<_Nv_Download_Ex*>::iterator it;
	//it = m_vt_Nv_Download.begin();
	//m_vt_Nv_Download.insert(it, Nv_Task_);
	m_vt_Nv_Download.push_back(Nv_Task_);

	return TRUE;
}

//��ȡlistpos
int CMainDlg::get_DownloadPtrPos(CControlUI* cContrCmp)
{
	if (cContrCmp == NULL)
	{
		return -1;
	}
	//�������ָ����vector�������ĸ���ȣ� �������ø���
	DWORD dwSize = m_vt_Nv_Download.size();
	for (int i=0; i<dwSize; ++i)
	{
		if (m_vt_Nv_Download[i]->m_pBtnIco == cContrCmp)
		{
			return i;
		}
	}

	return -1;
}


//��ȡӦ�ó���·��
char *CMainDlg::get_ProcessPath(void)
{
	static char szOutCpyFile[1024];

	DWORD dw = GetModuleFileName(NULL, szOutCpyFile, 1024);
	DWORD dwSize = strlen(szOutCpyFile);

	for (int i=0; i<dwSize; ++i)
	{
		if(szOutCpyFile[dwSize-i-1] == '\\')
		{
			szOutCpyFile[dwSize-i] = '\0';			
			return szOutCpyFile;
		}
	}

	return NULL;
}



//���һ�������ļ���¼
BOOL CMainDlg::add_DownloadFileIni(
						__in const char *strUrl,
						__in const char *strSaveFilePath,
						__in const char *strFileName,
						__in __int64 n64FileSize,
						__in const char *strCoolie,
						__in __int64 n64ProgRessPos,
						__in const char *strPrint,
						__in bool bOpenFile
						)
{
	if (strCoolie == NULL)
	{
		strCoolie = "strCoolie";
	}
	//��������
	tag_Donwload_File_Ini_Data  tag_File_Data;
	tag_File_Data.strUrl = strUrl;
	tag_File_Data.strPath = strSaveFilePath;
	tag_File_Data.strFileName = strFileName;
	tag_File_Data.n64FileSize = n64FileSize;
	tag_File_Data.strDataPrint = strPrint;
	tag_File_Data.strCoolie = strCoolie;
	tag_File_Data.n64ProgRessPos = n64ProgRessPos;
	tag_File_Data.bOpenFile = bOpenFile;

	vector<tag_Donwload_File_Ini_Data>::iterator it;
	it = m_vtDownLoadFileData.begin();
	m_vtDownLoadFileData.insert(it, tag_File_Data);

	string strPath = string(get_ProcessPath()) + "downloadfile.ini"; 
	FILE *fp = fopen(strPath.c_str(), "w+");
	if (fp != NULL)
	{
		//д��
		DWORD dwSize = m_vtDownLoadFileData.size();
		fprintf(fp, "%d\n", dwSize);
		for (int i=0; i<dwSize; ++i)
		{
			fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%lld\n%lld\n%d\n",
				m_vtDownLoadFileData[i].strUrl.c_str(),
				m_vtDownLoadFileData[i].strPath.c_str(),
				m_vtDownLoadFileData[i].strFileName.c_str(),
				m_vtDownLoadFileData[i].strCoolie.c_str(),
				m_vtDownLoadFileData[i].strDataPrint.c_str(),
				m_vtDownLoadFileData[i].n64FileSize,
				m_vtDownLoadFileData[i].n64ProgRessPos,
				m_vtDownLoadFileData[i].bOpenFile
				);
		}

		fclose(fp);
	}

	return TRUE;
}


//�޸�һ�������ļ���¼
BOOL CMainDlg::mod_DownloadFileIni(
								   __in int nPos,
								   __in const char *strUrl,
								   __in const char *strSaveFilePath,
								   __in const char *strFileName,
								   __in const char *strCoolie,
								   __in __int64 n64FileSize,
								   __in __int64 n64ProgRessPos,
								   __in const char *strPrint,
								   __in bool bOpenFile
								   )
{
	if (strCoolie == NULL)
	{
		strCoolie = "strCoolie";
	}
	//��������
	tag_Donwload_File_Ini_Data  tag_File_Data;
	tag_File_Data.strUrl = strUrl;
	tag_File_Data.strPath = strSaveFilePath;
	tag_File_Data.strFileName = strFileName;
	tag_File_Data.strDataPrint = strPrint;
	tag_File_Data.strCoolie = strCoolie;
	tag_File_Data.n64FileSize = n64FileSize;
	tag_File_Data.n64ProgRessPos = n64ProgRessPos;
	tag_File_Data.bOpenFile = bOpenFile;

	if (m_vtDownLoadFileData.size() != 0)
	{
		m_vtDownLoadFileData[nPos] = tag_File_Data;
	}

	string strPath = string(get_ProcessPath()) + "downloadfile.ini"; 
	FILE *fp = fopen(strPath.c_str(), "w+");
	if (fp != NULL)
	{
		//д��
		DWORD dwSize = m_vtDownLoadFileData.size();
		fprintf(fp, "%d\n", dwSize);
		for (int i=0; i<dwSize; ++i)
		{
			fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%lld\n%lld\n%d\n",
				m_vtDownLoadFileData[i].strUrl.c_str(),
				m_vtDownLoadFileData[i].strPath.c_str(),
				m_vtDownLoadFileData[i].strFileName.c_str(),
				m_vtDownLoadFileData[i].strCoolie.c_str(),
				m_vtDownLoadFileData[i].strDataPrint.c_str(),
				m_vtDownLoadFileData[i].n64FileSize,
				m_vtDownLoadFileData[i].n64ProgRessPos,
				m_vtDownLoadFileData[i].bOpenFile
				);
		}

		fclose(fp);
	}

	return TRUE;
}


//��ȡ�����ļ�
BOOL CMainDlg::rand_DownloadFileIni(VOID)
{

	string strPath = string(get_ProcessPath()) + "downloadfile.ini"; 
	FILE *fp = fopen(strPath.c_str(), "r");
	if (fp != NULL)
	{
		//��������
		tag_Donwload_File_Ini_Data  tag_File_Data;
		//д��
		DWORD dwSize = 0;
		fscanf(fp, "%d\n", &dwSize);
		for (int i=0; i<dwSize; ++i)
		{
			char strData[1024] = {0};
			fgets(strData, 1024, fp);
			set_StrSign(strData);
			tag_File_Data.strUrl = strData;
			fgets(strData, 1024, fp);
			set_StrSign(strData);
			tag_File_Data.strPath = strData;
			fgets(strData, 1024, fp);
			set_StrSign(strData);
			tag_File_Data.strFileName = strData;
			fgets(strData, 1024, fp);
			set_StrSign(strData);
			tag_File_Data.strCoolie = strData;
			fgets(strData, 1024, fp);
			set_StrSign(strData);
			tag_File_Data.strDataPrint = strData;

			fscanf(fp, "%lld\n%lld\n%d\n", &tag_File_Data.n64FileSize, &tag_File_Data.n64ProgRessPos, &tag_File_Data.bOpenFile);

			m_vtDownLoadFileData.push_back(tag_File_Data);

			create_ListItem(tag_File_Data);

		}

		fclose(fp);
	}

	return TRUE;
}


BOOL CMainDlg::null_DownloadFileIni(VOID)
{
	string strPath = string(get_ProcessPath()) + "downloadfile.ini"; 
	FILE *fp = fopen(strPath.c_str(), "w+");
	if (fp != NULL)
	{
		//д��
		DWORD dwSize = m_vtDownLoadFileData.size();
		fprintf(fp, "%d\n", dwSize);
		for (int i=0; i<dwSize; ++i)
		{
			fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%lld\n%lld\n%d\n",
				m_vtDownLoadFileData[i].strUrl.c_str(),
				m_vtDownLoadFileData[i].strPath.c_str(),
				m_vtDownLoadFileData[i].strFileName.c_str(),
				m_vtDownLoadFileData[i].strCoolie.c_str(),
				m_vtDownLoadFileData[i].strDataPrint.c_str(),
				m_vtDownLoadFileData[i].n64FileSize,
				m_vtDownLoadFileData[i].n64ProgRessPos,
				m_vtDownLoadFileData[i].bOpenFile
				);
		}

		fclose(fp);
		return TRUE;
	}

	return FALSE;
}


//�޳��ַ���\n
void CMainDlg::set_StrSign(__in char *strData)
{
	int nLen = 0;

	while (strData[nLen] != '\0')
	{
		if (strData[nLen] == '\n')
		{
			strData[nLen] = '\0';
		}
		nLen++;
	}
}