#include "StringOption.h"

#include <stdio.h>
#include <tchar.h>

#include "Constant.h"

int ConvertByteArrayToGUIDStringA(byte byteArray[16], char* paStrGUID)
{
	int ret = sprintf(paStrGUID,
		"{%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		byteArray[0],byteArray[1],byteArray[2],byteArray[3],byteArray[4],byteArray[5],byteArray[6],byteArray[7],
		byteArray[8],byteArray[9],byteArray[10],byteArray[11],byteArray[12],byteArray[13],byteArray[14],byteArray[15]);
	if (-1 == ret)
	{
		return RET_ERR;
	}
	return RET_OK;
}

int ConverByteArrayToGUIDStringW(byte byteArray[16], wchar_t* pwStrGUID)
{
	int ret = swprintf(pwStrGUID,
		_T("{%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X}"), 
		byteArray[0],byteArray[1],byteArray[2],byteArray[3],byteArray[4],byteArray[5],byteArray[6],byteArray[7],
		byteArray[8],byteArray[9],byteArray[10],byteArray[11],byteArray[12],byteArray[13],byteArray[14],byteArray[15]);
	if (-1 == ret)
	{
		return RET_ERR;
	}
	return RET_OK;
}

int ConvertCharToWChar(char* pStr, wchar_t* pwStr)
{
	int nLen = strlen(pStr)+1;
	int nwLen = MultiByteToWideChar(CP_ACP, 0, pStr, nLen, NULL, 0);
	int ret = MultiByteToWideChar(CP_ACP, 0, pStr, nLen, pwStr, nwLen);
	if (0 == ret)
	{
		return RET_ERR;
	}
	return RET_OK;
}

int ConvertWCharToChar(wchar_t* pwStr, char* pStr)
{
	int nwLen = wcslen(pwStr)+1;  
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwStr, nwLen, NULL, 0, NULL, NULL);
	int ret = WideCharToMultiByte(CP_ACP, 0, pwStr, nwLen, pStr, nwLen, NULL, NULL);
	if (0 == ret)
	{
		return RET_ERR;
	}
	return RET_OK;
}

