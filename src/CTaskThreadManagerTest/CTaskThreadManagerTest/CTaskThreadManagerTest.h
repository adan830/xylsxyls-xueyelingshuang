
// CTaskThreadManagerTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCTaskThreadManagerTestApp:
// �йش����ʵ�֣������ CTaskThreadManagerTest.cpp
//

class CCTaskThreadManagerTestApp : public CWinApp
{
public:
	CCTaskThreadManagerTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCTaskThreadManagerTestApp theApp;