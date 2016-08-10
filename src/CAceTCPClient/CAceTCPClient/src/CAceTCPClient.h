#pragma once
#include "CLocalIPPort.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Connector.h"
#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"
#include <afxmt.h>
#include "CAceTCPClientMacro.h"

#ifdef _DEBUG
#pragma comment(lib,"ACEd.lib")
#else
#pragma comment(lib,"ACE.lib")
#endif

class CAceTCPClientAPI CAceTCPClient{
	//�ڳ�ʼ��֮����Ѿ���һ���߳�����recv��
public:
	ACE_SOCK_Connector* pconnector;
	ACE_SOCK_Stream* ppeer;
	CMutex mutex;

public:
	~CAceTCPClient();

public:
	//�ͷ��������ӳɹ��򷵻�1��ʧ�ܷ���0������֮�����һ���̺߳�̨���շ������������͵Ķ�����RecvMaxLengthΪ���ջ���������
	BOOL init(CString strIP,int port,int ConnectWaitTime,int RecvMaxLength);

	//���������׵�ַ�����ݳ��ȣ����ʹ������ɹ��򲻼�������������ʵ�ʷ��ͳ�ȥ�ĳ���
	int send(char *pData,int length,int sendTimes);

	virtual void Receive(char *pData,int length) = 0;
};