#pragma once

#include <Windows.h>

int ConvertByteArrayToGUIDStringA(byte byteArray[16], char* pStr);

int ConverByteArrayToGUIDStringW(byte byteArray[16], wchar_t* pwStr);

int ConvertCharToWChar(char* pStr, wchar_t* pwStr);

int ConvertWCharToChar(wchar_t* pwStr, char* pStr);