
// FundInvest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFundInvestApp:
// �йش����ʵ�֣������ FundInvest.cpp
//

class CFundInvestApp : public CWinApp
{
public:
	CFundInvestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFundInvestApp theApp;