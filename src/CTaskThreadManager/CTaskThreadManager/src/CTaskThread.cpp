#include "CTaskThread.h"
#include <assert.h>

CTaskThread::CTaskThread(__int32 threadId) :
m_threadId(threadId)
{

}

bool CTaskThread::CreateThread()
{
    //�����Ƚ�m_hasExitSignal��Ϊfalse������һ�����̺߳������˳���
    std::thread* pThread = new std::thread(std::bind(&CTaskThread::WorkThread, this));
    if (pThread == nullptr)
    {
        m_hasExitSignal = true;
        return false;
    }
    m_spWorkThread.reset(pThread);
    return true;
}

void CTaskThread::DeleteThread()
{
    //����߳���������
    if (m_spWorkThread != NULL)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_hasExitSignal = true;
            StopAllTaskUnlock();
        }
        m_spWorkThread->join();
        
        std::map<__int32, __int32> taskCountMap;
        GetWaitTaskCount(taskCountMap);
        m_spWorkThread.reset(NULL);
    }
}

void CTaskThread::PostTask(const std::shared_ptr<CTask>& task, __int32 taskLevel)
{
    if (task == NULL || taskLevel < 1 || m_hasExitSignal)
    {
        return;
    }
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_hasExitSignal)
    {
        return;
    }
    m_taskMap[taskLevel].push_back(task);
    //��������������ȼ����ڵ�ǰ������ǰ����ֹͣ
    if (m_spCurTask != NULL && taskLevel > m_curTaskLevel)
    {
        //���������������Ǳ�������������������Ӵ������п��Ƿ�ֹ��ǰ����û���ü��˳�������˶�����ȼ����ߵ�����
        if (m_spCurTaskBk != NULL && m_spCurTask->ReExecute())
        {
            m_taskMap[m_curTaskLevel].push_front(m_spCurTaskBk);
            m_spCurTaskBk = NULL;
        }
        m_spCurTask->StopTask(false);
    }
}

void CTaskThread::SendTask(const std::shared_ptr<CTask>& task, __int32 taskLevel)
{
    if (task == NULL || taskLevel < 1 || m_hasExitSignal)
    {
        return;
    }

    PostTask(task, taskLevel);
    
    while (!task->HasExecuted())
    {
        std::chrono::milliseconds dura(50);
        std::this_thread::sleep_for(dura);
    }
}

void CTaskThread::WorkThread()
{
    //���˳��źţ����Ƕ������еȴ�����ʱ��Ȼ����ѭ������ѭ���ڴ����������
    while (!m_hasExitSignal || HasTask())
    {
        //�����ǰ���˳��źţ�����յȴ�����ͬʱ�ѵ�ǰ����ֹͣ
        if (m_hasExitSignal)
        {
            if (m_spCurTask != NULL)
            {
                m_spCurTask->StopTask(false);
            }
            std::unique_lock<std::mutex> lock(m_mutex);
            m_taskMap.clear();
        }
        //�����ǰ������
        if (m_spCurTask != NULL)
        {
            m_spCurTask->DoTask();
        }
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            //һ�����˳��ź��򽫵�ǰ������Ϊ��
            if (m_hasExitSignal)
            {
                m_spCurTask = NULL;
            }
            else
            {
                //ȡ����û��������m_spCurTask��Ϊ�գ������������m_spCurTask������ʣ�����ɾ��ԭ�ж��нڵ�
                PopToCurTask();
            }
        }

        //���˳��źţ����ڵ�������֮��ǰ������ȻΪ��ʱ����
        if (!m_hasExitSignal && m_spCurTask == NULL)
        {
            std::chrono::milliseconds dura(50);
            std::this_thread::sleep_for(dura);
        }
    }
}

void CTaskThread::StopAllTaskUnlock()
{
    for (auto itListTask = m_taskMap.begin(); itListTask != m_taskMap.end(); ++itListTask)
    {
        auto listTask = itListTask->second;
        for (auto itTask = listTask.begin(); itTask != listTask.end(); ++itTask)
        {
            (*itTask)->StopTask(false);
        }
    }
    //����л�δִ����ϵ�����
    if (m_spCurTask != NULL)
    {
        m_spCurTask->StopTask(false);
    }
}

bool CTaskThread::HasTaskUnlock()
{
    return !m_taskMap.empty();
}

bool CTaskThread::HasTask()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return HasTaskUnlock();
}

void CTaskThread::PopToCurTask()
{
    if (HasTaskUnlock())
    {
        //���������ȡ�����һ�����ȼ��Ķ������񼯺�
        auto itTaskList = --(m_taskMap.end());
        std::list<std::shared_ptr<CTask>>& listTask = itTaskList->second;
        //�����һ�����ȼ����е��׸�����ȡ��
        m_spCurTask = listTask.front();
        m_spCurTaskBk.reset(m_spCurTask->Clone());
        m_curTaskLevel = itTaskList->first;
        //ֻҪ�м��Ͼͱ���������
        if (m_spCurTask == NULL)
        {
            assert(0);
        }
        listTask.pop_front();
        //����ü��������û��������ɾ���ü�����map�еĽڵ�
        if (listTask.empty())
        {
            m_taskMap.erase(itTaskList);
        }
    }
    else
    {
        m_spCurTask = NULL;
        m_spCurTaskBk = NULL;
        m_curTaskLevel = 0;
    }
}

void CTaskThread::StopTask(__int32 taskId, bool ifChoke, __int32 taskLevel)
{
    if (taskLevel != 0)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        auto itListTask = m_taskMap.find(taskLevel);
        if (itListTask != m_taskMap.end())
        {
            StopTaskInList(itListTask->second, taskId, ifChoke);
        }
    }
    else
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        for (auto itListTask = m_taskMap.begin(); itListTask != m_taskMap.end(); ++itListTask)
        {
            StopTaskInList(itListTask->second, taskId, ifChoke);
        }
    }
}

void CTaskThread::StopTaskInList(const std::list<std::shared_ptr<CTask>>& taskList, __int32 taskId, bool ifChoke)
{
    for (auto itTask = taskList.begin(); itTask != taskList.end(); ++itTask)
    {
        if ((*itTask)->GetTaskId() == taskId)
        {
            (*itTask)->StopTask(ifChoke);
        }
    }
}

void CTaskThread::StopAllTask()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    StopAllTaskUnlock();
}

void CTaskThread::GetWaitTaskCount(std::map<__int32, __int32>& taskCountMap)
{
    taskCountMap.clear();
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        for (auto itTaskList = m_taskMap.begin(); itTaskList != m_taskMap.end(); ++itTaskList)
        {
            taskCountMap[itTaskList->first] = itTaskList->second.size();
        }
    }
}