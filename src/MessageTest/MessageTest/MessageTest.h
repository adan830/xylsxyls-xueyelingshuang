
// MessageTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMessageTestApp:
// �йش����ʵ�֣������ MessageTest.cpp
//

class CMessageTestApp : public CWinApp
{
public:
	CMessageTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMessageTestApp theApp;
