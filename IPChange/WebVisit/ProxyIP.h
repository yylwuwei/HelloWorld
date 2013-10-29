#pragma once

#include <afxinet.h>   
#include <string>
#include <vector>
using namespace std;

class CProxyIP
{
public:
	CProxyIP();
	~CProxyIP();
public:
	void Start();
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