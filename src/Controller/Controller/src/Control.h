#pragma once
#include <string>
#include <mutex>
#include <atomic>
#include "ControllerMacro.h"
using namespace std;

class ControllerAPI Control{
public:
    bool ifChoke;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    string strControl;
    atomic<bool> current;
    atomic<int> num;
    string strNextControl;
    atomic<int> numNext;
    mutex mutex;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    
    //?Ĭ�ϲ�������1Ϊ������"111"��ʾǰ3�ξ�����Ҫ֪ͨ�������
    static Control* CreateApi(string strControl, bool ifChoke = false);
    void Set();
};