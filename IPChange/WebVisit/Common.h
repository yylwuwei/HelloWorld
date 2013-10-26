#pragma once

#define MAX_URL_LEN 200
#define MAX_STR_LEN 2000

bool ConvertMultiByteToWideChar(const char* pChar, wchar_t* pWChar, int wLen);

LPBYTE CString_To_LPBYTE(CString str);
