
// CivilEngineeringDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCivilEngineeringDlg �Ի���
class CCivilEngineeringDlg : public CDialogEx
{
// ����
public:
	CCivilEngineeringDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CIVILENGINEERING_DIALOG };

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
	CEdit m_BallPositionAndRadius;
	CEdit m_PointPosition;
	CEdit m_PointSpeed;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_x;
	CEdit m_y;
	CEdit m_z;
	CEdit m_biggestx;
	CEdit m_OsmoticCoefficient;
	CEdit m_NowNumber;
};
