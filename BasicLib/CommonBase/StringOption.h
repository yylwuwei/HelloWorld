#pragma once

#include <Windows.h>

BOOL ConvertByteArrayToGUIDStringA(byte byteArray[16], char* pStr);

BOOL ConvertByteArrayToGUIDStringW(byte byteArray[16], wchar_t* pwStr);

BOOL ConvertCharToWChar(char* pStr, wchar_t* pwStr);

BOOL ConvertWCharToChar(wchar_t* pwStr, char* pStr);

#ifdef _UNICODE
#define ConvertByteArrayToGUIDString ConvertByteArrayToGUIDStringW
#else
#define ConvertByteArrayToGUIDString ConvertByteArrayToGUIDStringA
#endif