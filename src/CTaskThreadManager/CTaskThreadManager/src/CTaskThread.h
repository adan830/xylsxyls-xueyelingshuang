#pragma once
#include "CTask.h"
#include <list>
#include <map>
#include <thread>
#include <memory>
#include <mutex>
#include <atomic>

class CTaskThreadManagerAPI CTaskThread
{
    friend class CTaskThreadManager;
public:
    /* ��������������ȼ��������1
    */
    void PostTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel);

    /* ͬ��ִ�����񣬵�����û�����Ƿ����߳̿�ס������������Ȼ�����߳���ִ��
    */
    void SendTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel);

    /* �ж�����������Ƿ�������
    */
    bool HasTask();

    void StopTask(int32_t taskId, bool ifChoke, int32_t taskLevel = 0);

    void StopAllTask();

    /* ��ȡ��ǰmap������������ú�������մ����map
    @param [out] taskCountMap ������������ȼ����ұ��ǵ�ǰ���ȼ����������
    */
    void GetWaitTaskCount(std::map<int32_t, int32_t>& taskCountMap);

private:
    CTaskThread(int32_t threadId);

    bool CreateThread();

    void DestroyThread();

    /* �����˳��ź�
    */
    void SetExitSignal();

    /* �����̵߳�ʱ��ȴ��߳��˳�
    */
    void WaitForExit();

    /* ��ȡ������ȼ�����
    * �����������������������������ȼ�����ͬʱ����������֮���Ƿ���Ҫɾ���ü������
    */
    void PopToCurTask();

    void StopTaskInList(const std::list<std::shared_ptr<CTask>>& taskList, int32_t taskId, bool ifChoke);

    //�����߳��������£�ִ�е�ǰ����ִ���������������Ƿ������������������ŵ���ǰ�����У������ǰ����û��������
    void WorkThread();

    void StopAllTaskUnlock();

    bool HasTaskUnlock();

private:

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    /*
    int32_t �������ȼ�
    */
    std::map<int32_t, std::list<std::shared_ptr<CTask>>> m_taskMap;

    /* ����ִ�е�����
    */
    std::shared_ptr<CTask> m_spCurTask;

    /* ����ִ������ı��ݣ����ڱ�����������ʱ����
    */
    std::shared_ptr<CTask> m_spCurTaskBk;

    /* �����߳�ָ��
    */
    std::unique_ptr<std::thread> m_spWorkThread;

    /* �߳���
    */
    std::mutex m_mutex;

    /* �߳��Ƿ����˳��ź�
    */
    std::atomic<bool> m_hasExitSignal = false;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    
    /* ����ִ����������ȼ�
    */
    int32_t m_curTaskLevel = 0;

    /* �߳�ID
    */
    int32_t m_threadId = 0;

	/* �ȴ��¼�
	*/
	HANDLE m_waitEvent;
};