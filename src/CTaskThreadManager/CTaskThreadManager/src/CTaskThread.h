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
    void PostTask(const std::shared_ptr<CTask>& task, __int32 taskLevel);

    /* ͬ��ִ�����񣬵�����û�����Ƿ����߳̿�ס������������Ȼ�����߳���ִ��
    */
    void SendTask(const std::shared_ptr<CTask>& task, __int32 taskLevel);

    /* �ж�����������Ƿ�������
    */
    bool HasTask();

    void StopTask(__int32 taskId, bool ifChoke, __int32 taskLevel = 0);

    void StopAllTask();

    /* ��ȡ��ǰmap������������ú�������մ����map
    @param [out] taskCountMap ������������ȼ����ұ��ǵ�ǰ���ȼ����������
    */
    void GetWaitTaskCount(std::map<__int32, __int32>& taskCountMap);

private:
    CTaskThread(__int32 threadId);

    bool CreateThread();

    void DeleteThread();

    /* ��ȡ������ȼ�����
    * �����������������������������ȼ�����ͬʱ����������֮���Ƿ���Ҫɾ���ü������
    */
    void PopToCurTask();

    void StopTaskInList(const std::list<std::shared_ptr<CTask>>& taskList, __int32 taskId, bool ifChoke);

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
    __int32 �������ȼ�
    */
    std::map<__int32, std::list<std::shared_ptr<CTask>>> m_taskMap;

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
    __int32 m_curTaskLevel = 0;

    /* �߳�ID
    */
    __int32 m_threadId = 0;
};