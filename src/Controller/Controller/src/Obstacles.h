#pragma once
#include <string>
#include <mutex>
#include <atomic>
#include "ControllerMacro.h"
using namespace std;

//�ϰ������ó���ͨ����ͨ��
class ControllerAPI Obstacles{
    friend class Controller;
private:
    Obstacles(){}
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
    atomic<int> status = outside;
    mutex mutex;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

    enum{
        outside,
        insideChoke,
        insideUnChoke
    };
private:
    //?Ĭ�ϲ�������1Ϊ������"111"��ʾǰ3�ξ�����Ҫ֪ͨ�������
    static Obstacles* CreateApi(string strControl, bool ifChoke = false);
public:
    void Set();
};