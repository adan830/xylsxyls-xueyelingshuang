#include <assert.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__GNUC__)
    #include <pthread.h>
#else
    #error use must add yourself code.
#endif

#ifndef __PTMUTEXLOCK_H__
#define __PTMUTEXLOCK_H__

class ptMutexLock  // ����һ���̻߳�����
{
public:

#if defined(__GNUC__)
    ptMutexLock(pthread_mutexattr_t* muterattr=NULL)   // ��ʼ��һ����
#else
    ptMutexLock()   // ��ʼ��һ����
#endif
    {
    #if defined(_WIN32)
        InitializeCriticalSection(&mutex);
    #elif defined(__GNUC__)
        pthread_mutex_init(&mutex, muterattr);
    #endif
    }

    virtual ~ptMutexLock()      // ɾ����
    {
    #if defined(_WIN32)
        DeleteCriticalSection(&mutex);
    #elif defined(__GNUC__)
        pthread_mutex_destroy(&mutex);
    #endif
    }

    inline void Lock()      // ����
    {
    #if defined(_WIN32)
        EnterCriticalSection(&mutex);
    #elif defined(__GNUC__)
        pthread_mutex_lock(&mutex);
    #endif
    }

    inline void unLock()    // ����
    {
    #if defined(_WIN32)
        LeaveCriticalSection(&mutex);
    #elif defined(__GNUC__)
        pthread_mutex_unlock(&mutex);
    #endif
    }

#if !defined(_WIN32) || (_WIN32_WINNT >= 0x0400)
    inline bool tryLock()    // ��ͼ������������
    {
    #if defined(_WIN32) 
        return (!!TryEnterCriticalSection(&mutex)); // 95/98��֧��
    #elif defined(__GNUC__)
        return (!!(pthread_mutex_trylock(&mutex)==0));
    #endif
    }
#endif

private:
#if defined(_WIN32)
    CRITICAL_SECTION mutex;
#elif defined(__GNUC__)
    pthread_mutex_t mutex;
#endif
};

#endif


#ifndef __PTMUTEXLOCKADP_H__
#define __PTMUTEXLOCKADP_H__

class ptMutexLockAdp   // �Ի�������һ���򵥵İ�װ,��֧�ֶ༶����
{
public:
    ptMutexLockAdp(ptMutexLock* mutex, bool bInitialLock=true)
    {
        assert(mutex != NULL);
        pMutex = mutex;
        if(bInitialLock) 
        {
            islock = false;
            this->Lock();
        }   
    }

    virtual ~ptMutexLockAdp()
    {
        this->unLock();
    }

    inline void Lock()
    {
        if(!islock)
        {
            pMutex->Lock();
            islock = true;
        }
    }

    inline void unLock()
    {
        if(islock)
        {
            pMutex->unLock();
            islock = false;
        }
    }

#if !defined(_WIN32) || (_WIN32_WINNT >= 0x0400)
    inline bool tryLock()
    {
        islock = islock ? true : pMutex->tryLock();
        return islock;
    }
#endif

    inline bool isLocked() { return islock; }

private:
    ptMutexLock* pMutex;
    bool islock;
};

#endif

