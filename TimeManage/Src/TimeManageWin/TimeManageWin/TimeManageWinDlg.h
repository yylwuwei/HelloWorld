
// TimeManageWinDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CTimeManageWinDlg �Ի���
class CTimeManageWinDlg : public CDialog
{
// ����
public:
	CTimeManageWinDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TIMEMANAGEWIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTypeManage();
	afx_msg void OnBnClickedButtonTimeManage();
	CTreeCtrl m_treeType;
};
