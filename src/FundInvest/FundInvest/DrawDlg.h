#pragma once


// CDrawDlg �Ի���
#include "resource.h"

class CDrawDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDrawDlg)

public:
	CDrawDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
