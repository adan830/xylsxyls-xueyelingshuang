#pragma once
#include <string>
#include "CTaskMacro.h"
using namespace std;

class CTaskAPI CTask{
	//Run()��SuspendRun()���������д
public:
	CTask();
public:
	//?UUID��ΪTask��Ψһ��ʶ
	string uuid;
	//?�������̽ڵ㣬0��ʾ��ʼ����1��ʾ�Ѿ���������
	int node;
	//?�Ƿ����ü���쳣����
	bool ifExceptionRun;
	//?�����ʼ��
	void init(int level, bool ifExceptionRun = 0);
	//?��⵱ǰ״̬�Ƿ����ִ��
	virtual bool CheckRun();
	//?����ִ�����ݣ�����1��ʾ��ֹ���񣬺�̨����߳�һ��ر�
	virtual bool Run();
	//?������ͣ����
	virtual bool SuspendRun();
	//?�쳣��������1��ʾ��ֹ����
	virtual void ExceptionRun(int exception);
	//?��̨����쳣�������쳣���𣬲�����������������ѭ��
	virtual int CheckException();
};