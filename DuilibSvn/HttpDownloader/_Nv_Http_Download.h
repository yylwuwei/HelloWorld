//////////////////////////////////////////////////////////////////////////
//
//��:http ���̶߳ϵ�����   
//����: ����(Nature Virus) 
//ʱ��: 2012.10.7 - 2012.10.9
//��ע: ���д��� �� ������ĵ��� ������ϵ��.�������޸�
//QQ: 8035408
//
//////////////////////////////////////////////////////////////////////////



#pragma once


#include <Windows.h>
#include <wininet.h>
#include <iostream>
#include <process.h>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>


class _Nv_Download;

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ws2_32.lib")

//string
using std::string;
using std::vector;
using std::sort;


#define		Msg(msg)		::MessageBox(NULL, msg, "��Ϣ", 0)
#define		DegMsg(msg)		OutputDebugStringA(msg)
#define		DegMsgW(msg)	OutputDebugStringW(msg)

//////////////////////////////////////////////////////////////////////////
//
#define		Run_Mode_1								FALSE
#define		Run_Mode_2								TRUE
//����״̬
#define		Http_Return_206							206
#define		Http_Return_200							200

//�߳��˳�
#define		Thread_download_Out						0x110
#define		Thread_download_Ok						0x111
#define		Thread_ThreadTask_Out					0x112
#define		Thread_Download_Fun						0x113

//�ź�״̬
#define		T_X										0x1
#define		T_Y										0x2
#define		T_Z										0x3

//����״̬
#define		Thread_OK								0x01
#define		Thread_ON								0x02


//////////////////////////////////////////////////////////////////////////
//�ϵ㴫�ļ�
#define		FILE_SAVE_STRCAT_BUF					".NatureVirusDownloadFile"


//�ϵ����������ÿ���̵߳�״̬
struct _Nv_Tag_Download_Data
{
	__int64		n64X_;
	__int64		n64DownloadCnt_;
	__int64		n64TaskCnt_;

	_Nv_Tag_Download_Data()
	{
		n64X_ = n64TaskCnt_ = n64DownloadCnt_ = 0;
	}

	bool operator <   (const _Nv_Tag_Download_Data& rhs )   const 
	{
		return n64X_ < rhs.n64X_;
	}
	bool operator >   (const _Nv_Tag_Download_Data& rhs )   const
	{
		return n64X_ > rhs.n64X_;
	}
};


class _Nv_Download_Task
{
public:
	//����
	//ƽ����������
	_Nv_Download_Task(
		__in CONST CHAR *strDownloadUrl, 
		__in CONST CHAR *strSaveFilePath, 
		__in __int64 _n64X,  
		__in __int64 _n64Size,
		__out int *nCallCnt,
		__in CONST CHAR *strCoolie,
		__in BOOL bFalg = Run_Mode_2
		);
	//��ͨ����
	_Nv_Download_Task();
	~_Nv_Download_Task();

public:
	//�����¼
	DWORD		dwError_;

	//http
	HINTERNET	Hinternet_Main_;
	HINTERNET	Hinternet_OpenUrl_;
	HINTERNET	Hinternet_Connect_;
	HINTERNET	Hinternet_Request_;
	
	//����
	CHAR		strHostName_[1024];
	CHAR		strFileName_[1024];

	//��������
	int		*nCallByteCnt_;
	__int64	*n64CallByteCnt_;

	//��¼url
	string		strUrl_;
	//��¼�����ļ�·��
	string		strFilePath_;
	//��¼�ϵ������ļ�
	string		strDownloadFile_;
	//��¼�ļ���С
	__int64		n64FileSize_;

	//��¼x y
	__int64		n64X_, n64Y_;

	//Ŀ�������ֽ�
	__int64		n64DownloadSize_;

	//ֹͣ����
	BOOL		bStop_Download_;
	HANDLE		Handle_Stop_Download_;
	//�߳̾��
	HANDLE		Handle_Download_Ok;

	//��¼��ǰ�����������˶����ֽ�
	__int64		n64_Download_Byte_Cnt_;

	//����
	DWORD		*dwSleep_;
	//���������
	DWORD		dwTaskOk_;

	//�Ƿ���Coolie
	BOOL		bCoolie_;
	string		strCoolie_;

	//������ָ��
	_Nv_Download	*Nv_Download_Ptr_;
	//////////////////////////////////////////////////////////////////////////
	//����
	//���پ��
	BOOL	NvInternetCloseHandle	(__in HINTERNET hDelete);
	//���غ���
	BOOL	NvDownload_Task			(__in CONST CHAR *strSaveFilePath);
	//��ȡ��������ָ��
	BOOL	get_DownloadThisPtr		(__in _Nv_Download *nv_this);
	//����ֹͣ�ź�
	BOOL	stop_Task				(VOID);
	
