#pragma once
#include <windows.h>
#include <string>
#include "CSystemMacro.h"
using namespace std;

class CSystemAPI CSystem{
public:
	//?ʵ��CPU��Ƶ
	static double GetCPUSpeedGHz();
	//?��ȡϵͳ���������δ�С
	static RECT GetTaskbarRect();
	//?��ȡ��Ļ�ֱ���
	static RECT GetWindowResolution();
	//?��ȡȥ����������������ʱ���������������Ļ�߶�
	static int GetVisibleHeight();
	//?��ƽ̨Sleep������
	static void Sleep(long long milliseconds);
	//?����UUID������1��ʾ��-����0��ʾ����
	static string uuid(int flag = 1);

};