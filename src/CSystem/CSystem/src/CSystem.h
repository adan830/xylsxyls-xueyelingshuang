#pragma once
#include <afxwin.h>
#include "CSystemMacro.h"

class CSystemAPI CSystem{
public:
	//ʵ��CPU��Ƶ
	double GetCPUSpeedGHz();
	//��ȡϵͳ���������δ�С
	CRect GetTaskbarRect();
	//��ȡ��Ļ�ֱ���
	CRect GetWindowResolution();
	//��ȡȥ����������������ʱ���������������Ļ�߶�
	int GetVisibleHeight();
};