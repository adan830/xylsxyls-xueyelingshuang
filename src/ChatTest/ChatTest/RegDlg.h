#pragma once
#include "afxwin.h"


// CRegDlg �Ի���

class CTCPClient;
extern CTCPClient client;
class CRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegDlg)

public:
	CRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegDlg();

// �Ի�������
	enum { IDD = IDD_REGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	LPARAM Close(WPARAM wparam,LPARAM lparam);

public:
	CTCPClient* pClient;

	CEdit m_NewUser;
	CEdit m_NewPassWordOne;
	CEdit m_NewPassWordTwo;
};

extern CRegDlg* pRegDlg;