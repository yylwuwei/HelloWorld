#include "stdafx.h"
#include "Common.h"

bool ConvertMultiByteToWideChar(const char* pChar, wchar_t* pWChar, int wLen)
{
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, pChar, -1, NULL, 0);
	if (wLen > unicodeLen)
	{
		memset(pWChar, 0, (wLen)*sizeof(wchar_t));
		::MultiByteToWideChar(CP_UTF8, 0, pChar, -1, (LPWSTR)pWChar, unicodeLen);
		return true;
	}
	return false;	
}

LPBYTE CString_To_LPBYTE(CString str)
{
	LPBYTE lpb=new BYTE[str.GetLength()+1];
	for(int i=0;i<str.GetLength();i++)
		lpb[i]=str[i];
	lpb[str.GetLength()]=0;
	return lpb;
}
