#pragma once
#include <afxsock.h>
#include "CCheckConnectMacro.h"
#include <string>
using namespace std;

class CCheckConnectAPI CCheckConnect{
public:
	//ֻͨ��IP����Ƿ�����
	bool CheckWithIP(string IP,int CheckTimes = 3,unsigned int WaitTimeForOne = 10);
	//ͨ��IP�Ͷ˿ڼ��
	bool CheckWithIPPort(string IP,int Port,unsigned int WaitTime = 300);
};