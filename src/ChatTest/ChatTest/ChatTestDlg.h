
// ChatTestDlg.h : ͷ�ļ�
//

#pragma once
#include "CTCPClient.h"
#include "afxwin.h"
#include "resource.h"


// CChatTestDlg �Ի���
class CChatTestDlg : public CDialogEx
{
// ����
public:
	CChatTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	CEdit m_User;
	CEdit m_PassWord;
	afx_msg void OnBnClickedButton2();
	LPARAM OpenMainDlg(WPARAM wparam,LPARAM lparam);
};

extern CTCPClient client;

extern CChatTestDlg* pChatTestDlg;