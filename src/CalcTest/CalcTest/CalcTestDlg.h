
// CalcTestDlg.h : ͷ�ļ�
//

#pragma once
#include "CGetPath/CGetPathAPI.h"
#include "IntDateTime/IntDateTimeAPI.h"

// CCalcTestDlg �Ի���
class CCalcTestDlg : public CDialogEx
{
// ����
public:
	CCalcTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

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
    IntDateTime editTime;
	afx_msg void OnBnClickedButton1();
    string fileName = "calc.data";
    string fileNameBk = "calcbk.data";
    string myFileName = "mycalc.data";
    string myFileNameBk = "mycalcbk.data";
    string curPath = CGetPath::GetCurrentExePath();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
};
