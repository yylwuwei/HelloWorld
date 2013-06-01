#include "StringOption.h"

#include <stdio.h>
#include <tchar.h>

#include "Constant.h"

int ConvertByteArrayToGUIDStringA(byte byteArray[16], char* paStrGUID)
{
	sprintf(paStrGUID,
		"{%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		byteArray[0],byteArray[1],byteArray[2],byteArray[3],byteArray[4],byteArray[5],byteArray[6],byteArray[7],
		byteArray[8],byteArray[9],byteArray[10],byteArray[11],byteArray[12],byteArray[13],byteArray[14],byteArray[15]);
	return RET_OK;
}

int ConverByteArrayToGUIDStringW(byte byteArray[16], wchar_t* pwStrGUID)
{
	swprintf(pwStrGUID,
		_T("{%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X}"), 
		byteArray[0],byteArray[1],byteArray[2],byteArray[3],byteArray[4],byteArray[5],byteArray[6],byteArray[7],
		byteArray[8],byteArray[9],byteArray[10],byteArray[11],byteArray[12],byteArray[13],byteArray[14],byteArray[15]);
	return RET_OK;
}