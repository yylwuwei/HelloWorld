
// MFCDlgStudyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDlgStudy.h"
#include "MFCDlgStudyDlg.h"
#include "KDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCDlgStudyDlg dialog




CMFCDlgStudyDlg::CMFCDlgStudyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCDlgStudyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlgStudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCDlgStudyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMFCDlgStudyDlg message handlers

BOOL CMFCDlgStudyDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDlgStudyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDlgStudyDlg::OnPaint()
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

		dc.TextOut(0,0, _T("hello"));
	}
	else
	{
		CDC* pDC = GetDC();
		pDC->TextOut(0,0, _T("hello"));
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCDlgStudyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define IDD_SIMPLEDIALOG 201

BOOL CMFCDlgStudyDlg::PreTranslateMessage(MSG* pMsg)
{
	HINSTANCE hinst = GetModuleHandle(_T("MFCDlgStudy.exe"));
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_F1)
		{
			//MessageBox(_T("F1 key down"));
			

			HWND hwnd; 
			hwnd = CreateWindow( 
				_T("BUTTON"),        // name of window class 
				_T("Hello,Subwnd"),            // title-bar string 
				WS_CHILD |WS_VISIBLE, // top-level window 
				0,       // default horizontal position 
				0,       // default vertical position 
				200,       // default width 
				200,       // default height 
				(HWND) GetSafeHwnd(),         // no owner window 
				(HMENU) NULL,        // use class menu 
				hinst,           // handle to application instance 
				(LPVOID) NULL);      // no window-creation data 
			if (!hwnd) 
			{
				int errCode = GetLastError();
				return FALSE; 
			}
			ShowWindow(SW_SHOW);
			UpdateWindow();
		}
		else if (pMsg->wParam == VK_F2)
		{
//			MessageBox(_T("F2 key down"));

			//m_pSimpleDialog initialized to NULL in the constructor of CMyDialog class
			CAboutDlg* m_pSimpleDlg = new CAboutDlg();
			//Check if new succeeded and we got a valid pointer to a dialog object
			if(m_pSimpleDlg != NULL)
			{
				BOOL ret = m_pSimpleDlg->Create(IDD_ABOUTBOX, this);
				if(!ret)   //Create failed.
					AfxMessageBox(_T("Error creating Dialog"));
				m_pSimpleDlg->ShowWindow(SW_SHOW);
			}
			else
			{
				AfxMessageBox(_T("Error Creating Dialog Object"));
			}
		}
		else if (pMsg->wParam == VK_F3)
		{
			CAboutDlg* m_pSimpleDlg = new CAboutDlg();
			m_pSimpleDlg->DoModal();
			return TRUE;
		}
		else if (pMsg->wParam == VK_F4)
		{
			KDialog dlg(hinst,(HWND) GetSafeHwnd());  
			dlg.DoModal();  
		}
		else if (pMsg->wParam == VK_F5)
		{
// 			CWnd wnd;
// 			BOOL b=wnd.CreateEx (ExStyle, ClassName, WindowName, Style, x, y, Width, Height, Parent, Menu,P a r a m ) ;
		}
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMFCDlgStudyDlg::OnHelp()
{
	return;
}