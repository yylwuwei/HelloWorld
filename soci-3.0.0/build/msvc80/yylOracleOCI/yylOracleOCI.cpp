// yylOracleOCI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <oci.h>

void checkerr0(void* handle, ub4 htype, sword status)
{
	text errbuf[2048];
	sb4 errcode = 0;
	switch(status)
	{
	case OCI_SUCCESS:
		break;
	case OCI_SUCCESS_WITH_INFO:
		(void)printf("Error - OCI_SUCCESS_WITH_INFO\n");
		break;
	case OCI_NEED_DATA:
		(void)printf("Error - OCI_NEED_DATA\n");
		break;
	case OCI_NO_DATA:
		(void)printf("Error - OCI_NODATA\n");
		break;
	case OCI_ERROR:
		(void)printf("Error - OCI_ERROR\n");
		if (handle)
		{
			(void)OCIErrorGet(handle, 1, (text *)NULL, &errcode,
				errbuf, (ub4)sizeof(errbuf), htype);
			(void)printf("Error - %d. %s\n", sizeof(errbuf), errbuf);
		}
		else
		{
			(void)printf("NULL handle\n");
		}
		exit(1);
		break;
	case OCI_INVALID_HANDLE:
		(void)printf("Error - OCI_INVALID_HANDLE\n");
		exit(1);
		break;
	case OCI_STILL_EXECUTING:
		printf("Error - OCI_STILL_EXECUTING\n");
		break;
	case OCI_CONTINUE:
		printf("Error - OCI_CONTINUE\n");
		break;
	default:
		break;
	}
}

#define checkerr(errhp, status) checkerr0((errhp), OCI_HTYPE_ERROR, (status))
#define checkenv(envhp, status) checkerr0((envhp), OCI_HTYPE_ENV, (status))

char* my_select = (char *)"select * from PQRSTest where INT2 = :EMPNO";
//static const text * plsql_block = (text *)"begin open :cursor1 for select * from PQRSTEST; end;";
static const text * plsql_block = (text *)"begin sp_testrs(:cursor1); end;";
char* connstr = (char *)"192.168.27.120:1521/orcl";
OCIAuthInfo* authp = NULL;
OCISvcCtx* svchp = NULL;
OCIError* errhp = NULL;
OCIEnv* envhp = (OCIEnv *)NULL;
//ub2 charset = getCharSetIdFromName(charSetName);

