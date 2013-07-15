#include "soci.h"
#include "soci-oracle.h"
#include "ywindb.h"
#include "yoracledb.h"

#include <string>

using namespace soci;
using namespace std;

int COracleDBParameters::AddParamInt(LPCWSTR strKeyName, int iVal, int iParamType)
{
	return RET_ERR;
}

int COracleDBParameters::GetInt(LPCWSTR strKeyName, int *piVal)
{
	return RET_ERR;
}

IDBParameters* soci::COracleDBConnection::CreateParameters()
{
	m_pParameters = new COracleDBParameters();
	return m_pParameters;
}

int COracleDBConnection::ExecProc(LPCWSTR strProName, IDBParameters * pParams, IDBRecordset ** pRecordset)
{
	procedure proc = ((*m_pSql).prepare <<
		"sp_testrs(:output)",
		use(*m_pStInner, "output"));
	proc.execute(1);
	COracleDBRecordset* pRs = new COracleDBRecordset();
	pRs->SetStatement(m_pStInner);
	*pRecordset = pRs;
	return RET_ERR;
}

IDBConnection* COracleDBConnectionFactory::CreateOracleConnection(LPCSTR strSvr,LPCSTR strDb,LPCSTR strUser,LPCSTR strPwd)
{
	session* sql = new session(oracle, "service=192.168.27.120:1521/orcl user=sa password=123456");
	statement* stInner = new statement(*sql);	
	m_pConnection = new COracleDBConnection();
	m_pConnection->SetSession(sql);
	m_pConnection->SetStatement(stInner);
	return m_pConnection;
}

int COracleDBRecordset::MoveNext()
{
//  	string name;
// 	string name2;
//  	string name3;
// 	m_pStInner->exchange(into(name));
// 	m_pStInner->exchange(into(name2));
// 	m_pStInner->exchange(into(name3));
	m_pStInner->fetch();
	return RET_ERR;
}

int COracleDBRecordset::GetInt(LPCWSTR strKeyName, int *piVal)
{
	return RET_ERR;
}