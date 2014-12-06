
// TimeManageWinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TimeManageWin.h"
#include "TimeManageWinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTimeManageWinDlg �Ի���




CTimeManageWinDlg::CTimeManageWinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeManageWinDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimeManageWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_TYPE, m_treeType);
}

BEGIN_MESSAGE_MAP(CTimeManageWinDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_TYPE_MANAGE, &CTimeManageWinDlg::OnBnClickedButtonTypeManage)
	ON_BN_CLICKED(IDC_BUTTON_TIME_MANAGE, &CTimeManageWinDlg::OnBnClickedButtonTimeManage)
END_MESSAGE_MAP()


// CTimeManageWinDlg ��Ϣ�������

BOOL CTimeManageWinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// Insert a root item using the structure. We must
	// initialize a TVINSERTSTRUCT structure and pass its
	// address to the call. 

	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("United States");

	HTREEITEM hCountry = m_treeType.InsertItem(&tvInsert);

	// Insert subitems of that root. Pennsylvania is
	// a state in the United States, so its item will be a child
	// of the United States item. We won't set any image or states,
	// so we supply only the TVIF_TEXT mask flag. This
	// override provides nearly complete control over the
	// insertion operation without the tedium of initializing
	// a structure. If you're going to add lots of items
	// to a tree, you might prefer the structure override
	// as it affords you a performance win by allowing you
	// to initialize some fields of the structure only once,
	// outside of your insertion loop.

	HTREEITEM hPA = m_treeType.InsertItem(TVIF_TEXT,
		_T("Pennsylvania"), 0, 0, 0, 0, 0, hCountry, NULL);

	// Insert the "Washington" item and assure that it is
	// inserted after the "Pennsylvania" item. This override is 
	// more appropriate for conveniently inserting items with 
	// images.

	HTREEITEM hWA = m_treeType.InsertItem(_T("Washington"),
		0, 0, hCountry, hPA);

	// We'll add some cities under each of the states.
	// The override used here is most appropriate
	// for inserting text-only items.

	m_treeType.InsertItem(_T("Pittsburgh"), hPA, TVI_SORT);
	m_treeType.InsertItem(_T("Harrisburg"), hPA, TVI_SORT);
	m_treeType.InsertItem(_T("Altoona"), hPA, TVI_SORT);

	m_treeType.InsertItem(_T("Seattle"), hWA, TVI_SORT);
	m_treeType.InsertItem(_T("Kalaloch"), hWA, TVI_SORT);
	m_treeType.InsertItem(_T("Yakima"), hWA, TVI_SORT);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTimeManageWinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimeManageWinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTimeManageWinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTimeManageWinDlg::OnBnClickedButtonTypeManage()
{
	// TODO: Add your control notification handler code here
}

void CTimeManageWinDlg::OnBnClickedButtonTimeManage()
{
	// TODO: Add your control notification handler code here
}
