#pragma once
#include "CBrainMacro.h"
#include <map>
#include <list>
#include <thread>
#include <mutex>
#include <atomic>
#include "CTask/CTaskAPI.h"
using namespace std;

class CBrainAPI CBrain{
public:
	enum{
		RUN,
		SUSPEND,
		SUSPENDED,
		END
	};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	map<int, atomic<bool>> ctrl;
	map<int, list<CTask*>> mapTask;
	list<CTask*> listTaskBack;
	mutex mutex;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
	thread* workThread;
	thread* backThread;
	int currentLevel;
	CTask* currentTask;
	CTask emptyTask;
public:
	CBrain();
	//?������Ϣ��ʼ�ղ��У���ʼ������������ִ����ͣ��ֹ��1��ʼ0��ͣ-1��ֹ
	//void listen(int flag = 1);
	//?�����б�levelΪ�������ȼ���0Ϊ���
	void push_back(CTask* task, int level);
	//?��ʼִ������
	void Run();
	//?��ִͣ������
	void SuspendRun();
	//?�ָ�ִ������
	void RecoveryRun();
	//?����ִ������
	void EndRun();
	//?�����߳�
	void ThreadWork();
	//?��̨�߳�
	void ThreadBack();
	//?ɾ��ǰִ̨�У������ڲ�����
	void DeleteTask(CTask* task);
	//?ɾ����̨��⣬�����ڲ�����
	void DeleteBack(CTask* task);
	//?ȡ��������ȼ������񣬲�����ǰ�����ƶ�����ǰ���ȼ��Ķ�β
	void GetCurrentTask();
	//?��������ӽ���̨����б�
	void AddBack(CTask* task);
	//?�ƶ�����β
	void MoveToEnd(CTask* task);
	//?ִ�����񣬵ȴ�ʱ��
	//?��ͣ���񣬵ȴ�ʱ��
	//?��ֹ���񣬵ȴ�ʱ��
	//?��̨��⣬һ�����������������������
};