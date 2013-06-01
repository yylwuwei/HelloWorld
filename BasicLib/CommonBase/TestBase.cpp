#include "StringOption.h"

#include <stdio.h>
#include <tchar.h>

int main()
{
	//test ConverByteArrayToGUIDStringA begin
	byte aByteArray[16] = {229,197,78,31,129,246,66,113,168,7,143,58,186,55,177,79};
	char aStrGUID[100] = {0};
	ConvertByteArrayToGUIDStringA(aByteArray, aStrGUID);
	printf("%s\n", aStrGUID);
	//test ConverByteArrayToGUIDStringA end

	//test ConverByteArrayToGUIDStringW begin
	byte wByteArray[16] = {229,197,78,31,129,246,66,113,168,7,143,58,186,55,177,79};
	wchar_t wStrGUID[100] = {0};
	ConverByteArrayToGUIDStringW(wByteArray, wStrGUID);
	wprintf(_T("%s\n"), wStrGUID);
	//test ConverByteArrayToGUIDStringW end

	//test ConvertCharToWChar begin
	char pStr[] = "hello";
	wchar_t pwStr[100] = {0};
	ConvertCharToWChar(pStr, pwStr);
	wprintf(_T("%s\n"), pwStr);
	//test ConvertCharToWChar end

	//test ConvertWCharToChar begin
	wchar_t pwStr2[] = _T("world");
	char pStr2[100] = {0};
	ConvertWCharToChar(pwStr2, pStr2);
	printf("%s\n", pStr2);
	//test ConvertWCharToChar end

	return 0;
}