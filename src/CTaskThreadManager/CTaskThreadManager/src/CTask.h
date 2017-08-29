#pragma once
#include "CTaskThreadManagerMacro.h"

//���Ҫ�������ִ�н���������ڴ���task��ʱ��Ͱѻ�ý����ָ�봫��task�ڲ����̰߳�ȫ�����ⲿά��
class CTaskThreadManagerAPI CTask
{
public:
    CTask(__int32 taskId);

public:
    virtual void DoTask() = 0;
    virtual void StopTask(bool ifChoke) = 0;
    /* ���������ȼ����ߵ����񶥵�ʱ�Ƿ�����
    */
    virtual bool ReExecute() = 0;
    virtual CTask* Clone() = 0;
    virtual bool HasExecuted() = 0;
    __int32 GetTaskId();

private:
    __int32 m_taskId;
};