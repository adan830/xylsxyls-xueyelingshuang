
// MFCTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CMyEdit.h"
#include <vector>
using namespace std;

// CMFCTestDlg �Ի���
class CFindTextDlg : public CDialogEx
{
// ����
public:
	CFindTextDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
    enum { IDD = IDD_FINDTEXT_DIALOG };

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
    CEdit m_path;
    CEdit m_outFormat;
    CEdit m_text;
    CMyEdit m_find;
    afx_msg void OnBnClickedButton2();
    string m_strPath;
    string m_strOutFormat;
    string m_strFind;
    CButton m_case;
    bool IsOutFormat(const string& path, const vector<string>& vecOutFormat);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    CButton m_btnFind;
};
