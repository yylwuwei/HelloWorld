#ifndef SOCI_Y_ORACLE_H_INCLUDE
#define SOCI_Y_ORACLE_H_INCLUDE

#ifdef _MSC_VER
#pragma warning(disable:4512 4511)
#endif

namespace soci
{
	class __declspec(dllexport) COracleDBParameters: public IDBParameters 
	{
	public:
		virtual int GetInt(LPCWSTR strKeyName,int * piVal);
		virtual int AddParamInt(LPCWSTR strKeyName, int iVal, int iParamType);
	};

	class __declspec(dllexport) COracleDBConnection: public IDBConnection
	{
	public:
		virtual IDBParameters * CreateParameters();
		virtual int ExecProc(LPCWSTR strProName, IDBParameters * pParams, IDBRecordset ** pRecordset);
		void SetSession(session* pSql)
		{
			m_pSql = pSql;
		}
		void SetStatement(statement* pStatment)
		{
			m_pStInner = pStatment;
		}
	private:
		COracleDBParameters* m_pParameters;
		session* m_pSql;
		statement* m_pStInner;
	};

	class __declspec(dllexport) COracleDBConnectionFactory: public IDBConnectionFactory
	{
	public:
		virtual IDBConnection * CreateOracleConnection(LPCSTR strSvr,LPCSTR strDb,LPCSTR strUser,LPCSTR strPwd);
	private:
		COracleDBConnection* m_pConnection;
	};

	class __declspec(dllexport) COracleDBRecordset: public IDBRecordset
	{
	public:
		virtual int MoveNext();
		virtual int GetInt(LPCWSTR strKeyName,int * piVal);
		void SetStatement(statement* pStatment)
		{
			m_pStInner = pStatment;
		}
	private:
		statement* m_pStInner;
	};
}

#endif