#pragma once
#include "afxwin.h"
#include "CTCPClient.h"


// CChatDlg �Ի���

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChatDlg();

// �Ի�������
	enum { IDD = IDD_CHATDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTCPClient* pClient;
	CEdit m_Show;
	CEdit m_Text;
	afx_msg void OnBnClickedButton1();
	void OnCancel();
	CString strUser; //�Լ�
	CString strChatUser; //����
};
