
// FundInvestDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include <map>
#include <vector>
#include "IntDateTime/IntDateTimeAPI.h"
#include "DataNeuron.h"
#include "CSystem/CSystemAPI.h"

class CDrawDlg;
// CFundInvestDlg �Ի���
class CFundInvestDlg : public CDialogEx
{
// ����
public:
	CFundInvestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FundInvest_DIALOG };

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
	afx_msg void OnBnClickedButton2();

private:
	void LoadFund();
	DataNeuron* GetNeuron(const std::string& fundName, const std::string& time);

private:
	std::string m_fundPath = CSystem::GetEnvironment("xueyelingshuang") + "data\\Fund\\";
	std::string m_fundName = "110022";
	bool m_isOpenBuy = true;
	bool m_isOpenSell = true;

	std::map<std::string, std::map<IntDateTime, DataNeuron>> m_mapDataNeuron;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();

	void Draw(const std::map<double,double>& mapData);

	CDrawDlg * drawDlg = NULL;
	afx_msg void OnBnClickedButton12();

	double WeekBidSell(const std::string& beginTime,
					   const std::string& endTime,
					   double bid,
					   double sell);
};
