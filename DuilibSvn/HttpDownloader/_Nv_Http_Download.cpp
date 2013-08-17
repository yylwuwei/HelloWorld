#include "StdAfx.h"
#include "_Nv_Http_Download.h"



//////////////////////////////////////////////////////////////////////////
//�̺߳���
void Thread_Download_Task(void *vpPtr)
{
	_Nv_Download_Task *Nv_Download_ = (_Nv_Download_Task*)vpPtr;
	
	//���ؽ�������
	BOOL bRet = Nv_Download_->NvDownload_Task(Nv_Download_->strFilePath_.c_str());

	if (bRet == FALSE)
	{
		DegMsg("һ�������̳߳�����...");
		//δ�������
		Nv_Download_->NvInternetCloseHandle(NULL);
		Nv_Download_->dwTaskOk_ = Thread_ON;
		_endthreadex(Thread_download_Ok);
		return;
	}

	//��ͣ����
	DWORD dwRet = WaitForSingleObject(Nv_Download_->Handle_Stop_Download_, 0);

	//�����ɹ�
	if (dwRet == WAIT_OBJECT_0)
	{
		DegMsg("�̰߳�ȫ�ر�");
		Nv_Download_->Handle_Stop_Download_ = NULL;
		Nv_Download_->NvInternetCloseHandle(NULL);
		//�ر��߳� ���ô���
		_endthreadex(Thread_download_Out);
		return;
	}
	
	//�������
	Nv_Download_->NvInternetCloseHandle(NULL);
	Nv_Download_->dwTaskOk_ = Thread_OK;
	_endthreadex(Thread_download_Ok);
}

//�̺߳���
void Thread_Download(void *vpPtr)
{
	_Nv_Download *Nv_Download_ = (_Nv_Download*)vpPtr;
	
	if (Nv_Download_->strCoolie_.length() != 0)
		Nv_Download_->thread_Task(Nv_Download_->strUrl_.c_str(), Nv_Download_->strFileSavePath_.c_str(), Nv_Download_->strCoolie_.c_str());
	else
		Nv_Download_->thread_Task(Nv_Download_->strUrl_.c_str(), Nv_Download_->strFileSavePath_.c_str(), NULL);

	_endthreadex(Thread_Download_Fun);
}

void Thread_OneDownload(void *vpPtr)
{
	_Nv_Download *Nv_Download_ = (_Nv_Download*)vpPtr;

	if (Nv_Download_->strCoolie_.length() != 0)
		Nv_Download_->thread_OneTask(Nv_Download_->strUrl_.c_str(), Nv_Download_->strFileSavePath_.c_str(), Nv_Download_->strCoolie_.c_str());
	else
		Nv_Download_->thread_OneTask(Nv_Download_->strUrl_.c_str(), Nv_Download_->strFileSavePath_.c_str(), NULL);

	_endthreadex(Thread_Download_Fun);
}


//�̺߳���
void Thread_DetectTask(void *vpPtr)
{
	_Nv_Download *Nv_Download_ = (_Nv_Download*)vpPtr;

	while (TRUE)
	{
		//
		DWORD dwRet = WaitForSingleObject(Nv_Download_->Handle_DetectTask_Out_, 0);

		//�����ɹ�
		if (dwRet == WAIT_OBJECT_0)
		{
			//�����߳̾��
			BOOL bRet = CloseHandle(Nv_Download_->Handle_DetectTask_Out_);

			Nv_Download_->Handle_DetectTask_Out_ = NULL;
			DegMsg("Thread_DetectTask OUT....");
			//�ر��߳� ���ô���
			_endthreadex(Thread_download_Ok);
			return;
		}

		Nv_Download_->detect_vtThread_Task();
		Sleep(10);
	}
}

void Thread_DetectOneTask(void *vpPtr)
{
	_Nv_Download *Nv_Download_ = (_Nv_Download*)vpPtr;

	while (TRUE)
	{
		//
		DWORD dwRet = WaitForSingleObject(Nv_Download_->Handle_DetectTask_Out_, 0);

		//�����ɹ�
		if (dwRet == WAIT_OBJECT_0)
		{
			//�����߳̾��
			BOOL bRet = CloseHandle(Nv_Download_->Handle_DetectTask_Out_);

			Nv_Download_->Handle_DetectTask_Out_ = NULL;
			DegMsg("detect_vtThreadOne_Task OUT....");
			//�ر��߳� ���ô���
			_endthreadex(Thread_download_Ok);
			return;
		}

		Nv_Download_->detect_vtThreadOne_Task();
		Sleep(10);
	}
}


//////////////////////////////////////////////////////////////////////////
//************************************************************************
//
// ����:	
// ����:	
// ����ֵ:	
// ����:	����
//
//
//************************************************************************
_Nv_Download_Task::_Nv_Download_Task()
{
	Init();
}




//************************************************************************
//
// ����:	
// ����:	
// ����ֵ:	
// ����:	�ӿ� ���� ��������
//
//
//************************************************************************
_Nv_Download_Task::_Nv_Download_Task(
							__in CONST CHAR *strDownloadUrl, 
							__in CONST CHAR *strSaveFilePath, 
							__in __int64 _n64X,
							__in __int64 _n64Size,
							__out int *nCallCnt,
							__in CONST CHAR *strCoolie,
							__in BOOL bFalg
)
{
	Init();

	nCallByteCnt_ = nCallCnt;

	strUrl_ = strDownloadUrl;
	strFilePath_ = strSaveFilePath;

	//ƫ����
	n64X_ = _n64X;
	
	//
	set_Coolie(strCoolie);

	if (bFalg == Run_Mode_2)
	{	
		n64DownloadSize_ = _n64Size;
	}
	
	Thread_Task();
}



//************************************************************************
//
// ����:	
// ����:	
// ����ֵ:	
// ����:	
//
//
//************************************************************************
_Nv_Download_Task::~_Nv_Download_Task()
{

}



//************************************************************************
//
// ����:	Init
// ����:	
// ����ֵ:	
// ����:	��ʼ����ı���
//
//
//************************************************************************
VOID _Nv_Download_Task::Init(VOID)
{
	memset(strFileName_, 0, sizeof(strFileName_));
	memset(strHostName_, 0, sizeof(strHostName_));

	n64DownloadSize_ = 0;

	Handle_Stop_Download_ = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	bStop_Download_ = FALSE;

	dwSleep_ = NULL;

	strUrl_ = "";
	strFilePath_ = "";

	n64FileSize_ = 0;

	n64X_ = n64Y_ = 0;

	n64_Download_Byte_Cnt_ = 0;

	dwTaskOk_ = 0;

	bCoolie_ = FALSE;

	strCoolie_ = "";

	Handle_Download_Ok = NULL;

	Nv_Download_Ptr_ = NULL;

	nCallByteCnt_ = NULL;
	n64CallByteCnt_ = NULL;

	Hinternet_OpenUrl_ = NULL;
}



//************************************************************************
//
// ����:	Thread_Task
// ����:	
// ����ֵ:	�ɹ�����TRUE ����FALSE
// ����:	��������
//
//
//************************************************************************
BOOL _Nv_Download_Task::Thread_Task(VOID)
{
	int nRetCode = 0;

	if (strCoolie_.length() != 0)
		nRetCode = GetHttpReturnData(strUrl_.c_str(), n64X_, n64Y_, strCoolie_.c_str());
	else
		nRetCode = GetHttpReturnData(strUrl_.c_str(), n64X_, n64Y_, NULL);

	if (nRetCode == Http_Return_206)
	{
		//��ʼ��������
		Handle_Download_Ok = (HANDLE)_beginthreadex(
			NULL, 
			0, 
			(unsigned int (__stdcall *)(void *))Thread_Download_Task, 
			this, 
			0, 
			NULL
			);

		return TRUE;
	}

	return FALSE;
}


