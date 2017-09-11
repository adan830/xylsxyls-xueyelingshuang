#include "CTaskThread.h"
#include <assert.h>
#include <windows.h>

CTaskThread::CTaskThread(int32_t threadId) :
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
	m_waitEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    return true;
}

void CTaskThread::DestroyThread()
{
    SetExitSignal();
    WaitForExit();
}

void CTaskThread::SetExitSignal()
{
    m_hasExitSignal = true;
    //����������źž������ѵ�ǰ����ֹͣ
    if (m_spCurTask != nullptr)
    {
        m_spCurTask->StopTask();
    }
}

void CTaskThread::WaitForExit()
{
    //����߳���������
    if (m_spWorkThread != NULL)
    {
        ::SetEvent(m_waitEvent);
        m_spWorkThread->join();
        m_spWorkThread.reset(NULL);
		::CloseHandle(m_waitEvent);
    }
}

void CTaskThread::PostTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel)
{
    if (spTask == NULL || taskLevel < 1 || m_hasExitSignal)
    {
        return;
    }
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_hasExitSignal)
    {
        return;
    }
	::SetEvent(m_waitEvent);
    m_taskMap[taskLevel].push_back(spTask);
    //��������������ȼ����ڵ�ǰ������ǰ����ֹͣ
    if (m_spCurTask != NULL && taskLevel > m_curTaskLevel)
    {
        //���������������Ǳ�������������������Ӵ������п��Ƿ�ֹ��ǰ����û���ü��˳�������˶�����ȼ����ߵ�����
        if (m_spCurTaskBk != NULL && m_spCurTask->ReExecute())
        {
            m_taskMap[m_curTaskLevel].push_front(m_spCurTaskBk);
            m_spCurTaskBk = NULL;
        }
        m_spCurTask->StopTask();
    }
}

void CTaskThread::SendTask(const std::shared_ptr<CTask>& spTask, int32_t taskLevel)
{
    if (spTask == NULL || taskLevel < 1 || m_hasExitSignal)
    {
        return;
    }

	HANDLE waitForSend = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	spTask->SetWaitForSendHandle(waitForSend);
    PostTask(spTask, taskLevel);
    
    bool inWhile = true;
    while (inWhile)
    {
        if (spTask.use_count() == 1)
        {
            break;
        }
        ::WaitForSingleObject(waitForSend, 50);
    }
	::CloseHandle(waitForSend);
	spTask->SetWaitForSendHandle(nullptr);
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
                m_spCurTask->StopTask();
            }
            std::unique_lock<std::mutex> lock(m_mutex);
            m_taskMap.clear();
        }
        //�����ǰ������
        if (m_spCurTask != NULL)
        {
            m_spCurTask->DoTask();
			HANDLE waitForSend = m_spCurTask->GetWaitForSendHandle();
			if (waitForSend != nullptr)
			{
				::SetEvent(waitForSend);
			}
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
			::WaitForSingleObject(m_waitEvent, INFINITE);
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
            (*itTask)->StopTask();
        }
    }
    //����л�δִ����ϵ�����
    if (m_spCurTask != NULL)
    {
        m_spCurTask->StopTask();
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
		::ResetEvent(m_waitEvent);
    }
}

void CTaskThread::StopTask(int32_t taskId, int32_t taskLevel)
{
    if (taskLevel != 0)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        auto itListTask = m_taskMap.find(taskLevel);
        if (itListTask != m_taskMap.end())
        {
            StopTaskInList(itListTask->second, taskId);
        }
    }
    else
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        for (auto itListTask = m_taskMap.begin(); itListTask != m_taskMap.end(); ++itListTask)
        {
            StopTaskInList(itListTask->second, taskId);
        }
    }
}

void CTaskThread::StopTaskInList(const std::list<std::shared_ptr<CTask>>& taskList, int32_t taskId)
{
    for (auto itTask = taskList.begin(); itTask != taskList.end(); ++itTask)
    {
        if ((*itTask)->GetTaskId() == taskId)
        {
            (*itTask)->StopTask();
        }
    }
}

void CTaskThread::StopAllTask()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    StopAllTaskUnlock();
}

void CTaskThread::GetWaitTaskCount(std::map<int32_t, int32_t>& taskCountMap)
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

int32_t CTaskThread::GetCurTaskLevel()
{
	return m_curTaskLevel;
}