
// MFCQueryIntroduce.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// CMFCQueryIntroduceApp:
// �йش����ʵ�֣������ MFCQueryIntroduce.cpp
//

class CMFCQueryIntroduceApp : public CWinApp
{
public:
	CMFCQueryIntroduceApp();

// ��д
public:
	virtual BOOL InitInstance();
    ULONG_PTR m_gdiplusToken;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCQueryIntroduceApp theApp;