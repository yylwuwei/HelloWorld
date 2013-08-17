#pragma once

#include "_Nv_Http_Download.h"
#include <vector>

using std::vector;



//DLL Ҫ�����ĺ���
typedef BOOL (*DLL_SetUrL)			(CHAR *strFileUrl);
typedef BOOL (*DLL_SetClassStr)		(CHAR *strClassStr);
typedef BOOL (*DLL_SetCoolie)		(CHAR *strCoolie);

//��
class _Nv_Download_Ex;

//////////////////////////////////////////////////////////////////////////
//�궨��
#define WM_USER_PROG			WM_USER+100
#define WM_USER_TEXTPRINT		WM_USER+101
#define WM_USER_DELETE_ITEM		WM_USER+102


#define	Thread_OutCode_ProgRess	0x110
#define	Thread_OutCode_Print	0x120
#define Thread_OutCode_Sleep	0x130



//���񷢲������͵Ľṹ��
struct tagDownloadAttriBute
{
	__int64		int64FileSize;
	CHAR		strFileName[1024];
	CHAR		strURL[4096];
	CHAR		strFilePath[1024];
	CHAR		strCollie[4096];
	BOOL		bIsOpen;
	INT			nNameType;

	tagDownloadAttriBute()
	{
		int64FileSize = 0;
		memset(strFilePath, 0, sizeof(strFilePath));
		memset(strURL, 0, sizeof(strURL));
		memset(strFileName, 0, sizeof(strFileName));
		memset(strCollie, 0, sizeof(strCollie));
		bIsOpen	= FALSE;
		nNameType = -1;
	}

	~tagDownloadAttriBute()
	{

	}
};


//��¼�����ļ����ȵĽṹ��
struct tag_Donwload_File_Ini_Data 
{
	string strUrl;
	string strPath;
	string strFileName;
	string strDataPrint;
	string strCoolie;
	__int64 n64ProgRessPos;
	__int64 n64FileSize;
	BOOL	bOpenFile;

	tag_Donwload_File_Ini_Data()
	{
		strUrl =
		strPath = 
		strFileName = 
		strCoolie = 
		strDataPrint = "";

		n64ProgRessPos = 0;
		bOpenFile = FALSE;
	}
};


//�߳��������ݽṹ��
struct tag_Download_Data 
{
	CProgressUI		*pProgress;
	_Nv_Download	*Nv_Download_;
	CTextUI			*pTextPrint;
	INT				nPos;
	CListUI			*pList;
	_Nv_Download_Ex	*pDownloadEx;
	BOOL			bMode;