	//��ȡ�ļ���С
	__int64	get_UrlFileSizeAndFileName(
		__in	CONST CHAR *strUrl,
		OUT CHAR *strFileName, 
		__in	CONST CHAR *strCoolie
		);

	//�����Ƿ�֧�ֶ��߳�
	INT		Detece_ThreadMode		( 
		__in CONST CHAR *strUrl, 
		__in __int64 dwMinPos, 
		__in __int64 dwMaxPos, 
		__in CONST CHAR *strCoolie 
		);

	//���߳�����
	__int64 SinglethreadDwondLoad	( 
		__in CONST CHAR *strDownloadUrl, 
		__in CONST CHAR *strSaveFilePath, 
		__out __int64 *n64CallCnt, 
		__in CONST CHAR *strCoolie
		);

protected:
private:
	//��INET
	BOOL NvInternetOpen		(__in CONST CHAR *strHttpName, __in INT nFalg);
	//ֱ�Ӵ�URL
	BOOL NvInternetOpenUrl	(__in CONST CHAR *strUrl, __in INT nFalg);
	//����URL
	BOOL NvAnalyzeURL		(__in CONST CHAR *strUrl);
	//����HTTP
	BOOL NvInternetConnect	(__in CHAR *strHostName);
	//�����Ϣͷ
	BOOL NvHttpOpenRequest	(__in CONST CHAR *strAcceptTypes, __in CHAR *strFileName, __in CONST CHAR *strHttpType, __in DWORD dwFalg);
	//��������
	BOOL NvHttpSendRequest	(VOID);
	//���öϵ�����λ��
	BOOL NvHttpAddRequestHeaders(__in HINTERNET hRequest, __in __int64 dwMinPos, __in __int64 dwMaxPos, __in INT nFalg);
	//����״̬ ��
	__int64 NvHttpQueryInfo	(__in HINTERNET hRequest, __in INT nFalg);
	VOID	NvHttpQueryInfo	(__in HINTERNET hRequest, __in INT nFalg, OUT CHAR *strFileName);
	
	//////////////////////////////////////////////////////////////////////////
	//��ʼ��
	VOID	Init(VOID);
	//////////////////////////////////////////////////////////////////////////
	//���Է���ֵ
	DWORD	GetHttpReturnData	(
		__in	CONST CHAR	*strUrl, 
		__in	__int64 dwMinPos, 
		__in	__int64 dwMaxPos, 
		__in	CONST CHAR	*strCoolie
		);

	BOOL	Thread_Task				(VOID);

	//ֹͣ����
	VOID	stop_Download			(VOID);
	__int64 get_Download_Byte_Cnt	(VOID);
	VOID	set_Coolie				(__in CONST CHAR *strCoolie);
};




class _Nv_Download
{
public:
	//////////////////////////////////////////////////////////////////////////
	//����
	_Nv_Download();
	_Nv_Download( 
		__in CONST CHAR *strDownloadUrl, 
		__in CONST CHAR *strSaveFilePath, 
		__in CONST CHAR *strCoolie, 
		__in BOOL bModeFalg  = Run_Mode_2
		);
	~_Nv_Download();

public:
	//////////////////////////////////////////////////////////////////////////
	//����
	CRITICAL_SECTION chitical_section_;
	CRITICAL_SECTION chitical_section_Add;

	BOOL		bCoolie_;
	string		strCoolie_;

	//����������߳���
	DWORD		dwThreadCnt_;
	//ÿ������������
	__int64		n64ThreadDownloadCnt_;
	//��һ���������ʼλ��
	__int64		n64ThreadTaskSion_;
	//�ļ���С
	__int64		n64FileSize_;

	//�����߳��б�
	vector<_Nv_Download_Task*>		vtThread_Task_;

	//��¼��ǰ�����е�url
	string		strUrl_;
	string		strFileSavePath_;
	//�����ļ�
	string		strDownloadFile_;

	//������
	__int64		n64DownloadCount_;
	int			nDataCount_;
	int			*nDownloadCount_;
	DWORD		dwDownloadVectorSize_;

	//��������̰߳�ȫ�ź�
	HANDLE		Handle_DetectTask_;
	//��������̰߳�ȫ�ź�ǿ���˳�
	HANDLE		Handle_DetectTask_Out_;
	//�̹߳�������ȫ�ź�
	HANDLE		Handle_ThreadTask_;
	//�̹߳�����ǿ���˳��ź�
	HANDLE		Handle_ThreadTask_Out_;

	//��ǰ������
	__int64		n64JiDonwloadCnt_;

	//ʱ���
	__int64		n64TimeDownloadCnt_;

	//��ǰ����
	DWORD		dwIsSpeed_;

