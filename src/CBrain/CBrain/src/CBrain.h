#pragma once
#include "CBrainMacro.h"
#include <map>
#include <list>
#include <thread>
#include <mutex>
#include <atomic>
#include "CTask/CTaskAPI.h"
using namespace std;

class CBrain{
public:
	enum{
		RUN,
		SUSPEND,
		END
	};
	map<int, atomic<bool>> ctrl;
	map<int, list<CTask>> mapTask;
	list<CTask> listTaskBack;
	mutex mutex;
	thread* workThread;
	thread* backThread;
	CTask currentTask;
public:
	CBrain();
	//?������Ϣ��ʼ�ղ��У���ʼ������������ִ����ͣ��ֹ��1��ʼ0��ͣ-1��ֹ
	//void listen(int flag = 1);
	//?�����б�levelΪ�������ȼ���0Ϊ���
	void push_back(const CTask& task, int level);
	//?��ʼִ������
	void Run();
	//?��ִͣ������
	void SuspendRun();
	//?����ִ������
	void EndRun();
	//?�����߳�
	void ThreadWork();
	//?��̨�߳�
	void ThreadBack();
	//?ִ�����񣬵ȴ�ʱ��
	//?��ͣ���񣬵ȴ�ʱ��
	//?��ֹ���񣬵ȴ�ʱ��
	//?��̨��⣬һ�����������������������
};