	tag_Download_Data()
	{
		pProgress = NULL;
		Nv_Download_ = NULL;
		pTextPrint = NULL;
		nPos = 0;
		pList = NULL;
		pDownloadEx = NULL;
		bMode = FALSE;
	}
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CMainDlg : public CWindowWnd, public INotifyUI
{
public:

	//����
	CMainDlg();

	LPCTSTR GetWindowClassName() CONST { return _T("UIMainFrame"); };
	UINT GetClassStyle() CONST { return CS_DBLCLKS; };
	VOID OnFinalMessage(HWND /*hWnd*/) { delete this; };

	VOID OnPrepare() {
	}

	VOID Notify(TNotifyUI& msg);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::PostQuitMessage(0L);

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if( ::IsIconic(*this) ) bHandled = FALSE;
		return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCopyData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//////////////////////////////////////////////////////////////////////////
	//�Զ�����Ϣ
	LRESULT OnUserCloseListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserProg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUserPrint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//////////////////////////////////////////////////////////////////////////
	//���� �ƶ� �ؼ�
	VOID	set_WidthPos	(IN CRichEditUI *pdlg, IN INT nWidth);
	VOID	set_WidthPos	(IN CButtonUI *pdlg, IN INT nWidth);
	VOID	set_WidthPos	(IN CTextUI *pdlg, IN INT nWidth);
	VOID	set_Width		(IN CRichEditUI *pdlg, IN INT nWidth);
	VOID	set_Width		(IN CHorizontalLayoutUI *pdlg, IN INT nWidth);

public:

	//�󶨿ؼ�
	VOID init_BindControls(VOID);
	//��ʼ������
	VOID init_ControlsData(VOID);
	//���һ��list item
	BOOL add_ListItem(CONST CHAR *strUrl, CONST CHAR *strFilePath, BOOL bOpenMode, _Nv_Download_Ex *pdlg);
	//��ȡlist pos
	INT  get_DownloadPtrPos(CControlUI* cContrCmp);
	//��ȡ��ǰӦ�ó���·��
	CHAR *get_ProcessPath(VOID);
	
	//��Ӽ�¼�ļ�
	BOOL add_DownloadFileIni( 
		__in CONST CHAR *strUrl,
		__in CONST CHAR *strSaveFilePath, 
		__in CONST CHAR *strFileName,
		__in __int64 n64FileSize,
		__in CONST CHAR *strCoolie = NULL, 
		__in __int64 n64ProgRessPos = 0, 
		__in CONST CHAR *strPrint = "���ڵȴ�����..", 
		__in bool bOpenFile = false
		);
	//�޸ļ�¼�ļ�
	BOOL mod_DownloadFileIni(
		__in INT nPos,
		__in CONST CHAR *strUrl,
		__in CONST CHAR *strSaveFilePath, 
		__in CONST CHAR *strFileName, 
		__in CONST CHAR *strCoolie,
		__in __int64 n64FileSize,
		__in __int64 n64ProgRessPos, 
		__in CONST CHAR *strPrint, 
		__in bool bOpenFile
		);
	
	//��ȡ���ü�¼�ļ�
	BOOL rand_DownloadFileIni(VOID);
	//����һ��list item
	BOOL create_ListItem(tag_Donwload_File_Ini_Data tag_File_Data);
	//�޳��ַ�����\n
	VOID set_StrSign(__in CHAR *strData);
	BOOL null_DownloadFileIni(VOID);
public:
	//��������
	CPaintManagerUI m_pm;

	//�˳���ť
	CButtonUI		*m_pBtnClose;
	CButtonUI		*m_pBtnMin;
	//�������
	CButtonUI		*m_pBtnAddTask;

	//�����������
	DLL_SetUrL			m_FunSetUrL;
	DLL_SetCoolie		m_FunSetCoolie;
	DLL_SetClassStr		m_FunSetClassStr;
	
	//������
	HINSTANCE		m_hinstance;
	
	//����׷������
	vector<_Nv_Download_Ex*>	m_vt_Nv_Download;
	
	//�������ۼ�
	DWORD			m_dwLinkCount;

	//�������ü���
	INT				m_nTaskCount;
	
	//��¼�����ļ�����
	vector<tag_Donwload_File_Ini_Data>	m_vtDownLoadFileData;
	
};



//������
class _Nv_Download_Ex
{
public:
	//��ʼ��
	_Nv_Download_Ex(){ 
		m_strUrl=""; m_strFileSavePath=""; m_strCoolie=""; m_ListItemPos=-1;
		m_Handle_ProgRess = NULL;
		m_Handle_Print = NULL;
		m_bClose = FALSE;
		Nv_Download_ = NULL;
		m_bOpenFile = NULL;
	};
	~_Nv_Download_Ex(){};
	
	//////////////////////////////////////////////////////////////////////////
	//list item������ָ��
	CListUI						*m_pList;
	CListContainerElementUI		*m_pListElement;
	CVerticalLayoutUI			*m_pVerticalLayout;
	CButtonUI					*m_pBtnIco;
	CTextUI						*m_pTextFile;
	CTextUI						*m_pTextPrint;
	CTextUI						*m_pTextJdtBk;
	CProgressUI					*m_pProgRess;
	CButtonUI					*m_pBtnStop;
	CButtonUI					*m_pBtnGo;
	CButtonUI					*m_pBtnOK;
	CButtonUI					*m_pBtnClose;
	
	//������ָ��
	CMainDlg					*m_pWndPtr;
	
	//���ع�����
	_Nv_Download				*Nv_Download_;

	string						m_strUrl;
	string						m_strFileSavePath;
	string						m_strCoolie;
	
	//��ǰlist��pos
	INT							m_ListItemPos;
	
	//�߳��˳�����
	HANDLE						m_Handle_ProgRess;
	HANDLE						m_Handle_Print;
	
	//�Ƿ�����list
	BOOL						m_bClose;
	//�Ƿ�ֱ�Ӵ��ļ�
	BOOL						m_bOpenFile;
	
	//��ȡ������ָ��
	BOOL	get_WndPtr(CMainDlg *pdlg)
	{
		if (pdlg != NULL)
		{
			m_pWndPtr = pdlg;
			return TRUE;
		}

		return FALSE;
	}
protected:
private:
};