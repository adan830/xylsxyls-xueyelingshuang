#pragma once
#include <afxsock.h>
#include "CCheckConnectMacro.h"

class CCheckConnectAPI CCheckConnect{
public:
	//ֻͨ��IP����Ƿ�����
	bool CheckWithIP(CString IP,int CheckTimes = 3,unsigned int WaitTimeForOne = 10);
	//ͨ��IP�Ͷ˿ڼ��
	bool CheckWithIPPort(CString IP,int Port,unsigned int WaitTime = 300);
};