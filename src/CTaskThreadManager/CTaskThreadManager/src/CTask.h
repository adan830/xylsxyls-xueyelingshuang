#pragma once
#include "CTaskThreadManagerMacro.h"
#include <stdint.h>

//���Ҫ�������ִ�н���������ڴ���task��ʱ��Ͱѻ�ý����ָ�봫��task�ڲ����̰߳�ȫ�����ⲿά��
class CTaskThreadManagerAPI CTask
{
public:
    CTask(int32_t taskId);

public:
    virtual void DoTask() = 0;
    virtual void StopTask(bool ifChoke) = 0;
    /* ���������ȼ����ߵ����񶥵�ʱ�Ƿ�����
    */
    virtual bool ReExecute() = 0;
    virtual CTask* Clone() = 0;
    virtual bool HasExecuted() = 0;
    int32_t GetTaskId();

private:
    int32_t m_taskId;
};