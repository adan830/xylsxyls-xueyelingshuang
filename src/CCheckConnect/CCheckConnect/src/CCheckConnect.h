#pragma once
#include <afxwin.h>
#include "API.h"

class CCheckConnectAPI CCheckConnect{
public:
	int IfConnect;
	CString IP;
	int port;

public:
	//ֻ�ж������Ƿ�ͨ����WaitTimeΪ���ȴ�ʱ�䵥λ���룬������ӳɹ�����������1��ʧ�ܷ���0
	bool Connect(CString IP,int port,unsigned int WaitTime);
	//ͨ��ping���
	bool ConnectWithPing(CString IP,int WaitTime);
};