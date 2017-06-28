
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
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();

public:
    //? ���ļ�����
    //? path [in] ���ļ���·��
    //? key [in] �����Ĺؼ���
    //? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
    void OpenFileFind(const string& path, const string& key, bool& bAddFileName);

    //? �����ļ���
    //? path [in] ���ļ���·��
    //? key [in] �����Ĺؼ���
    //? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
    void FindFromFileName(const string& path, const string& key, bool& bAddFileName);

    //?����·��һ�β���
    void FindFromPath(const string& path, const string& key);

    //?��������
    //? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
    void FindEnd(bool& bAddFileName);

    //?�Ѽ�������Ϣ
    void GetInfoFromWindow();

    //?ִ������
    void Search();

    //?չʾ�������
    void ShowSearchResult();

private:
    //?�Ƿ����ų�����ĺ�׺
    bool IsOutFormat(const string& path, const vector<string>& vecOutFormat);
    //?��ȡ�༭���ַ�����string
    string GetCEditString(const CEdit& m_edit);
    //?��ȡ��ѡ�����ݵ�bool
    bool GetCButtonBool(const CButton& m_edit);

private:
    CEdit m_path;
    CEdit m_outFormat;
    CEdit m_text;
    CMyEdit m_find;
    string m_strPath;
    string m_strOutFormat;
    string m_strFind;
    CButton m_case;
    CButton m_btnFind;
    CButton m_fileNameCheck;
    string strLineFlag;
    string strKey;
    bool bBigSmallCheck;
    bool bFileNameCheck;
    CButton m_suffixCheck;
    bool bsuffixCheck;
};
