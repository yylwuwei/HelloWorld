#ifndef SOCI_Y_WINDB_H_INCLUDE
#define SOCI_Y_WINDB_H_INCLUDE

const int RET_ERR = -1;
const int RET_OK = 1;

#ifdef _MSC_VER
#pragma warning(disable:4512 4511)
#endif

namespace soci
{

class __declspec(dllexport)  IDBParameters 
{
public:
	virtual int GetInt(LPCWSTR strKeyName,int * piVal) = 0;
	virtual int AddParamInt(LPCWSTR strKeyName, int iVal, int iParamType) = 0;
};

class __declspec(dllexport)  IDBRecordset
{
public:
	virtual int MoveNext() = 0;
	virtual int GetInt(LPCWSTR strKeyName,int * piVal) = 0;
};

class __declspec(dllexport)  IDBConnection
{
public:
	virtual IDBParameters * CreateParameters() = 0;
	virtual int ExecProc(LPCWSTR strProName, IDBParameters * pParams, IDBRecordset ** pRecordset) = 0;
};

class __declspec(dllexport)  IDBConnectionFactory
{
public:
	virtual IDBConnection * CreateOracleConnection(LPCSTR strSvr,LPCSTR strDb,LPCSTR strUser,LPCSTR strPwd) = 0;
};


}

#endif