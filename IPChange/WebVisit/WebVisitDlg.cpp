
// WebVisitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebVisit.h"
#include "WebVisitDlg.h"

#include "Common.h"
#include "ProxyIP.h"

#include <process.h>

#include <MsHTML.h>
#include <atlbase.h>
#include <OleAcc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE g_hIPChange;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWebVisitDlg dialog




CWebVisitDlg::CWebVisitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebVisitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebVisitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_MyIE);
}

BEGIN_MESSAGE_MAP(CWebVisitDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CWebVisitDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWebVisitDlg message handlers

BOOL CWebVisitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//SetTimer(1, 10000, NULL);
	g_hIPChange = CreateEvent(NULL,TRUE,TRUE,NULL);  

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWebVisitDlg::OnTimer(UINT_PTR nIDEvent)
{
	ResetEvent(g_hIPChange);
	m_MyIE.Navigate(_T("http://shop72772786.taobao.com/"), NULL, NULL, NULL, NULL);
// 	m_MyIE.CloseWindow();
	SetEvent(g_hIPChange);

	CDialog::OnTimer(nIDEvent);
}

void CWebVisitDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWebVisitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWebVisitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


unsigned int __stdcall CWebVisitDlg::DealIP(void *pVoid)
{
	CProxyIP m_proxyIP;
	m_proxyIP.Start();
	return 0;
}

unsigned int __stdcall CWebVisitDlg::VisitWeb(void* pVoid)
{
	CExplorer1* pExplorer1 = (CExplorer1*)pVoid;
	pExplorer1->Navigate(_T("http://shop72772786.taobao.com/"), NULL, NULL, NULL, NULL);
	return 0;
}

void CWebVisitDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	//cookie option, failed
// 	HRESULT hr;
// 	IDispatch* lpDispatch;
// 
// 	lpDispatch = m_MyIE.get_Document();
// 	IHTMLDocument2* lpDocument2;
// 	hr = lpDispatch->QueryInterface(IID_IHTMLDocument2, (PVOID*)&lpDocument2);
// 	if (hr == S_OK)
// 	{
// 		BSTR bstrCookie;
// 
// // 		lpDocument2->put_cookie();
// 
// 		hr = lpDocument2->get_cookie(&bstrCookie);
// 		if (hr == S_OK)
// 		{
// 			CString strCookie(bstrCookie);
// 			::MessageBox(NULL, strCookie, NULL, 0);
// 			SysFreeString(bstrCookie);
// 		}
// 		lpDocument2->Release();
// 	}
// 	lpDispatch->Release();

	m_MyIE.Navigate(_T("http://shop72772786.taobao.com/"), NULL, NULL, NULL, NULL);


// 	HANDLE hDealIP = (HANDLE)_beginthreadex(NULL, 0, DealIP, NULL, 0, NULL);
	//HANDLE hVisitWeb = (HANDLE)_beginthreadex(NULL, 0, VisitWeb, &m_MyIE, 0, NULL);

// 	WaitForSingleObject(hDealIP, INFINITE);
	//WaitForSingleObject(hVisitWeb, INFINITE);

// 	CloseHandle(hDealIP);
	//CloseHandle(hVisitWeb);


}