#pragma once
#include <windows.h>
#include "CSystemMacro.h"

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
};