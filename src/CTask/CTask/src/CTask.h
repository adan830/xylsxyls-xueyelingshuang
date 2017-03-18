#pragma once
#include <string>
#include "CTaskMacro.h"
using namespace std;

class CTaskAPI CTask{
	//Run()��SuspendRun()���������д
public:
	CTask();
public:
	enum{
		INITSUCCESS = 1,
		RUNSUCCESS = 1,
		RUNBACK = 0,
		RUNSUSPEND = 2
	};
public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	//?UUID��ΪTask��Ψһ��ʶ
	string uuid;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
	//?�������̽ڵ㣬-1��ʾ������0��ʾ��ʼ����1��ʾ�Ѿ���������
	int node;
	//?�Ƿ����ü���쳣����
	bool ifExceptionRun;
	//?�����ʼ��
	void init(int level, bool ifExceptionRun = 0);
	//?����Ƿ���������Լ���ʼ����ǰ�ڵ㣬����1��ʾ��������
	virtual int initRun();
	//?����ִ�����ݣ�����RUNSUCCESS��ʾ��ֹ���񣬺�̨����߳�һ��رգ�����RUNBACK��ʾ��̨���һֱ���У�����RUNSUSPEND��ʾ�ֶ�������ͣ
	virtual int Run();
	//?������ͣ��������������֮ͣ��Run��������0���´��жϴ������Ƿ�����ͣס�ģ�������Ƚ���ָ�����Ȼ����ݽڵ�����ϴ���ͣ�ĵط�
	virtual void SuspendRun();
	//?�쳣��������-1��ʾCheckRun���󣬷���1��ʾ��ֹ����
	virtual void ExceptionRun(int exception);
	//?��̨����쳣�������쳣���𣬲�����������������ѭ��
	virtual int CheckException();
	//?����Ϊ������
	void SetEmpty();
	//?���������Ƿ���Ч
	bool isValid();
};