#pragma once
#include "CLocalIPPort.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Connector.h"
#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"

class CAceClient{
public:
	ACE_INET_Addr* paddr;
	ACE_SOCK_Connector* pconnector;
	ACE_SOCK_Stream* ppeer;

public:
	~CAceClient();

public:
	BOOL init(CString strIP,int port,int ConnectWaitTime);

	//���������׵�ַ�����ݳ��ȣ����ʹ������ɹ��򲻼����������Ƿ���շ�����Ϣ���������󳤶ȣ�����ʵ�ʽ��ճ��ȣ������ȴ�����ʱ��
	BOOL send(char *pData,int length,int sendTimes,BOOL ifRecv,int *maxLength,int recvWaitTime);

	virtual BOOL recv(char *pData,int length) = 0;
};