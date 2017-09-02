#pragma once
#include "CTask.h"
#include "CTaskThread.h"
#include <map>
#include <memory>

class CTaskThreadManagerAPI CTaskThreadManager
{
private:
    CTaskThreadManager();
    ~CTaskThreadManager();
public:
    static CTaskThreadManager& Instance();

    bool Init(int32_t threadId);

    void Uninit(int32_t threadId);

    void UninitAll();

    /* ������ȡ���̲߳���ָ�룬��Ҫ���ñ����ָ�룬���򼴱��߳�ֹͣҲ�����ͷ���Դ
    */
    std::shared_ptr<CTaskThread> GetThreadInterface(int32_t threadId);

private:

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

    std::map<int32_t, std::shared_ptr<CTaskThread>> m_spThreadMap;

    /* �̳߳���
    */
    std::mutex m_mutex;

#ifdef _MSC_VER
#pragma warning(pop)
#endif
};