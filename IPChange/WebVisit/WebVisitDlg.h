
// WebVisitDlg.h : header file
//

#pragma once
#include "explorer1.h"

#include <afxinet.h>   
#include <string>
#include <vector>
using namespace std;

// CWebVisitDlg dialog
class CWebVisitDlg : public CDialog
{
// Construction
public:
	CWebVisitDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WEBVISIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CExplorer1 m_MyIE;
public:
	static unsigned int __stdcall IPSearch(void* pVoid);
private:
	BOOL GetFirstGoalUrl(const TCHAR* pSrcUrl, TCHAR* pGoalUrl);
	BOOL FillGoalUrlVec(const TCHAR* pFirstGoalUrl);
	BOOL FillIpVec();
	BOOL SetHttpProxy(const TCHAR* pProxyIP, int isproxy);
private:
	int m_totalIp;
	CInternetSession* m_pSession;
	vector<wstring> m_goalUrlVec;
	vector<wstring> m_IpVec;
};
