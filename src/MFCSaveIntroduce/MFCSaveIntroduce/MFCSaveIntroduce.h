
// MFCSaveIntroduce.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCSaveIntroduceApp:
// �йش����ʵ�֣������ MFCSaveIntroduce.cpp
//

class CMFCSaveIntroduceApp : public CWinApp
{
public:
	CMFCSaveIntroduceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCSaveIntroduceApp theApp;