	//����ϵ�����ÿ���̵߳�����
	vector<_Nv_Tag_Download_Data>	vtTagTaskData;
	//δ������� ��Ҫ��������
	vector<_Nv_Tag_Download_Data>	vtDownloadNo_;

	//ֹͣ��������
	BOOL		bTaskStop_;

	//��������������Ѿ��˳�
	BOOL		bDownloadTaskCmd_;

	//���߳�����
	_Nv_Download_Task				*Nv_One_Download_Task_;
	//����ǵ��߳�����
	BOOL							bThreadMode_;
	//���߳����صļ�����
	__int64							n64ThreadOneCnt_;

public:
	//////////////////////////////////////////////////////////////////////////
	//����
	VOID	Init(VOID);
	//��ȡ�ļ���С
	__int64	get_TaskFileSize(__in CONST CHAR *strDownloadUrl);

	//��ȡ��ǰ�Ѿ����ض����ֽ�
	__int64 get_DownloadCount		(VOID);
	//�����ٶȲ�
	VOID	set_TimeCount			(VOID);
	//��ȡ��������
	__int64 get_DownloadSpeed		(VOID);
	//��ȡ������ػ�ʣ�����ʱ�� �����ַ���
	CHAR*	get_SurplusDownloadTime	(VOID);
	//���ö��߳�����
	VOID	set_ThreadCount			(__in DWORD dwThreadCount);
	//����ÿ���߳���Ҫ���ض����ֽ�
	VOID	set_DownloadTaskCnt		(__in DWORD dwDownloadTaskCnt);
	//��������Ƿ����
	BOOL	detect_TaskComplete		(VOID);
	//��ȫ�ر�����
	BOOL	thread_SecurityCloseTask(VOID);
	//����߳����������Ƿ����
	VOID	detect_vtThread_Task	(VOID);
	//��ȡ������ػ�ʣ�����ʱ�� ��������
	DOUBLE	get_SurplusDownloadTime_Dword(VOID);
	//��ȡ�Ƿ�ر�����
	BOOL	get_TaskStop			(VOID);
	//����������
	VOID	set_HttpLinkCount		(__in DWORD dwCount);
	//��ȡ�̹߳������Ƿ��Ѿ��˳�
	BOOL	get_DownloadTaskCmdOut	(VOID);
	//���ⲿ��ʾ���ȴ����ж��Ƿ����ֹͣ��ʾ����
	BOOL	get_StopPrintf			(VOID);
	//�Ƿ�������ٸ���
	BOOL	detect_DownlaodIsClose	(VOID);
	//���̺߳���
	VOID	detect_vtThreadOne_Task	(VOID);
	//����Ƕ��߳����ػ��ǵ��߳�����
	BOOL	deetct_ThreadMode		(VOID);
	
	
	//��ȡ�����߳�״̬
	VOID	get_ThreadTaskData(
		__in __int64 n64X, 
		__in __int64 n64TaskCnt, 
		__in __int64 n64DownloadCnt
		);

	//����
	BOOL	thread_Task( 
		__in CONST CHAR *strDownloadUrl, 
		__in CONST CHAR *strSaveFilePath, 
		__in CONST CHAR *strCoolie, 
		__in BOOL bModeFalg  = Run_Mode_2
		);

	//���߳�����
	BOOL thread_OneTask( 
		__in CONST CHAR *strDownloadUrl, 
		__in CONST CHAR *strSaveFilePath, 
		__in CONST CHAR *strCoolie, 
		__in BOOL bModeFalg  = Run_Mode_2
		);

	//���߳����ص���
	BOOL	Download(
		__in CONST CHAR *strUrl, 
		__in CONST CHAR *strFileSavePath, 
		__in CONST CHAR *strCoolie, 
		__in BOOL bModeFalg = Run_Mode_2
		);

protected:
private:
	//��������
	BOOL	call_AssignTasks		(__in __int64 &n641, __in __int64 &n642, __in __int64 &n643);
	//ֹͣ�����������
	VOID	stop_DetectTask		(VOID);
	//ֹͣ�߳���������
	BOOL	stop_ThreadTask		(VOID);
	//�����ϵ������ļ�
	BOOL	create_DwonloadFile	(VOID);
	//��д�ϵ������ļ�
	BOOL	read_DwonloadFile	(VOID);

	//�ϵ������̲߳���
	__int64	set_ThreadTaskData(
		__out __int64 &n64X, 
		__out __int64 &n64TaskCnt,
		__out __int64 &n64Count
		);

	//�޲������߳�
	BOOL decete_TaskFailure( 
		__in CONST CHAR *strDownloadUrl, 
		__in CONST CHAR *strSaveFilePath, 
		__in CONST CHAR *strCoolie 
		);
};