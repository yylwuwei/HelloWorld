#include "stdafx.h"
#include "ProxyIP.h"

#include "Common.h"

extern HANDLE g_hIPChange;

CProxyIP::CProxyIP()
{

}

CProxyIP::~CProxyIP()
{

}

unsigned int __stdcall CProxyIP::IPSearch(void* pVoid)
{
	return 0;
}

void CProxyIP::Start()
{
	// TODO: Add your control notification handler code here

	// 	HINTERNET hOpen = InternetOpen(_T("Testing"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	// 	if (hOpen == NULL)
	// 	{
	// 		AfxMessageBox(_T("InternetOpen Error ! "));
	// 		//continue;
	// 	}
	// 	HINTERNET hOpenUrl = InternetOpenUrl(hOpen, _T("http://shop72772786.taobao.com/"), NULL, 0, INTERNET_FLAG_RESYNCHRONIZE, 0);
	// 	if (hOpenUrl == NULL)
	// 	{
	// 		AfxMessageBox(_T("InternetOpenUrl Error! "));
	// 		//continue;
	// 	}

// 	HANDLE handleIP = (HANDLE)_beginthreadex(NULL, 0, IPSearch, NULL, 0, NULL);


	m_totalIp = 0;
	m_pSession = new CInternetSession(_T("HttpClient_YYL"));

	TCHAR* pSrcUrl = _T("http://www.youdaili.cn/");
	TCHAR firstGoalUrl[MAX_URL_LEN] = {0};
	GetFirstGoalUrl(pSrcUrl, firstGoalUrl);

	m_goalUrlVec.push_back(firstGoalUrl);
	FillGoalUrlVec(firstGoalUrl);

	FillIpVec();

	for (int i = 0; i < m_IpVec.size(); i++)
	{
		int loc = m_IpVec[i].find(_T("@"));
		wstring strIP = m_IpVec[i].substr(0, loc);
		WaitForSingleObject(g_hIPChange, INFINITE);
		SetHttpProxy(strIP.c_str() ,1);
		//m_MyIE.Navigate(_T("http://shop72772786.taobao.com/"), NULL, NULL, NULL, NULL);
		Sleep(10000);
	}

	AfxMessageBox(_T("IP change ok! "));

	m_pSession->Close();
	delete m_pSession;

}

BOOL CProxyIP::GetFirstGoalUrl(const TCHAR* pSrcUrl, TCHAR* pGoalUrl)
{
	BOOL bRet = FALSE;
	CHttpFile* pHttpFile = (CHttpFile *)m_pSession->OpenURL(pSrcUrl);
	DWORD dwStatusCode = 0;
	pHttpFile->QueryInfoStatusCode(dwStatusCode);
	if (dwStatusCode == HTTP_STATUS_OK)
	{
		CString strData;
		wstring subStr = _T("国内网页http代理ip地址服务器");
		while(pHttpFile->ReadString(strData))
		{
			TCHAR mainStr[MAX_STR_LEN] = {0};
			ConvertMultiByteToWideChar((char *)strData.GetBuffer(), mainStr, MAX_STR_LEN);
			wstring wMainStr = mainStr;
			if (wMainStr.find(subStr) < wMainStr.length())
			{
				int startLoc = wMainStr.find(_T("href"));
				int endLoc = wMainStr.find(_T("title"));
				endLoc -= 2;
				startLoc += 6;
				wstring wTempUrl = wMainStr.substr(startLoc, endLoc-startLoc).c_str();
				wmemcpy(pGoalUrl, wTempUrl.c_str(), wcslen(wTempUrl.c_str())+1);
				bRet = TRUE;
				break;
			}
		}
	}
	pHttpFile->Close();
	delete pHttpFile;
	return bRet;
}

BOOL CProxyIP::FillGoalUrlVec(const TCHAR* pFirstGoalUrl)
{
	BOOL bRet = FALSE;
	int totalPage = 0;
	CHttpFile* pHttpFile = (CHttpFile *)m_pSession->OpenURL(pFirstGoalUrl);
	DWORD dwStatusCode = 0;
	pHttpFile->QueryInfoStatusCode(dwStatusCode);
	if (dwStatusCode == HTTP_STATUS_OK)
	{
		BOOL bCheck = FALSE;
		CString strData;
		wstring subStrPage = _T("class=\"pagelist\"");
		while(pHttpFile->ReadString(strData))
		{
			TCHAR mainStr[MAX_STR_LEN] = {0};
			ConvertMultiByteToWideChar((char *)strData.GetBuffer(), mainStr, MAX_STR_LEN);
			wstring wMainStr = mainStr;
			if (bCheck)
			{
				int lenn = wMainStr.find(_T("共"));
				wstring wsPage = wMainStr.substr(lenn+1, 1).c_str();
				totalPage = _wtoi(wsPage.c_str());	
				bCheck = FALSE;
				break;
			}

			if (wMainStr.find(subStrPage) < wMainStr.length())
			{
				bCheck = TRUE;
			}

		}

		wstring strGoalUrl = pFirstGoalUrl;
		int lenHtml = strGoalUrl.find(_T(".html"));
		wstring newStrGoalUrl = strGoalUrl.substr(0, lenHtml);
		for (int j = 2; j <= totalPage; j++)
		{
			TCHAR tChar[MAX_URL_LEN] = {0};
			swprintf(tChar, MAX_URL_LEN, _T("%s_%d.html"), newStrGoalUrl.c_str(), j);
			m_goalUrlVec.push_back(tChar);
		}
		bRet = TRUE;
	}
	pHttpFile->Close();
	delete pHttpFile;
	return bRet;
}

