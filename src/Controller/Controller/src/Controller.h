#pragma once
#include "Obstacles.h"
#include "ControllerMacro.h"
#include <map>
#include <vector>
using namespace std;

//ң�����������ϰ���״̬
class ControllerAPI Controller{
    friend class Obstacles;
public:
    //ң����һ������������������ϰ���ȫ��ʧЧ�����ǲ����ͷ��ϰ����ڴ棬�ϰ���תΪҰ��״̬
    ~Controller();
    //��Ұ��״̬�ϰ����ڴ�ȫ���ͷ�
    static void ReleaseOutObstacles();
public:
    //���ɣ���һ���������ϰ�����ţ�������������е��ϰ�������򷵻ؿգ�Ĭ������
    Obstacles* CreateObstacles(int num);
    //���ɣ�ǰ�水��strControlִ�У����治����
    Obstacles* CreateObstacles(int num, string strControl);
    //���ɣ�����ifChoke�ж�һֱ��������һֱ������
    Obstacles* CreateObstacles(int num, bool ifChoke);
    //����
    Obstacles* CreateObstacles(int num, string strControl, bool ifChoke);
    //�ͷţ�����ң�������������ϰ����ͷ�
    void ReleaseObstacles();
    //�����ϰ���Ϊ�������˺���������
    void SetChoke(int num);
    //�����ϰ���Ϊ���������˺���������
    void SetUnChoke(int num);
    //�����ϰ���Ϊ�������˺������������ٴ����е��ϰ�������λ��ʱ��ǰ��������ʱ����������
    void ChokeSetChoke(int num);
    //�����ϰ���Ϊ���������˺������������ٴ����е��ϰ�������λ��ʱ��������
    void ChokeSetUnChoke(int num);
    //�����������ٴ�ִ�е��ϰ��������ı��ϰ���״̬
    void ChokeToControl(int num);
    //�������ļ���
    void SetTempControl(int num, string nextControl);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    map<int, Obstacles*> mapObstacles;
    static vector<Obstacles*> vecOutObstacles;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};