
// MFCTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CMyEdit.h"
#include <vector>
#include "resource.h"
#include <atomic>
#include <mutex>
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
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();

public:
    enum
    {
        GBK,
        Unicode,
        UTF8
    };

public:
    //?�Ѽ�������Ϣ
    void GetInfoFromWindow();

    //?ִ������
    void Search();

    //?չʾ�������
    void ShowSearchResult();

	afx_msg void OnDestroy();
private:
    //?�Ƿ����ų�����ĺ�׺
    bool IsOutFormat(const string& path, const vector<string>& vecOutFormat);
    //?��ȡ�༭���ַ�����string
    string GetCEditString(const CEdit& m_edit);
    //?��ȡ���������ַ�����int
    int GetCComboBoxInt(const CComboBox& m_combo);
    //?��ȡ��ѡ�����ݵ�bool
    bool GetCButtonBool(const CButton& m_edit);
private:
    CEdit m_path;
    CEdit m_outFormat;
    CEdit m_text;
    CMyEdit m_find;
    string m_strPath;
    string m_strOutFormat;
    
    CButton m_case;
    CButton m_btnFind;
    CButton m_fileNameCheck;
    
    string strKey;
    bool bBigSmallCheck;
    
    CButton m_suffixCheck;
    
    CComboBox m_chara;
	int m_cpuCount = 0;
    
public:
	atomic<bool> bFileNameCheck;
	atomic<bool> bsuffixCheck;
	int showChara;
	string m_strFind;
	string strLineFlag;
	atomic<bool>* szEnd = nullptr;
	std::mutex m_mutex;
};