BOOL CProxyIP::FillIpVec()
{
	int i = 0;
	for (i = 0; i < m_goalUrlVec.size(); i++)
	{
		CHttpFile* pHttpFile = (CHttpFile *)m_pSession->OpenURL(m_goalUrlVec[i].c_str());
		DWORD dwStatusCode = 0;
		pHttpFile->QueryInfoStatusCode(dwStatusCode);
		if (dwStatusCode == HTTP_STATUS_OK)
		{
			BOOL bCheck = FALSE;
			CString strData;
			wstring subStr = _T("class=\"cont_ad\"");
			while(pHttpFile->ReadString(strData))
			{
				TCHAR mainStr[MAX_STR_LEN] = {0};
				ConvertMultiByteToWideChar((char *)strData.GetBuffer(), mainStr, MAX_STR_LEN);
				wstring wMainStr = mainStr;
				if (bCheck)
				{
					if (wMainStr.find(_T("</span>")) < wMainStr.length())
					{
						break;
					}
					TCHAR firstPosChar = wMainStr.at(0);
					if (firstPosChar < 48 || firstPosChar > 57)
					{
						continue;
					}
					m_IpVec.push_back(wMainStr);
					m_totalIp++;
				}
				if (wMainStr.find(subStr) < wMainStr.length())
				{
					bCheck = TRUE;
				}
			}
		}
		pHttpFile->Close();
		delete pHttpFile;
	}
	return TRUE;
}

BOOL CProxyIP::SetHttpProxy(const TCHAR* pProxyIP, int isproxy)
{
	CString ipstr = pProxyIP;
	HKEY hKEY;
	LPCTSTR data_Set= _T("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	//访问注册表，hKEY则保存此函数所打开的键的句柄
	long ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_WRITE,&hKEY));
	if(ret0!=ERROR_SUCCESS)						//如果无法打开hKEY,则中止程序的执行
	{
		AfxMessageBox(_T("错误：无法打开有关的hKEY"));
		return FALSE;
	}

	//打开局域网代理
	DWORD type = REG_DWORD ;					//定义数据类型

	long ret1=::RegSetValueEx(hKEY, _T("ProxyEnable"), NULL, type, (LPBYTE)(&isproxy), 4);
	if(ret1!=ERROR_SUCCESS)
	{
		AfxMessageBox(_T("错误：无法设置有关的注册表信息"));
		return FALSE;
	}

	LPBYTE owner_Set=CString_To_LPBYTE(pProxyIP);	//定义用户姓名 owner_Set
	type = REG_SZ ;								//定义数据类型
	//int len = str.GetLength();			//定义数据长度
	int len = wcslen(pProxyIP);

	ret1 = ::RegSetValueExA(hKEY, "ProxyServer", NULL, type, owner_Set, len);

	// 	ret1=::RegSetValueEx(hKEY, _T("ProxyServer"), NULL, type, owner_Set, len);
	if(ret1!=ERROR_SUCCESS)
	{
		AfxMessageBox(_T("错误：无法设置有关的注册表信息"));
		return FALSE;
	}

	//单独网络上网
	data_Set=_T("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections");
	//访问注册表，hKEY则保存此函数所打开的键的句柄
	ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_WRITE,&hKEY));
	if(ret0!=ERROR_SUCCESS)						//如果无法打开hKEY,则中止程序的执行
	{
		AfxMessageBox(_T("错误：无法打开有关的hKEY"));
		return FALSE;
	}

	type = REG_BINARY ;					//定义数据类型
	UCHAR szBuf[80] = {0}; 
	szBuf[0] = 0x3c;
	szBuf[4] = 0x09;
	if ( 1 == isproxy  )
	{
		szBuf[8] = 0x03;
	}else
	{
		szBuf[8] = 0x01;
	}
	szBuf[12] = wcslen(pProxyIP); //str.GetLength();
	int i = 0;
	for (i = 0; i < len; i++ )
	{
		szBuf[i+ 16] = pProxyIP[i];// str[i] ;
	}

	CString local = _T("<local>");
	for (i = 0; i < 7; i++ )
	{
		szBuf[20 + wcslen(pProxyIP) + i] = local[i];
	}

	ret1=::RegSetValueEx(hKEY, _T("宽带连接"), NULL, type, (LPBYTE)(szBuf), 80);

	if(ret1!=ERROR_SUCCESS)
	{
		AfxMessageBox(_T("错误：无法设置有关的注册表信息"));
		return FALSE;
	}

	RegCloseKey(hKEY);

	InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);		//通知注册表中代理改变,下次连接时启动代理
	InternetSetOption(NULL ,INTERNET_OPTION_REFRESH , NULL, 0);				//从注册表中读入代理


	return TRUE;

}

