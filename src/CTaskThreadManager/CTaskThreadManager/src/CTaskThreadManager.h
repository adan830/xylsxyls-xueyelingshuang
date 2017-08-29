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

    bool Init(__int32 threadId);

    void Uninit(__int32 threadId);

    void UninitAll();

    /* ������ȡ���̲߳���ָ�룬��Ҫ���ñ����ָ�룬���򼴱��߳�ֹͣҲ�����ͷ���Դ
    */
    std::shared_ptr<CTaskThread> GetThreadInterface(__int32 threadId);

private:

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

    std::map<__int32, std::shared_ptr<CTaskThread>> m_spThreadMap;

#ifdef _MSC_VER
#pragma warning(pop)
#endif
};