void select_emp_details(OCISvcCtx* svchp, ub4 empno)
{
	OCIStmt* stmthp;
	OCIStmt* stm2p;
	OCIBind* bndp1;
	OCIDefine* defhp1;

	ub4 num_rows = 1;
	char string2[100];
	sword status;

	printf("demonstrating single row select \n");

	
	status = OCIHandleAlloc(envhp,
		reinterpret_cast<dvoid**>(&stmthp),
		OCI_HTYPE_STMT, 0, 0);

	
	checkerr(errhp, OCIStmtPrepare(stmthp, errhp, (text *)plsql_block,
		strlen((char *)plsql_block), OCI_NTV_SYNTAX, OCI_DEFAULT));

// 	checkerr(errhp, OCIStmtPrepare2(svchp,
// 		&stmthp,
// 		errhp,
// 		(const OraText *)plsql_block,
// 		strlen((char *)plsql_block),
// 		NULL, 0,
// 		OCI_NTV_SYNTAX, OCI_DEFAULT));

	status =OCIHandleAlloc(envhp, (void **)(&stm2p), OCI_HTYPE_STMT, 0, NULL);

	checkerr(errhp, OCIBindByName(stmthp, (OCIBind **)&bndp1, errhp,
		(text *)":cursor1", (sb4)strlen((char *)":cursor1"), 
		(dvoid *)&stm2p, (sb4)0, SQLT_RSET, (dvoid *)0,
		(ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, (ub4)OCI_DEFAULT));

	int colCount;
// 	checkerr(errhp, OCIStmtExecute(svchp, stmthp, errhp,1, 0, 0, 0, OCI_DESCRIBE_ONLY)); 
// 	checkerr(errhp, OCIAttrGet(static_cast<dvoid*>(stmthp),
// 		static_cast<ub4>(OCI_HTYPE_STMT), static_cast<dvoid*>(&colCount),
// 		0, static_cast<ub4>(OCI_ATTR_PARAM_COUNT), errhp));
	
	checkerr(errhp, OCIStmtExecute(svchp, stmthp, errhp, 1, 0,
		(OCISnapshot *)NULL, (OCISnapshot *)NULL,
		OCI_COMMIT_ON_SUCCESS));

	OCIAttrGet( stm2p, OCI_HTYPE_STMT, &colCount, 0, OCI_ATTR_PARAM_COUNT, errhp );

	checkerr(errhp, OCIDefineByPos(stm2p, &defhp1, errhp, 1,
		(void *)&string2, (sb4)sizeof(string2),
		SQLT_STR, (void *)NULL, (ub2 *)NULL,
		(ub2 *)NULL, OCI_DEFAULT));

	status = OCIStmtFetch(stm2p, errhp, num_rows, OCI_FETCH_NEXT, OCI_DEFAULT);

	if (status == OCI_SUCCESS)
	{
		printf("string2: %s\n", string2);
	}
	else
	{
		checkerr(errhp, status);
	}
	
	
	/*
	checkerr(errhp, OCIStmtPrepare2(svchp,
									&stmthp,
									errhp,
									(const OraText *)my_select,
									strlen((char *)my_select),
									NULL, 0,
									OCI_NTV_SYNTAX, OCI_DEFAULT));
	
	checkerr(errhp, OCIBindByName(stmthp, &bndp1, errhp, (text *)":EMPNO",
		-1, (void *)&empno,
		sizeof(empno), SQLT_INT, (void *)NULL,
		(ub2 *)NULL, (ub2 *)NULL, 0, (ub4 *)NULL,
		OCI_DEFAULT));

	status =OCIHandleAlloc(envhp, (void **)(&stm2p), OCI_HTYPE_STMT, 0, NULL);

	checkerr(errhp, OCIDefineByPos(stmthp, &defhp1, errhp, 1,
		(void *)&stm2p, (sb4)0,
		SQLT_STR, (void *)NULL, (ub2 *)NULL,
		(ub2 *)NULL, OCI_DEFAULT));

	checkerr(errhp, OCIDefineByPos(stm2p, &defhp1, errhp, 1,
		(void *)&string2, (sb4)sizeof(string2),
		SQLT_STR, (void *)NULL, (ub2 *)NULL,
		(ub2 *)NULL, OCI_DEFAULT));

	checkerr(errhp, OCIStmtExecute(svchp, stmthp, errhp, 0, 0,
		(OCISnapshot *)NULL, (OCISnapshot *)NULL,
		OCI_DEFAULT ));

// 	checkerr(errhp, OCIDefineByPos(stmthp, &defhp1, errhp, 1,
// 		(void *)&string2, (sb4)sizeof(string2),
// 		SQLT_STR, (void *)NULL, (ub2 *)NULL,
// 		(ub2 *)NULL, OCI_DEFAULT));

	status = OCIStmtFetch(stmthp, errhp, num_rows, OCI_FETCH_NEXT, OCI_DEFAULT);
	if (status == OCI_SUCCESS)
	{
		printf("string2: %s\n", string2);
	}
	else
	{
		checkerr(errhp, status);
	}
	status = OCIStmtFetch(stm2p, errhp, num_rows, OCI_FETCH_NEXT, OCI_DEFAULT);

	
	//status = OCIStmtFetch2(stmthp, errhp, num_rows, OCI_FETCH_LAST,(sb4) 0, OCI_DEFAULT);

	//status = OCIStmtFetch(stmthp, errhp, num_rows, OCI_FETCH_NEXT, OCI_DEFAULT);

	if (status == OCI_SUCCESS)
	{
		printf("string2: %s\n", string2);
	}
	else
	{
		checkerr(errhp, status);
	}
	*/
	
	checkerr(errhp, OCIStmtRelease(stmthp, errhp,
									(OraText *)NULL,
									0, OCI_DEFAULT));
}

int _tmain(int argc, _TCHAR* argv[])
{

	checkenv(envhp, OCIEnvCreate(&envhp,
								OCI_DEFAULT,
								NULL, NULL, NULL, NULL,
								(size_t)0,
								(void **)NULL));

	//allocate error handle
	checkenv(envhp, OCIHandleAlloc(envhp,
									(void **)&errhp,
									OCI_HTYPE_ERROR,
									(size_t) 0,
									(void **)NULL));

	//allocate auth handle
	checkenv(envhp, OCIHandleAlloc(envhp,
		(void **)&authp, OCI_HTYPE_AUTHINFO,
		(size_t)0, (void **)NULL));
	
	//setup username and password
	checkerr(errhp, OCIAttrSet(authp, OCI_HTYPE_AUTHINFO,
		(void *)"sa", strlen((char *)"sa"),
		OCI_ATTR_USERNAME, errhp));
	checkerr(errhp, OCIAttrSet(authp, OCI_HTYPE_AUTHINFO,
		(void *)"123456", strlen((char *)"123456"),
		OCI_ATTR_PASSWORD, errhp));
	
	//get the database connection
	checkerr(errhp, OCISessionGet(envhp, errhp,
		&svchp,
		authp,
		(OraText *)connstr, strlen(connstr),
		NULL, 0, NULL, NULL, NULL,
		OCI_DEFAULT));

	//....
	select_emp_details(svchp, 88);

	//destroy the connection
	checkerr(errhp, OCISessionRelease(svchp, errhp, NULL, 0, OCI_DEFAULT));
	(void)OCIHandleFree(authp, OCI_HTYPE_AUTHINFO);

	return 0;
}