#pragma once

#include <Windows.h>

int ConvertByteArrayToGUIDStringA(byte byteArray[16], char* pStr);

int ConverByteArrayToGUIDStringW(byte byteArray[16], wchar_t* pStr);