
// MFCTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Manager.h"

// CMFCTestDlg �Ի���
class CMFCTestDlg : public CDialogEx
{
// ����
public:
	CMFCTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCTEST_DIALOG };

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
	afx_msg LRESULT OnSetPerson(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnShowPerson(WPARAM wparam, LPARAM lparam);
	CEdit name;
	CComboBox year;
	CComboBox month;
	CComboBox day;
	CComboBox sex;
	CComboBox marriage;
	CComboBox education;
	CEdit jobName;
	CComboBox jobNature;
	CEdit salary;
	CComboBox fatherJob;
	CComboBox fatherPension;
	CComboBox motherJob;
	CComboBox motherPension;
	CString picture1;
	CString picture2;
	CString picture3;
	CEdit introduce;
	CButton check;

	CComboBox tall;
	CComboBox weight;
	CEdit mobile;
	CEdit qq;
	CEdit weChat;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton6();
    CButton picture1show;
    CButton picture2show;
    CButton picture3show;

    void ShowPicture(const CString& picture);
    afx_msg void OnBnClickedButton7();
    afx_msg void OnBnClickedButton8();
	CComboBox house;
	CComboBox car;
	CEdit household;
	CComboBox houseAttri;
	CEdit houseAddr;
};
