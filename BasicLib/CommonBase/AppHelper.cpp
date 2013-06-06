#include "AppHelper.h"

//unicode转换为MBCS
std::string Unicode2MBCS(LPCWSTR wstr)
{
	if (wstr==NULL)
		return "";

	BOOL bUsedDefaultChar = FALSE;
	int nLen = wcslen(wstr)*2+2;
	char * pNewStr = new char[nLen];
	memset(pNewStr,0,nLen);
	WideCharToMultiByte(CP_ACP,0,wstr,-1,pNewStr,
		nLen,NULL,&bUsedDefaultChar);

	std::string strRet = pNewStr;
	delete [] pNewStr;
	return strRet;
}

//MBCS转换为UNICODE
std::wstring MBCS2Unicode(LPCSTR str)
{
	if (str==NULL)
		return L"";

	int nLen = strlen(str)*2+2;
	WCHAR * pNewStr = new WCHAR[nLen];
	memset(pNewStr,0,nLen);
	MultiByteToWideChar(CP_ACP, 0, str, -1, pNewStr, nLen);
	std::wstring strRet = pNewStr;
	delete [] pNewStr;
	return strRet;
}

//获取程序路径
std::string GetAppPathA()
{
	char sDrive[_MAX_DRIVE];
	char sDir[_MAX_DIR];
	char sFilename[_MAX_FNAME],Filename[_MAX_FNAME];
	char sExt[_MAX_EXT];

	GetModuleFileNameA(NULL, Filename, _MAX_PATH);
	_splitpath(Filename, sDrive, sDir, sFilename, sExt);

	std::string strRet = sDrive;
	sDir[strlen(sDir)-1] = '\0';
	strRet+=sDir;

	return strRet;
}

std::wstring GetAppPathW()
{
	WCHAR sDrive[_MAX_DRIVE];
	WCHAR sDir[_MAX_DIR];
	WCHAR sFilename[_MAX_FNAME],Filename[_MAX_FNAME];
	WCHAR sExt[_MAX_EXT];

	GetModuleFileNameW(NULL, Filename, _MAX_PATH);
	_wsplitpath(Filename, sDrive, sDir, sFilename, sExt);

	std::wstring strRet = sDrive;
	sDir[wcslen(sDir)-1] = '\0';
	strRet+=sDir;

	return strRet;
}

std::string MyGetHostNameA()
{//查询注册表	
	return Unicode2MBCS(MyGetHostNameW().c_str());
}

std::wstring MyGetHostNameW()
{
	WCHAR szHostName[100] = L"";

	HKEY hKey = NULL;
	LONG nRet = 0;

	nRet = RegOpenKeyW(HKEY_LOCAL_MACHINE,
		L"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters",&hKey);

	if (nRet==0)
	{
		ULONG nDataLen = 100;
		RegQueryValueExW(hKey,L"Hostname",NULL,NULL,(UCHAR *)szHostName,&nDataLen);
	}

	return std::wstring(szHostName);
}

BOOL GuidToStringA(const GUID & guid,std::string & str)
{
	std::wstring ws;
	BOOL bRet = GuidToStringW(guid,ws);

	if (bRet==FALSE)
		return FALSE;

	str = Unicode2MBCS(ws.c_str());

	return TRUE;
}

BOOL GuidToStringW(const GUID & guid,std::wstring & str)
{
	LPOLESTR lpOleStr = NULL;
	BOOL bRet = FALSE;
	if (S_OK==StringFromCLSID(guid,&lpOleStr))
	{
		bRet = TRUE;
		str = lpOleStr;
	}

	CoTaskMemFree(lpOleStr);
	return bRet;
}


GUID GUIDFromString( const WCHAR * str )
{
	WCHAR lpsz[256];
	wcscpy(lpsz, str);

	HRESULT hr;
	GUID guid;
	if (lpsz[0] == '{')
	{
		hr = CLSIDFromString(lpsz, &guid);
	}
	else
	{
		std::basic_string<OLECHAR> strGuid;
		strGuid.append(1, '{');
		strGuid.append(lpsz);
		strGuid.append(1, '}');
		hr = CLSIDFromString((LPOLESTR)strGuid.c_str(), &guid);
	}
	//assert(hr == S_OK);
	return guid;
}

GUID GUIDFromString(const char * lpsz)
{
	int   nLen   =   strlen(lpsz)   +   1;
	int   nwLen   =   MultiByteToWideChar(CP_ACP, 0, lpsz, nLen, NULL, 0);
	WCHAR * wlpsz = new WCHAR[nwLen];
	MultiByteToWideChar(CP_ACP, 0, lpsz, nwLen, wlpsz, nwLen);
	HRESULT hr;
	GUID guid;
	if (lpsz[0] == '{')
	{
		hr = CLSIDFromString(wlpsz, &guid);
	}
	else
	{
		std::basic_string<OLECHAR> strGuid;
		strGuid.append(1, '{');
		strGuid.append(wlpsz);
		strGuid.append(1, '}');
		hr = CLSIDFromString((LPOLESTR)strGuid.c_str(), &guid);
	}
	//assert(hr == S_OK);
	return guid;
}
