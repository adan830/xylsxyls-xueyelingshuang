#pragma once
#include "CHttpString.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"
#include <afxmt.h>
#include "Cjson/CjsonAPI.h"
#include "CAceHttpServerMacro.h"

#define Create_Thread(FunName,ParameterName,ThreadID) CreateThread(NULL, 0, FunName, (LPVOID)ParameterName, 0, &ThreadID)

#ifdef _DEBUG
#pragma comment(lib,"ACEd.lib")
#else
#pragma comment(lib,"ACE.lib")
#endif

class CAceHttpServer{
	//�������ȿ�����init֮���Ѿ���һ���߳�������recv��
public:
	ACE_SOCK_Acceptor* pacceptor;
	CMutex mutex;
	//���ݸ�ʽ
	int DataStyle;

public:
	CAceHttpServer();
	~CAceHttpServer();

public:
	//�򿪶˿ڳɹ�֮�����һ���̺߳�̨�ȴ��ͻ�������
	//һ���пͻ����������������߳��п����߳����ڴ����͵���Ϣ����֤һֱ��һ���̵߳ȴ�����
	BOOL init(int port,int RecvMaxLength,int DataStyle = 1);

	int SendRspJson(Cjson jsonRsp,CString strProtocol,ACE_SOCK_Stream* ppeer,int sendTimes = 3);
	//�麯�������е�ͨ·��Ϣ���룬�������Ϊ����Ĭ��Ϊ�ظ�

	virtual Cjson ReceiveReqJson(Cjson jsonReq,CString strProtocol,CHttpString str) = 0;
};