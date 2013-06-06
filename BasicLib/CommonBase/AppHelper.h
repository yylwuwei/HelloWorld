#pragma once

#include <Windows.h>
#include <string>

std::string Unicode2MBCS(LPCWSTR wstr);
std::wstring MBCS2Unicode(LPCSTR str);
std::string GetAppPathA();
std::wstring GetAppPathW();
std::string MyGetHostNameA();
std::wstring MyGetHostNameW();
BOOL GuidToStringA(const GUID & guid,std::string & str);
BOOL GuidToStringW(const GUID & guid,std::wstring & str);
GUID GUIDFromString( const WCHAR * str );
GUID GUIDFromString(const char * lpsz);