//************************************************************************
//
// ����:	Detece_ThreadMode
// ����:	
// ����ֵ:	�ɹ�����TRUE ����FALSE
// ����:	�������֧��֧�ֶ��߳�
//
//
//************************************************************************
INT _Nv_Download_Task::Detece_ThreadMode(
	__in	CONST CHAR	*strUrl,
	__in	__int64 dwMinPos, 
	__in	__int64 dwMaxPos,
	__in	CONST CHAR	*strCoolie
)
{
	int nRetCode = 0;

	if (strCoolie_.length() != 0)
		nRetCode = GetHttpReturnData(strUrl, n64X_, n64Y_, strCoolie);
	else
		nRetCode = GetHttpReturnData(strUrl, n64X_, n64Y_, NULL);

	NvInternetCloseHandle(NULL);
	
	return nRetCode;
}



//************************************************************************
//
// ����:	SinglethreadDwondLoad
// ����:	��
// ����ֵ:	ȱʡ ����
// ����:	���߳����غ��� ���߳�ʹ��
//
//
//************************************************************************
__int64 _Nv_Download_Task::SinglethreadDwondLoad(						
									__in CONST CHAR *strDownloadUrl, 
									__in CONST CHAR *strSaveFilePath,
									__out __int64 *n64CallCnt,
									__in CONST CHAR *strCoolie
)
{
	
	n64CallByteCnt_ = n64CallCnt;
	strUrl_ = strDownloadUrl;
	strFilePath_ = strSaveFilePath;

	//
	set_Coolie(strCoolie);

	//�������һ��HTTP ����
	LARGE_INTEGER   t1;
	QueryPerformanceCounter(&t1);
	char strTimeName[64] = {0};
	sprintf(strTimeName, ("NV-%d"), t1.QuadPart);

	//��ȡ�ļ���С
	__int64 n64FileSize = get_UrlFileSizeAndFileName(strDownloadUrl, NULL, strCoolie);

	//����һ������
	NvInternetOpen(strTimeName, INTERNET_OPEN_TYPE_PRECONFIG);
	NvInternetOpenUrl(strDownloadUrl, INTERNET_FLAG_RELOAD);

	//��������
	n64X_ = 0;
	//��ʼ��������
	Handle_Download_Ok = (HANDLE)_beginthreadex(
		NULL, 
		0, 
		(unsigned int (__stdcall *)(void *))Thread_Download_Task, 
		this, 
		0, 
		NULL
		);

	return n64FileSize;
}


//************************************************************************
//
// ����:	NvInternetOpen
// ����:	__in char *strHttpName ����HTTP�������� �������� __in int nFalg �������
// ����ֵ:	�ɹ�����TRUE ����FALSE
// ����:	����ϵͳAPI InternetOpenA
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvInternetOpen(__in CONST CHAR *strHttpName, __in INT nFalg)
{
	Hinternet_Main_ = InternetOpenA(strHttpName, nFalg, NULL, NULL, 0);

	if (Hinternet_Main_ == NULL)
	{
		dwError_ = ::GetLastError();
		return FALSE;
	}

	return TRUE;
}



//************************************************************************
//
// ����:	NvInternetOpenUrl
// ����:	__in char *strUrl Ҫ�򿪵�url  int nFalg ����
// ����ֵ:	�ɹ�����TRUE ����FALSE
// ����:	����ϵͳAPI InternetOpenA
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvInternetOpenUrl(__in CONST CHAR *strUrl, __in INT nFalg)
{
	Hinternet_OpenUrl_ = InternetOpenUrl(Hinternet_Main_, strUrl, NULL, 0, nFalg, 0);

	if (Hinternet_OpenUrl_ == NULL)
	{
		return FALSE;
	}

	return TRUE;
}



