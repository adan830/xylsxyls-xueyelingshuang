#pragma once
#include "CLocalIPPort.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"
#include <afxmt.h>
#include <vector>
using namespace std;
#include "CAceTCPServerMacro.h"

#ifdef _DEBUG
#pragma comment(lib,"ACEd.lib")
#else
#pragma comment(lib,"ACE.lib")
#endif

class CLocalIPPort;
class CAceTCPServerAPI CAceTCPServer{
	//�������ȿ�����init֮���Ѿ���һ���߳�������recv��
public:
	ACE_SOCK_Acceptor* pacceptor;
	vector<ACE_SOCK_Stream*> vecIPPeer;
	CMutex mutex;

public:
	CAceTCPServer();
	~CAceTCPServer();

public:
	//�򿪶˿ڳɹ�֮�����һ���̺߳�̨�ȴ��ͻ�������
	//һ���пͻ����������������߳��п����߳����ڴ����͵���Ϣ����֤һֱ��һ���̵߳ȴ�����
	BOOL init(int port,int RecvMaxLength);
	//���һ���ǵ�ǰ������Ϣ�Ŀͻ���ͨ·��ַ
	virtual void Receive(char* pData,int length,ACE_SOCK_Stream* ppeer) = 0;
	//���������׵�ַ�����ͳ��ȣ�ͨ·��ַͨ��vecIPPeer��ȡ������ʵ�ʷ��ͳ�ȥ�ĳ���
	int Send(char* pData,int length,ACE_SOCK_Stream* ppeer);
	CLocalIPPort GetLocalIPPort(ACE_SOCK_Stream* ppeer);
};