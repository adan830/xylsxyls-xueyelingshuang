
// OneKey.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COneKeyApp:
// �йش����ʵ�֣������ OneKey.cpp
//

class COneKeyApp : public CWinApp
{
public:
	COneKeyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COneKeyApp theApp;