//************************************************************************
//
// ����:	NvInternetConnect
// ����:	__in char *strHostName ����hostname �����ִ�NvAnalyzeURL��������
// ����ֵ:  �ɹ�����TRUE ����FALSE
// ����:	����ϵͳAPI InternetConnectA
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvInternetConnect(__in CHAR *strHostName)
{
	Hinternet_Connect_ = InternetConnectA(Hinternet_Main_, strHostName, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	
	if (Hinternet_Connect_ == NULL)
	{
		dwError_ = ::GetLastError();
		return FALSE;
	}

	return TRUE;
}

//************************************************************************
//
// ����:	NvAnalyzeURL
// ����:    __in char *strUrl �������ص�ַURL
// ����ֵ:	�ɹ�����TRUE ����FALSE
// ����:	����URL
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvAnalyzeURL(__in CONST CHAR *strUrl)
{
	URL_COMPONENTSA stURLComponents;
	ZeroMemory(&stURLComponents, sizeof(stURLComponents));

	stURLComponents.dwStructSize = sizeof(stURLComponents);
	stURLComponents.dwExtraInfoLength	= 1;
	stURLComponents.dwHostNameLength	= 1;
	stURLComponents.dwPasswordLength	= 1;
	stURLComponents.dwSchemeLength		= 1;
	stURLComponents.dwUrlPathLength		= 1;
	stURLComponents.dwUserNameLength	= 1;

	if (!InternetCrackUrlA(strUrl, 0, 0, &stURLComponents) || 
		stURLComponents.nScheme != INTERNET_SCHEME_HTTP || stURLComponents.dwUrlPathLength == 1)
	{
		dwError_ = ::GetLastError();
		return FALSE;
	}

	// ����ļ����ڷ������ķ�������
	ZeroMemory(strHostName_, sizeof(strHostName_));
	ZeroMemory(strFileName_, sizeof(strFileName_));

	strncpy(strHostName_, 
		stURLComponents.lpszHostName, 
		min(sizeof(strHostName_) / sizeof(char) - 1, 
		stURLComponents.dwHostNameLength)
		);
	strcpy(strFileName_, stURLComponents.lpszUrlPath);
	return TRUE;
}



//************************************************************************
//
// ����:	NvHttpOpenRequest
// ����:	__in const char *strAcceptTypes HTTP����Accept�ֶ� __in char *strFileName ��NvAnalyzeURL�������� __in DWORD dwFalg �Ƿ�ʹ��coolie
//			__in const char *strHttpType ȱʡ��
// ����ֵ:  �ɹ�����TRUE ����FALSE
// ����:    ����ϵͳAPI HttpOpenRequestA
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvHttpOpenRequest(__in CONST CHAR *strAcceptTypes, __in CHAR *strFileName, __in CONST CHAR *strHttpType, __in DWORD dwFalg)
{
	if (dwFalg != INTERNET_FLAG_NO_COOKIES)
	{
      Hinternet_Request_ = HttpOpenRequestA(Hinternet_Connect_, 
			("GET"), 
			strFileName, 
			HTTP_VERSIONA, 
			NULL,
			&strAcceptTypes,
			INTERNET_FLAG_RELOAD | INTERNET_FLAG_KEEP_CONNECTION,
			0
		  );
	}
	else
	{
		Hinternet_Request_ = HttpOpenRequestA(Hinternet_Connect_, 
			("GET"), 
			strFileName, 
			HTTP_VERSIONA, 
			NULL,
			&strAcceptTypes,
			INTERNET_FLAG_RELOAD | INTERNET_FLAG_KEEP_CONNECTION,
			INTERNET_FLAG_NO_COOKIES
			);
	}

	if (Hinternet_Request_ == NULL)
	{
		dwError_ = ::GetLastError();
		return FALSE;
	}
	
	return TRUE;
}



//************************************************************************
//
// ����:	NvHttpSendRequest
// ����:	HINTERNET hRequest ��NvHttpOpenRequest ��������������ľ��
// ����ֵ:  �ɹ�����TRUE ����FALSE
// ����:    ����ϵͳAPI HttpSendRequestA ���ͱ���
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvHttpSendRequest(VOID)
{
	BOOL bRet = ::HttpSendRequestA(Hinternet_Request_, NULL, 0, 0, 0);

	if (bRet == FALSE)
	{
		dwError_ = ::GetLastError();
		return bRet;
	}

	return bRet;
}



//************************************************************************
//
// ����:	NvHttpAddRequestHeaders
// ����:	__in HINTERNET hRequest ��NvHttpOpenRequest ��������������ľ�� 
//			__in DWORD dwMinPos, __in DWORD dwMaxPos ���ص�  __in int nFalg ����
// ����ֵ:	�ɹ�����TRUE ����FALSE
// ����:	����һ���ϵ㴫�͵����ص� x - y
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvHttpAddRequestHeaders(__in HINTERNET hRequest, __in __int64 _n64MinPos, __in __int64 _n64MaxPos, __in BOOL bFalg)
{
	char strPos[128] = {0};
	
	if (n64DownloadSize_ == 0)
	{
		sprintf(strPos, ("Range:bytes=%lld-\r\n"), _n64MinPos);
	}
	else
	{	
		(_n64MaxPos == 0) && (_n64MaxPos=_n64MinPos);
		sprintf(strPos, ("Range:bytes=%lld-%lld\r\n"), _n64MinPos, _n64MaxPos + n64DownloadSize_);
	}

	BOOL bRet = HttpAddRequestHeadersA(hRequest, strPos, -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);

	if (bRet == FALSE)
	{
		dwError_ = ::GetLastError();
		return bRet;
	}

	return bRet;
}



//************************************************************************
//
// ����:	NvHttpQueryInfo 
// ����:	__in HINTERNET hRequest, ��NvHttpOpenRequest ��������������ľ�� __in int nFalg ״̬��
// ����ֵ:	����״̬����
// ����:	��ѯһ�����ص�HTTP�����е�״̬����
//
//
//************************************************************************
__int64 _Nv_Download_Task::NvHttpQueryInfo(__in HINTERNET hRequest, __in int nFalg)
{
	char strBuf[1024] = {0};
	DWORD dwLen = sizeof(strBuf);
	if (FALSE == ::HttpQueryInfoA(hRequest, nFalg, strBuf, &dwLen , 0))
	{
		dwError_ = ::GetLastError();
		return 0;
	}

	__int64 int64Ret = _atoi64(strBuf);

	return int64Ret;
}



//************************************************************************
//
// ����:	NvHttpQueryInfo 
// ����:	__in HINTERNET hRequest, ��NvHttpOpenRequest ��������������ľ�� __in int nFalg ״̬�� OUT char *strFileName �����ļ���
// ����ֵ:	����״̬����
// ����:	��ѯһ�����ص�HTTP�����е�״̬����
//
//
//************************************************************************
void _Nv_Download_Task::NvHttpQueryInfo(__in HINTERNET hRequest, __in INT nFalg, OUT CHAR *strFileName)
{
	char strBuf[1024] = {0};
	DWORD dwLen = sizeof(strBuf);
	if (FALSE == ::HttpQueryInfoA(hRequest, nFalg, strBuf, &dwLen , 0))
	{
		strFileName = NULL;
		dwError_ = ::GetLastError();
		return;
	}

	strcpy(strFileName, strBuf);

	return;
}



//************************************************************************
//
// ����:	NvInternetCloseHandle
// ����:	__in HINTERNET hDelete �Ƿ�Ͽ�����
// ����ֵ:	�ɹ�����TRUE ����FALSE
// ����:	ɾ�����о��
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvInternetCloseHandle(__in HINTERNET hDelete)
{
	if (hDelete == NULL)
	{
		Hinternet_Main_ != NULL && (InternetCloseHandle(Hinternet_Main_), Hinternet_Main_ = NULL);
		Hinternet_Connect_ != NULL && (InternetCloseHandle(Hinternet_Connect_), Hinternet_Connect_ = NULL);
		Hinternet_Request_ != NULL && (InternetCloseHandle(Hinternet_Request_), Hinternet_Request_ = NULL);
	}
	else
	{
		InternetCloseHandle(hDelete);
	}

	return TRUE;
}



//************************************************************************
//
// ����:	GetHttpReturnData
// ����:	__in char *strUrl ���ص�URL __in char *strFileSavePath �ļ�����·��
//			__in DWORD dwMinPos ���ص� __in DWORD dwMaxPos ���ص� __in BOOL bCoolie �Ƿ���coolie __in char *strCoolie coolie����
// ����ֵ:	����״̬��
// ����:	����һ���������Ƿ�֧�� �ϵ�����
//
//
//************************************************************************
DWORD _Nv_Download_Task::GetHttpReturnData(
								__in	CONST CHAR	*strUrl,
								__in	__int64 dwMinPos, 
								__in	__int64 dwMaxPos,
								__in	CONST CHAR	*strCoolie
)
{
	//�������һ��HTTP ����
	LARGE_INTEGER   t1;
	QueryPerformanceCounter(&t1);
	char strTimeName[64] = {0};
	sprintf(strTimeName, ("NV-%d"), t1.QuadPart);
	
	//����
	NvInternetOpen(strTimeName, INTERNET_OPEN_TYPE_PRECONFIG);
	//����URL
	NvAnalyzeURL(strUrl);
	//����
	NvInternetConnect(strHostName_);

		//���챨��
	if (strCoolie == FALSE)
	{
		NvHttpOpenRequest(NULL, strFileName_, "HTTP/1.1", 0);
		//���һ����������
		HttpAddRequestHeadersA(Hinternet_Request_, "Accept: */*\r\n", -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	}
	else
	{
		NvHttpOpenRequest(NULL, strFileName_, "HTTP/1.1", INTERNET_FLAG_NO_COOKIES);
		//���һ����������
		HttpAddRequestHeadersA(Hinternet_Request_, "Accept: */*\r\n", -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
		//���һ����������
		HttpAddRequestHeadersA(Hinternet_Request_, strCoolie, -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	}

	//���öϵ�����
	NvHttpAddRequestHeaders(Hinternet_Request_, dwMinPos, dwMaxPos, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	
	//���ͱ���
	NvHttpSendRequest();
	
	//����״̬
	__int64 int64Recv = NvHttpQueryInfo(Hinternet_Request_, HTTP_QUERY_STATUS_CODE);

	if (int64Recv == Http_Return_206)
	{
		//�ϵ�����
		return Http_Return_206;
	}else if (int64Recv == Http_Return_200)
	{
		//��֧�ֶϵ�����
		return Http_Return_200;
	}else
	{
		//���� ����
		dwError_ = ::GetLastError();
		NvInternetCloseHandle(NULL);
		return 0xFFFF;
	}
}


//************************************************************************
//
// ����:	get_UrlFileSizeAndFileName
// ����:	__in char *strUrl ���ص�ַ URL __in BOOL bCoolie �Ƿ���coolie __in char *strCoolie coolie����
// ����ֵ:	�����ļ���С ���󷵻�0xFFFF
// ����:	��ȡԶ���ļ���С
//
//
//************************************************************************
__int64 _Nv_Download_Task::get_UrlFileSizeAndFileName(__in CONST CHAR *strUrl, OUT CHAR *strFileName, __in CONST CHAR *strCoolie)
{
	
	//�������һ��HTTP ����
	LARGE_INTEGER   t1;
	QueryPerformanceCounter(&t1);
	char strTimeName[64] = {0};
	sprintf(strTimeName, ("NV-%d"), t1.QuadPart);
	
	//����
	NvInternetOpen(strTimeName, INTERNET_OPEN_TYPE_PRECONFIG);
	//����URL
	NvAnalyzeURL(strUrl);
	//����
	NvInternetConnect(strHostName_);

		//���챨��
	if (strCoolie == NULL)
	{
		NvHttpOpenRequest(NULL, strFileName_, "HTTP/1.1", 0);
		//���һ����������
		HttpAddRequestHeadersA(Hinternet_Request_, "Accept: */*\r\n", -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	}
	else
	{
		NvHttpOpenRequest(NULL, strFileName_, "HTTP/1.1", INTERNET_FLAG_NO_COOKIES);
		//���һ����������
		HttpAddRequestHeadersA(Hinternet_Request_, "Accept: */*\r\n", -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
		//���һ����������
		HttpAddRequestHeadersA(Hinternet_Request_, strCoolie, -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	}

	//���ͱ���
	NvHttpSendRequest();

	//��ʱ
	Sleep(500);
	//��ȡ״̬�� HTTP_QUERY_FLAG_NUMBER| HTTP_QUERY_STATUS_CODE);
	__int64 int64Recv = NvHttpQueryInfo(Hinternet_Request_, HTTP_QUERY_STATUS_CODE); 

	if (int64Recv == 403 || int64Recv == 404)
	{
		NvInternetCloseHandle(NULL);
		return 0;
	}

	//��ȡ�ļ���С
	__int64 int64FileSize = NvHttpQueryInfo(Hinternet_Request_, HTTP_QUERY_CONTENT_LENGTH);

	if (strFileName != NULL && int64Recv == 302)
	{
		//��ȡ�ļ���
		NvHttpQueryInfo(Hinternet_Request_, HTTP_QUERY_LOCATION, strFileName);
	}
	else if (strFileName != NULL)
	{
		//��ȡ�ļ���
		NvHttpQueryInfo(Hinternet_Request_, HTTP_QUERY_CONTENT_DISPOSITION, strFileName);
	}

	NvInternetCloseHandle(NULL);
	
	//�ļ���СΪ0 ���� ���ô������
	if (int64FileSize <= 0)
	{
		dwError_ = ::GetLastError();
	}

	return int64FileSize;
}




//************************************************************************
//
// ����:	NvDownload_Task
// ����:	__in CONST CHAR *strSaveFilePath �����ļ�·��
// ����ֵ:	���������û����� ����TRUE ���򷵻�FALSE
// ����:	��ʼ���������ֽ�
//
//
//************************************************************************
BOOL _Nv_Download_Task::NvDownload_Task(__in CONST CHAR *strSaveFilePath)
{
	//������ָ��
	//m_nTaskOk = -1;

	//���ļ���ʼд������
	HANDLE hFile = CreateFileA(strSaveFilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, NULL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		dwError_ = ::GetLastError();
		return FALSE;
	}

	// ���ݶϵ�λ�ô����ļ���С
	LARGE_INTEGER largeFileSize;
	largeFileSize.QuadPart = n64X_;
	SetFilePointer(hFile, largeFileSize.LowPart, &largeFileSize.HighPart, FILE_BEGIN);

	//��ʼ����

	//����
	BOOL	bRecv	= FALSE;
	BOOL	bWrite	= FALSE;
	DWORD	dwError = 0;
	//ʵ���յ�
	DWORD	dwRecvSize;
	//д������
	DWORD	dwWriteSize = 1;
	//���Ӵ���
	DWORD	dwLinkCnt = 0;
	
	//����buf
	char	*strRecvBuf = new char[1024*2];

	if (NULL == strRecvBuf)
	{
		return FALSE;
	}

	while (dwWriteSize != 0)
	{
		if (Hinternet_OpenUrl_ != NULL)
			bRecv = InternetReadFile(Hinternet_OpenUrl_, strRecvBuf, 2047, &dwRecvSize);
		else
			bRecv = InternetReadFile(Hinternet_Request_, strRecvBuf, 2047, &dwRecvSize);
		dwError = ::GetLastError();
		
		//������
		if ((dwError == 12002) || (bRecv == FALSE))
		{
			//����һ������ ����������̹߳���������ִ�и��߳�
			dwLinkCnt++;

			if (dwLinkCnt == 20) { 
				CHAR strData[1024] = {0};
				sprintf(strData, "�߳���Ϣ1: ������:%u ���: %lld  ������: %lld, �Ѿ�����:%lld..", dwError, n64X_,
					n64DownloadSize_, n64_Download_Byte_Cnt_
					);
				DegMsg(strData);
				NvInternetCloseHandle(NULL); CloseHandle(hFile); 
				delete []strRecvBuf;  
				return FALSE; 
			}
			else continue;
		}

		bWrite = WriteFile(hFile, strRecvBuf, dwRecvSize, &dwWriteSize, NULL);
		if ((bWrite == FALSE) || (dwWriteSize!=dwRecvSize))
		{
bkw:
			dwError = ::GetLastError();
			//����һ������ ����������̹߳���������ִ�и��߳�
			CHAR strData[1024] = {0};
			sprintf(strData, "�߳���Ϣ2: ������:%u ���: %lld  ������: %lld, �Ѿ�����:%lld..", dwError, n64X_,
				n64DownloadSize_, n64_Download_Byte_Cnt_
				);
			DegMsg(strData);
			NvInternetCloseHandle(NULL); CloseHandle(hFile); 
			delete []strRecvBuf;  
			return FALSE; 
		}else if (((n64_Download_Byte_Cnt_ - 1) != n64DownloadSize_) && (dwWriteSize == 0))
		{
			goto bkw;
		}

		//�ۼƵ�ǰ�����߳������˶����ֽ�
		n64_Download_Byte_Cnt_ += dwWriteSize;
		if (nCallByteCnt_ != NULL)
			*nCallByteCnt_ += dwWriteSize;
		if (n64CallByteCnt_ != NULL)
			*n64CallByteCnt_ += dwWriteSize;
		
		//�����˳�����
		if (bStop_Download_ == TRUE)
		{
			DegMsg("�˳�����...");
			Nv_Download_Ptr_->get_ThreadTaskData(n64X_, n64DownloadSize_, n64_Download_Byte_Cnt_);
			//�˳�
			//������Դ
			delete []strRecvBuf;
			CloseHandle(hFile);
			NvInternetCloseHandle(NULL);
			return TRUE;
		}
	}
	

	if ((n64_Download_Byte_Cnt_ - 1) != n64DownloadSize_)
	{
		CHAR strData[1024] = {0};
		sprintf(strData, "�߳���Ϣ3: ������:%u ���: %lld  ������: %lld, �Ѿ�����:%lld..", dwError, n64X_,
			n64DownloadSize_, n64_Download_Byte_Cnt_
			);
		DegMsg(strData);

		delete []strRecvBuf;
		CloseHandle(hFile);
		NvInternetCloseHandle(NULL);

		return TRUE;
	}
	
	delete []strRecvBuf;
	CloseHandle(hFile);
	NvInternetCloseHandle(NULL);

	return TRUE;
}




//************************************************************************
//
// ����:	stop_Task
// ����:	
// ����ֵ:	
// ����:	�رո���������
//
//
//************************************************************************
BOOL _Nv_Download_Task::stop_Task(VOID)
{
	//ֹͣ����
	stop_Download();
	//�رո���������
	SetEvent(Handle_Stop_Download_);
	//�ȴ������ر�
	DWORD dwOutCode;
	while (TRUE)
	{
		::GetExitCodeThread(Handle_Download_Ok, &dwOutCode);
		if ((dwOutCode == Thread_download_Out) || (Thread_download_Ok == dwOutCode))
		{
			return TRUE;
		}
		Sleep(5);
	}

	return FALSE;
}


//************************************************************************
//
// ����:	stop_Download
// ����:	
// ����ֵ:	
// ����:	ֹͣ����
//
//
//************************************************************************
VOID _Nv_Download_Task::stop_Download(VOID)
{
	bStop_Download_ = TRUE;
}



//************************************************************************
//
// ����:	get_Download_Byte_Cnt
// ����:	
// ����ֵ:	
// ����:	
//
//
//************************************************************************
__int64 _Nv_Download_Task::get_Download_Byte_Cnt(VOID)
{
	return n64_Download_Byte_Cnt_;
}


//************************************************************************
//
// ����:	set_Coolie
// ����:	
// ����ֵ:	
// ����:	����Coolie
//
//
//************************************************************************
VOID _Nv_Download_Task::set_Coolie(__in CONST CHAR *strCoolie)
{
	if (strCoolie != NULL)
	{
		strCoolie_ = strCoolie;
		bCoolie_ = TRUE;
	}
}



//************************************************************************
//
// ����:	get_DownloadThisPtr
// ����:	
// ����ֵ:	
// ����:	��ȡ���ع�������ָ��
//
//
//************************************************************************
BOOL _Nv_Download_Task::get_DownloadThisPtr(__in _Nv_Download *nv_this)
{
	if (nv_this != NULL)
	{
		Nv_Download_Ptr_ = nv_this;
		return TRUE;
	}

	return FALSE;
}





//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// _Nv_Download ��ʵ��


//************************************************************************
//
// ����:	
// ����:	
// ����ֵ:	
// ����:	ʹ���๹�캯��ֱ������ ���޷������߳����� �߳�Ĭ�Ϲ����� �������Ĭ������
//
//
//************************************************************************
_Nv_Download::_Nv_Download( 
			__in CONST CHAR *strDownloadUrl, 
			__in CONST CHAR *strSaveFilePath,
			__in CONST CHAR *strCoolie,
			__in BOOL bModeFalg /* = Run_Mode_2 */ 
)
{
	Init();

	if (strCoolie != NULL)
	{
		strCoolie_ = strCoolie;
		bCoolie_ = TRUE;
	}

}




//************************************************************************
//
// ����:	
// ����:	
// ����ֵ:	
// ����:	����
//
//
//************************************************************************
_Nv_Download::_Nv_Download()
{
	Init();
}



//************************************************************************
//
// ����:	
// ����:	
// ����ֵ:	
// ����:	
//
//
//************************************************************************
_Nv_Download::~_Nv_Download()
{

}


//************************************************************************
//
// ����:	Init
// ����:	
// ����ֵ:	
// ����:	��ʼ�������
//
//
//************************************************************************
VOID _Nv_Download::Init()
{
	InitializeCriticalSection(&chitical_section_);
	InitializeCriticalSection(&chitical_section_Add);

	bCoolie_ = FALSE;
	strCoolie_ = "";

	vtThread_Task_.clear();
	vtTagTaskData.clear();
	vtDownloadNo_.clear();
	//vt64DownloadCount_.clear();
	
	//�߳�����
	dwThreadCnt_ = 10;
	//�̹߳�����
	n64ThreadDownloadCnt_ = 204800;
	n64ThreadTaskSion_ = 0 - n64ThreadDownloadCnt_;

	n64FileSize_ = 0;

	strUrl_ = "";
	strFileSavePath_ = "";

	n64DownloadCount_ = 0;

	Handle_DetectTask_Out_ = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	Handle_ThreadTask_Out_ = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	n64JiDonwloadCnt_ = 0;

	n64TimeDownloadCnt_ = 0;

	dwIsSpeed_ = 0;

	bTaskStop_ = FALSE;

	bDownloadTaskCmd_ = FALSE;
	
	nDataCount_ = 0;

	Nv_One_Download_Task_ = NULL;

	n64ThreadOneCnt_ = 0;

	bThreadMode_ = FALSE;

	nDownloadCount_ = NULL;
}



//************************************************************************
//
// ����:	Download
// ����:	
// ����ֵ:	
// ����:	�ⲿ�ӿ�  ����
//
//
//************************************************************************
BOOL _Nv_Download::Download(__in CONST CHAR *strUrl, __in CONST CHAR *strFileSavePath, __in CONST CHAR *strCoolie, __in BOOL bModeFalg)
{
	if (strCoolie != NULL)
	{
		strCoolie_ = strCoolie;
		bCoolie_ = TRUE;
	}


	//��ȡ�ļ���С
	__int64 n64FileSize = get_TaskFileSize(strUrl);

	//��ȡurl
	strUrl_ = strUrl;
	//��ȡ�����ļ�·��
	strFileSavePath_ = strFileSavePath;

	//���Զϵ������ļ�
	read_DwonloadFile();

	_Nv_Download_Task *Nv_Task_ = new _Nv_Download_Task;
	if (Http_Return_206 == Nv_Task_->Detece_ThreadMode(strUrl, 0, 0,  strCoolie))
	{
		delete Nv_Task_;
		
		if (n64FileSize < n64ThreadDownloadCnt_ * 5)
			dwDownloadVectorSize_ = 100;
		else
			dwDownloadVectorSize_ = (n64FileSize / n64ThreadDownloadCnt_) * 2;
		nDownloadCount_ = new int[dwDownloadVectorSize_];

		if (nDownloadCount_ == NULL)
		{
			DegMsg("���ش���: �ֽڼ�¼������䲻�ɹ�!");
			return FALSE;
		}
		else
		{
			for (int i=0; i<dwDownloadVectorSize_; ++i)
			{
				nDownloadCount_[i] = 0;
			}
		}

		//��ʼ��������
		Handle_ThreadTask_ = (HANDLE)_beginthreadex(
			NULL, 
			0, 
			(unsigned int (__stdcall *)(void *))Thread_Download, 
			this, 
			0, 
			NULL
			);

		Handle_DetectTask_ = (HANDLE)_beginthreadex(
			NULL, 
			0, 
			(unsigned int (__stdcall *)(void *))Thread_DetectTask, 
			this, 
			0, 
			NULL
			);
	}
	else
	{
		bThreadMode_ = TRUE;
		
		////
		//��ʼ��������
		Handle_ThreadTask_ = (HANDLE)_beginthreadex(
			NULL, 
			0, 
			(unsigned int (__stdcall *)(void *))Thread_OneDownload, 
			this, 
			0, 
			NULL
			);

		Handle_DetectTask_ = (HANDLE)_beginthreadex(
			NULL, 
			0, 
			(unsigned int (__stdcall *)(void *))Thread_DetectOneTask, 
			this, 
			0, 
			NULL
			);

	}

	return TRUE;
}


//************************************************************************
//
// ����:	get_TaskFileSize
// ����:	__in CONST CHAR *strDownloadUrl  ����URL
// ����ֵ:	�����ļ���С
// ����:	��ȡҪ���ص��ļ���С
//
//
//************************************************************************
__int64 _Nv_Download::get_TaskFileSize(__in CONST CHAR *strDownloadUrl)
{
	_Nv_Download_Task *Nv_FileSize_ = new _Nv_Download_Task;
	__int64 n64FileSize = Nv_FileSize_->get_UrlFileSizeAndFileName(strDownloadUrl, NULL, strCoolie_.c_str());
	n64FileSize_ = n64FileSize;

	delete Nv_FileSize_;

	return n64FileSize;
}



//************************************************************************
//
// ����:	call_AssignTasks
// ����:	
// ����ֵ:	
// ����:	������������
//
//
//************************************************************************
BOOL _Nv_Download::call_AssignTasks(__in __int64 &n641, __in __int64 &n642, __in __int64 &n643)
{
	if ((n641 + n642) == n643)
	{
		return FALSE;
	}

	if ((n641 + n642) < (n643 - n642))
	{
		n641 += n642;
	}
	else if (((n641 + n642) < n643) && ((n641+n642+n642) > n643))
	{
		n641 += n642;
		n642 = n643 - n641;
	}

	return TRUE;
}



//************************************************************************
//
// ����:	decete_TaskFailure
// ����:	
// ����ֵ:	
// ����:	�޲������̺߳���
//
//
//************************************************************************
BOOL _Nv_Download::decete_TaskFailure(
						__in CONST CHAR *strDownloadUrl, 
						__in CONST CHAR *strSaveFilePath,
						__in CONST CHAR *strCoolie
						)
{
	DWORD dwTask = vtDownloadNo_.size();
	if (dwTask != 0)
	{
		_Nv_Tag_Download_Data Nv_Tag_Data_;
		Nv_Tag_Data_.n64X_ = vtDownloadNo_[0].n64X_;
		Nv_Tag_Data_.n64TaskCnt_ = vtDownloadNo_[0].n64TaskCnt_;
		Nv_Tag_Data_.n64DownloadCnt_ = vtDownloadNo_[0].n64DownloadCnt_;
		vtDownloadNo_.erase(vtDownloadNo_.begin() + 0);
		
		//EnterCriticalSection(&chitical_section_Add);
		nDownloadCount_[nDataCount_] = 0;

		//����һ�������߳�����;
		_Nv_Download_Task *Nv_Task_ = new _Nv_Download_Task(
			strDownloadUrl, strSaveFilePath, Nv_Tag_Data_.n64X_ + Nv_Tag_Data_.n64DownloadCnt_, 
			Nv_Tag_Data_.n64TaskCnt_ - Nv_Tag_Data_.n64DownloadCnt_ - 1, &nDownloadCount_[nDataCount_], strCoolie
			);

		nDataCount_++;
		//LeaveCriticalSection(&chitical_section_Add);
		if (Nv_Task_ != NULL)
		{
			CHAR strData[1024] = {0};
			sprintf(strData, "�̴߳����޸�: ԭʼ���ص�:%lld, ������:%lld. �޸����ص�:%lld, ������:%lld, ԭʼ������:%lld..", 
				Nv_Tag_Data_.n64X_, Nv_Tag_Data_.n64DownloadCnt_, 
				Nv_Tag_Data_.n64X_ + Nv_Tag_Data_.n64DownloadCnt_,
				Nv_Tag_Data_.n64TaskCnt_ - Nv_Tag_Data_.n64DownloadCnt_ - 1,
				Nv_Tag_Data_.n64TaskCnt_
				);
			DegMsg(strData);

			Nv_Task_->get_DownloadThisPtr(this);
			vtThread_Task_.push_back(Nv_Task_);
		}
		

		return TRUE;
	}

	return FALSE;
}



//************************************************************************
//
// ����:	thread_Task
// ����:	
// ����ֵ:	
// ����:	���ĺ���
//
//
//************************************************************************
BOOL _Nv_Download::thread_Task( 
			__in CONST CHAR *strDownloadUrl, 
			__in CONST CHAR *strSaveFilePath,
			__in CONST CHAR *strCoolie,
			__in BOOL bModeFalg /* = Run_Mode_2 */ 
)
{
	__int64 n64CopyCount = n64ThreadDownloadCnt_;

	while(TRUE)
	{
		//�����̴߳���������
		if (dwThreadCnt_ > vtThread_Task_.size())
		{
			//�˳�
			DWORD dwRet = WaitForSingleObject(Handle_ThreadTask_Out_, 0);

			//�����ɹ�
			if (dwRet == WAIT_OBJECT_0)
			{
				DegMsg("thread_Task�̰߳�ȫ�ر�");
				//ֹͣ������
				stop_DetectTask();
				return TRUE;
			}
			
			//�Ƿ�������ʧ�ܵ��߳�
			if (decete_TaskFailure(strDownloadUrl, strSaveFilePath, strCoolie) == TRUE)
			{
				Sleep(10);
				continue;
			}
			//����������
			if ((vtTagTaskData.size() == 0) && (n64CopyCount == n64ThreadDownloadCnt_))
			{
				if (FALSE == call_AssignTasks(n64ThreadTaskSion_, n64ThreadDownloadCnt_, n64FileSize_))
				{
					NULL;
				}
			}
			else if (vtTagTaskData.size() == 0)
			{
				//�������
				if (get_DownloadCount() == n64FileSize_)
					break;
				else
					Sleep(10);
					continue;
			}
			//�ϵ���������
			__int64 n64GetTaskCnt = 0;
			__int64 n64RetCode = set_ThreadTaskData(n64ThreadTaskSion_, n64ThreadDownloadCnt_, n64GetTaskCnt);
			
			//EnterCriticalSection(&chitical_section_Add);
			nDownloadCount_[nDataCount_] = 0;
			//����һ�������߳�����;
			_Nv_Download_Task *Nv_Task_ = new _Nv_Download_Task(
				strDownloadUrl, strSaveFilePath, n64ThreadTaskSion_, 
					n64ThreadDownloadCnt_ - 1, &nDownloadCount_[nDataCount_], strCoolie
				);
			nDataCount_++;
			//LeaveCriticalSection(&chitical_section_Add);
			if (Nv_Task_ == NULL)
			{
				DegMsg("���صĴ���,Nv_Task_�ڴ����ʧ��..");
			}

			if ((n64RetCode != T_X) && (n64RetCode != T_Z))
			{
				//���
				n64ThreadTaskSion_ = (n64RetCode - n64CopyCount) + n64ThreadDownloadCnt_;
				n64ThreadDownloadCnt_ = n64CopyCount;
			}

			//
			if (Nv_Task_ != NULL)
			{
				/*CHAR strData[1024] = {0};
				sprintf(strData, "Thread: from %lld to %lld, count:%lld..", n64ThreadTaskSion_,
					n64ThreadTaskSion_ + (n64ThreadDownloadCnt_ - 1), n64ThreadDownloadCnt_ - 1
					);
				DegMsg(strData);*/
				//����this
				Nv_Task_->get_DownloadThisPtr(this);
				//׷�ٸ�����
				vtThread_Task_.push_back(Nv_Task_);
			}
		}

		Sleep(100);
	}
	
	//ֹͣ���
	stop_DetectTask();

	bDownloadTaskCmd_ = TRUE;
	
	EnterCriticalSection(&chitical_section_);
	delete []nDownloadCount_;
	nDownloadCount_ = NULL;
	LeaveCriticalSection(&chitical_section_);
	return TRUE;
}



//************************************************************************
//
// ����:	detect_vtThread_Task
// ����:	
// ����ֵ:	
// ����:	�̹߳�������麯�� ���ж�һ���߳��Ƿ��Ѿ�����Լ�������
//
//
//************************************************************************
VOID _Nv_Download::detect_vtThread_Task(VOID)
{
	DWORD dwSize = vtThread_Task_.size();
	
	for (int i=0; i<dwSize; ++i)
	{
		if (vtThread_Task_[i]->dwTaskOk_ == Thread_ON)
		{
			_Nv_Tag_Download_Data Nv_Data;
			Nv_Data.n64X_ = vtThread_Task_[i]->n64X_;
			Nv_Data.n64TaskCnt_ = vtThread_Task_[i]->n64DownloadSize_ + 1;
			Nv_Data.n64DownloadCnt_ = vtThread_Task_[i]->n64_Download_Byte_Cnt_;
			vtDownloadNo_.push_back(Nv_Data);
		}

		if ((vtThread_Task_[i]->dwTaskOk_ == Thread_ON) ||
			(vtThread_Task_[i]->dwTaskOk_ == Thread_OK))
		{
			//��ȡ�߳��˳�����
			//����˳�����
			while(TRUE)
			{
				DWORD dwOutCode = 0;
				::GetExitCodeThread(vtThread_Task_[i]->Handle_Download_Ok, &dwOutCode);
				if (dwOutCode == Thread_download_Ok)
				{
					CloseHandle(vtThread_Task_[i]->Handle_Download_Ok);
					//���߳��Ѿ���ȫ�˳�
					//EnterCriticalSection(&chitical_section_);
					delete vtThread_Task_[i];
					//LeaveCriticalSection(&chitical_section_);
					vtThread_Task_[i] = NULL;
					vtThread_Task_.erase(vtThread_Task_.begin() + i);
					dwSize = vtThread_Task_.size();
					return;
				}
				Sleep(100);
			}
		}
	}
}



//************************************************************************
//
// ����:	detect_vtThreadOne_Task
// ����:	
// ����ֵ:	
// ����:	�ػ����߳�
//
//
//************************************************************************
VOID _Nv_Download::detect_vtThreadOne_Task(VOID)
{
	if (Nv_One_Download_Task_ != NULL)
	{
		if ((Nv_One_Download_Task_->dwTaskOk_ == Thread_ON) ||
			(Nv_One_Download_Task_->dwTaskOk_ == Thread_OK))
		{
			//��ȡ�߳��˳�����
			//����˳�����
			while(TRUE)
			{
				DWORD dwOutCode = 0;
				::GetExitCodeThread(Nv_One_Download_Task_->Handle_Download_Ok, &dwOutCode);
				if (dwOutCode == Thread_download_Ok)
				{
					CloseHandle(Nv_One_Download_Task_->Handle_Download_Ok);
					//���߳��Ѿ���ȫ�˳�
					delete Nv_One_Download_Task_;
					Nv_One_Download_Task_ = NULL;
					return;
				}
				Sleep(100);
			}
		}
	}
}



BOOL _Nv_Download::thread_OneTask( 
							   __in CONST CHAR *strDownloadUrl, 
							   __in CONST CHAR *strSaveFilePath,
							   __in CONST CHAR *strCoolie,
							   __in BOOL bModeFalg /* = Run_Mode_2 */ 
							   )
{
	//����һ��
	while(TRUE)
	{
		//�˳�
		DWORD dwRet = WaitForSingleObject(Handle_ThreadTask_Out_, 0);

		//�����ɹ�
		if (dwRet == WAIT_OBJECT_0)
		{
			DegMsg("thread_Task�̰߳�ȫ�ر�");
			//ֹͣ������
			stop_DetectTask();
			return TRUE;
		}
		
		//���ָ����ѱ�����
		if (Nv_One_Download_Task_ == NULL)
		{
			//�ж��ļ��Ƿ��������
			//�������
			if (get_DownloadCount() == n64FileSize_)
			{
				break;
			}
			else
			{
				//�����������ظ�����
				//���߳�����
				Nv_One_Download_Task_ = new _Nv_Download_Task;
				
				n64ThreadOneCnt_ = 0;
				
				Nv_One_Download_Task_->get_DownloadThisPtr(this);

				Nv_One_Download_Task_->SinglethreadDwondLoad(
					strDownloadUrl, 
					strSaveFilePath, 
					&n64ThreadOneCnt_, 
					strCoolie
					);
			}
		}
	}

	//ֹͣ���
	stop_DetectTask();

	bDownloadTaskCmd_ = TRUE;

	EnterCriticalSection(&chitical_section_);
	delete []nDownloadCount_;
	nDownloadCount_ = NULL;
	LeaveCriticalSection(&chitical_section_);
	return TRUE;
}

//************************************************************************
//
// ����:	stop_DetectTask
// ����:	
// ����ֵ:	
// ����:	�ر��̹߳���������߳�
//
//
//************************************************************************
VOID _Nv_Download::stop_DetectTask(VOID)
{
	//�ر�
	SetEvent(Handle_DetectTask_Out_);
}




//************************************************************************
//
// ����:	stop_ThreadTask
// ����:	
// ����ֵ:	
// ����:	ֹͣ�߳����������
//
//
//************************************************************************
BOOL _Nv_Download::stop_ThreadTask(VOID)
{
	//�ر�
	SetEvent(Handle_ThreadTask_Out_);
	
	DWORD dwOutCode;
	while (TRUE)
	{
		::GetExitCodeThread(Handle_ThreadTask_, &dwOutCode);
		if (dwOutCode == Thread_Download_Fun)
		{
			return TRUE;
		}
		Sleep(5);
	}

	return FALSE;
}



//************************************************************************
//
// ����:	get_DownloadCount
// ����:	
// ����ֵ:	
// ����:	��ȡ��ǰ�Ѿ����ض����ֽ�
//
//
//************************************************************************
__int64 _Nv_Download::get_DownloadCount(VOID)
{
	
	if (nDownloadCount_ == NULL)
	{
		//n64ThreadOneCnt_
		if (bThreadMode_ == FALSE)
			return n64DownloadCount_;
		
		return n64ThreadOneCnt_;
	}
	EnterCriticalSection(&chitical_section_);
	__int64 n64Ret = n64JiDonwloadCnt_;

	DWORD dwSize = vtThread_Task_.size();

	for (int i=0; i<nDataCount_; ++i)
	{
		n64Ret += (__int64)nDownloadCount_[i];
	}
	n64DownloadCount_ = n64Ret;
	LeaveCriticalSection(&chitical_section_);
	return n64Ret;
}



//************************************************************************
//
// ����:	get_DownloadSpeed
// ����:	
// ����ֵ:	
// ����:	��ȡ��������
//
//
//************************************************************************
__int64 _Nv_Download::get_DownloadSpeed(VOID)
{
	dwIsSpeed_ = (DWORD)(get_DownloadCount() - n64TimeDownloadCnt_) / 1024;
	set_TimeCount();
	return dwIsSpeed_;
}




//************************************************************************
//
// ����:	set_TimeCount
// ����:	
// ����ֵ:	
// ����:	����ʱ���
//
//
//************************************************************************
VOID _Nv_Download::set_TimeCount(VOID)
{
	n64TimeDownloadCnt_ = get_DownloadCount();
}


//************************************************************************
//
// ����:	set_ThreadCount
// ����:	
// ����ֵ:	
// ����:	�����߳���
//
//
//************************************************************************
VOID _Nv_Download::set_ThreadCount(__in DWORD dwThreadCount)
{
	if (dwThreadCount > 12)
	{
		dwThreadCnt_ = 12;
	}
	else if(dwThreadCount == 0)
	{
		dwThreadCnt_ = 6;
	}
}



//************************************************************************
//
// ����:	set_HttpLinkCount
// ����:	
// ����ֵ:	
// ����:	����������
//
//
//************************************************************************
VOID _Nv_Download::set_HttpLinkCount(__in DWORD dwCount)
{
	HKEY hKey;
	::RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",0,KEY_WRITE,&hKey);
	::RegSetValueEx(hKey,"MaxConnectionsPer1_0Server",0,REG_DWORD,(CONST BYTE *)&dwCount, 4);
	::RegSetValueEx(hKey,"MaxConnectionsPerServer",0,REG_DWORD,(CONST BYTE *)&dwCount, 4);
	::RegCloseKey(hKey);
}



//************************************************************************
//
// ����:	set_DownloadTaskCnt
// ����:	
// ����ֵ:	
// ����:	����ÿ���̵߳�������
//
//
//************************************************************************
VOID _Nv_Download::set_DownloadTaskCnt(__in DWORD dwDownloadTaskCnt)
{
	if (dwDownloadTaskCnt > 1020000/3)
	{
		n64ThreadDownloadCnt_ = 204800;
	}
	else if(dwDownloadTaskCnt == 0)
	{
		n64ThreadDownloadCnt_ = 204800;
	}
}


//************************************************************************
//
// ����:	get_SurplusDownloadTime
// ����:	��
// ����ֵ:	���� ʣ��ʱ��
// ����:	����ʣ��ʱ��
//
//
//************************************************************************
CHAR *_Nv_Download::get_SurplusDownloadTime(VOID)
{
	
	//��ǰ��������
	__int64	dwSize = dwIsSpeed_;

	if (dwSize == 0)
	{
		return "�޷�����..";
	}

	//���ж���ô��������
	__int64	dwOutSize = n64FileSize_ - get_DownloadCount();
	//��Լ��ʣ�¶�����
	double  bOutTime = (double)(dwOutSize / 1024 / (double)(dwSize));
	BOOL	bFeng = FALSE;

	DWORD	dwFeng = (DWORD)(bOutTime / 60.0);
	DWORD	dwShi  = 0;
	
	if (dwFeng >= 60)
	{
		bFeng	= TRUE;
		dwShi	= dwFeng / 60;
		dwFeng	= dwFeng % 60;
	}

	DWORD	dwMiao = (DWORD)bOutTime % 60;

	static char strOut[64] = {0};
	if (bFeng == TRUE)
		sprintf(strOut, "%dСʱ%d����%d��", dwShi, dwFeng, dwMiao);
	else
		sprintf(strOut, "%d����%d��", dwFeng, dwMiao);

	return strOut;
}


//************************************************************************
//
// ����:	get_SurplusDownloadTime_Dword
// ����:	��
// ����ֵ:	���� ʣ��ʱ��
// ����:	����ʣ��ʱ��
//
//
//************************************************************************
DOUBLE _Nv_Download::get_SurplusDownloadTime_Dword(VOID)
{
	//��ǰ��������
	__int64	dwSize = dwIsSpeed_;

	if (dwSize == 0)
	{
		return 0;
	}

	//���ж���ô��������
	__int64	dwOutSize = n64FileSize_ - get_DownloadCount();
	//��Լ��ʣ�¶�����
	DOUBLE  bOutTime = (double)(dwOutSize / 1024 / (double)(dwSize));
	
	return bOutTime;
}




//************************************************************************
//
// ����:	detect_TaskComplete
// ����:	
// ����ֵ:	 
// ����:	��������Ƿ������
//
//
//************************************************************************
BOOL _Nv_Download::detect_TaskComplete(VOID)
{
	if ((n64FileSize_ != 0) && (n64FileSize_ == get_DownloadCount()))
	{
		DegMsg("������: detect_TaskComplete");
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



//************************************************************************
//
// ����:	thread_SecurityCloseTask
// ����:	
// ����ֵ:	 
// ����:	��ȫ�ر��߳�
//
//
//************************************************************************
BOOL _Nv_Download::thread_SecurityCloseTask(VOID)
{
	//�������ݱ���
	vtTagTaskData.clear();

	//����ֹͣ
	bTaskStop_ = TRUE;

	//��ֹͣ�̹߳�����
	stop_ThreadTask();

	if (bThreadMode_ == FALSE)
	{
		//ֹͣ�����������е��߳�
		DWORD dwSize = vtThread_Task_.size();

		for (int i=0; i<dwSize; ++i)
		{
			vtThread_Task_[i]->stop_Task();
			DegMsg("�Ѱ�ȫ�ر�һ���̡߳�");
		}

		create_DwonloadFile();

		for (int i=0; i<dwSize; ++i)
		{
			delete vtThread_Task_[i];
		}

		vtThread_Task_.clear();
	}
	else
	{
		Nv_One_Download_Task_->stop_Task();
		delete Nv_One_Download_Task_;
		Nv_One_Download_Task_ = NULL;
	}
	return TRUE;
}


//************************************************************************
//
// ����:	read_DwonloadFile
// ����:	
// ����ֵ:	
// ����:	��ȡ�ϵ������ļ�
//
//
//************************************************************************
BOOL _Nv_Download::read_DwonloadFile(VOID)
{
	//����·��
	strDownloadFile_ = strFileSavePath_ + FILE_SAVE_STRCAT_BUF;

	FILE *fp = fopen(strDownloadFile_.c_str(), "r");

	if (fp != NULL)
	{
		DWORD dwSize = 0;
		fscanf(fp, "%u\n", &dwSize);
		//�Ѿ������˶���
		fscanf(fp, "%lld\n", &n64JiDonwloadCnt_);
		
		_Nv_Tag_Download_Data Nv_Tag_Task_Data_;
		for (int i=0; i<dwSize; ++i)
		{
			fscanf(fp, "%lld\n%lld\n%lld\n", 
				&Nv_Tag_Task_Data_.n64X_, &Nv_Tag_Task_Data_.n64TaskCnt_, &Nv_Tag_Task_Data_.n64DownloadCnt_);

			vtTagTaskData.push_back(Nv_Tag_Task_Data_);
		}

		fclose(fp);

		//����
		//greater
		sort(vtTagTaskData.begin(), vtTagTaskData.end(), std::less<_Nv_Tag_Download_Data>());
		//ɾ���ϵ������ļ�
		return DeleteFile(strDownloadFile_.c_str());

	}

	return FALSE;
}




//************************************************************************
//
// ����:	create_DwonloadFile
// ����:	
// ����ֵ:	
// ����:	�����ϵ������ļ�
//
//
//************************************************************************
BOOL _Nv_Download::create_DwonloadFile(VOID)
{
	//����·��
	strDownloadFile_ = strFileSavePath_ + FILE_SAVE_STRCAT_BUF;

	FILE *fp = fopen(strDownloadFile_.c_str(), "w+");

	if (fp != NULL)
	{
		//���浱ǰ�����������ص���������
		DWORD dwSize = vtTagTaskData.size();

		//���浱ǰ������߳���
		fprintf(fp, "%u\n", dwSize);

		fprintf(fp, "%lld\n", get_DownloadCount());

		for (int i=0; i<dwSize; ++i)
		{
			fprintf(fp, "%lld\n%lld\n%lld\n", 
				vtTagTaskData[i].n64X_, vtTagTaskData[i].n64TaskCnt_,vtTagTaskData[i].n64DownloadCnt_);
		}

		fclose(fp);
		return TRUE;
	}

	return FALSE;
}


//************************************************************************
//
// ����:	get_ThreadTaskData
// ����:	
// ����ֵ:	
// ����:	��ȡ�̵߳�����״̬
//
//
//************************************************************************
VOID _Nv_Download::get_ThreadTaskData(__in __int64 n64X, __in __int64 n64TaskCnt, __in __int64 n64DownloadCnt)
{
	_Nv_Tag_Download_Data Nv_Tag_Task_Data_;
	Nv_Tag_Task_Data_.n64X_ = n64X;
	Nv_Tag_Task_Data_.n64DownloadCnt_ = n64DownloadCnt;
	Nv_Tag_Task_Data_.n64TaskCnt_ = n64TaskCnt + 1;

	vtTagTaskData.push_back(Nv_Tag_Task_Data_);

	return;
}



//************************************************************************
//
// ����:	set_ThreadTaskData
// ����:	
// ����ֵ:	
// ����:	
//
//
//************************************************************************
__int64 _Nv_Download::set_ThreadTaskData(__out __int64 &n64X, __out __int64 &n64TaskCnt, __out __int64 &n64Count)
{
	DWORD dwSize = vtTagTaskData.size();
	
	if (dwSize == 0)
	{
		return T_X;
	}

	for (int i=0; i<dwSize; ++i)
	{
		//�����￪ʼ����
		n64X = vtTagTaskData[i].n64X_ + vtTagTaskData[i].n64DownloadCnt_;
		//��ε�������
		n64TaskCnt = vtTagTaskData[i].n64TaskCnt_ - vtTagTaskData[i].n64DownloadCnt_;

		if (dwSize == 1)
		{
			n64Count = vtTagTaskData[i].n64TaskCnt_;
			vtTagTaskData.erase(vtTagTaskData.begin() + i);
			return n64X;
		}

		vtTagTaskData.erase(vtTagTaskData.begin() + i);

		return T_Z;
	}

	return T_X;
}


//************************************************************************
//
// ����:	get_TaskStop
// ����:	
// ����ֵ:	
// ����:	
//
//
//************************************************************************
BOOL _Nv_Download::get_TaskStop(VOID)
{
	if (bTaskStop_ == TRUE)
		DegMsg("������: get_TaskStop");
	return bTaskStop_;
}


//************************************************************************
//
// ����:	get_DownloadTaskCmdOut
// ����:	
// ����ֵ:	
// ����:	
//
//
//************************************************************************
BOOL _Nv_Download::get_DownloadTaskCmdOut(VOID)
{
	if (bDownloadTaskCmd_ == TRUE)
		DegMsg("������: get_DownloadTaskCmdOut");
	return bDownloadTaskCmd_;
}


//************************************************************************
//
// ����:	get_StopPrintf
// ����:	
// ����ֵ:	
// ����:	���ⲿ��ʾ���ȴ����ж��Ƿ����ֹͣ��ʾ����
//
//
//************************************************************************
BOOL _Nv_Download::get_StopPrintf(VOID)
{
	if ((detect_TaskComplete() == TRUE) || (get_TaskStop() == TRUE) || (get_DownloadTaskCmdOut() == TRUE))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}




//************************************************************************
//
// ����:	detect_DownlaodIsClose
// ����:	
// ����ֵ:	
// ����:	�������Ƿ��Ѿ���ȫֹͣ�� �ﵽ�����ͷŸ����Ŀ��
//
//
//************************************************************************
BOOL _Nv_Download::detect_DownlaodIsClose(VOID)
{
	DWORD dwOutCode = 0;
	BOOL bRet = FALSE;

	::GetExitCodeThread(Handle_DetectTask_, &dwOutCode);
	if (dwOutCode == Thread_download_Ok)
	{
		CloseHandle(Handle_DetectTask_);
		bRet = TRUE;

		if (bRet == FALSE)
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	::GetExitCodeThread(Handle_ThreadTask_, &dwOutCode);
	if (dwOutCode == Thread_Download_Fun)
	{
		CloseHandle(Handle_ThreadTask_);
		bRet = TRUE;

		if (bRet == FALSE)
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}


//************************************************************************
//
// ����:	deetct_ThreadMode
// ����:	
// ����ֵ:	
// ����:	����Ƕ��߳����� ���ǵ��߳�����
//
//
//************************************************************************
BOOL _Nv_Download::deetct_ThreadMode(VOID)
{
	return bThreadMode_;
}