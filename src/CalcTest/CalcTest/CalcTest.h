
// CalcTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCalcTestApp:
// �йش����ʵ�֣������ CalcTest.cpp
//

class CCalcTestApp : public CWinApp
{
public:
	CCalcTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCalcTestApp theApp;