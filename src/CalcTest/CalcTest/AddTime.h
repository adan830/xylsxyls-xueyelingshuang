#pragma once
#include "afxwin.h"
#include "IntDateTime/IntDateTimeAPI.h"

// CAddTime �Ի���

class CAddTime : public CDialogEx
{
	DECLARE_DYNAMIC(CAddTime)

public:
	CAddTime(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddTime();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CEdit m_time;
    afx_msg void OnBnClickedButton1();
    IntDateTime* editTime;
    void SetEditTime(IntDateTime* editTime);
};
