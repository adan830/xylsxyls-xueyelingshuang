
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
    enum
    {
        GBK,
        Unicode,
        UTF8
    };

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

    //?���ղ�ͬ�����ʽ����һ�в����
    //? oneLine [in] ��������һ�У�gbk��ʽ
    //? path [in] ���ļ���·��
    //? key [in] �����Ĺؼ���
    //? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
    //? line [in] �к�
    //? addString [out] Ҫ��ӵ��ַ���
    //? format [in] �������ַ�����ʲô��ʽ��
    //? �����ҵ���λ�ã�0��ʼ
    int FindAdd(const string& oneLine, const string& path, const string& key, bool& bAddFileName, int line, string& addString, const string& format);

private:
    //?�Ƿ����ų�����ĺ�׺
    bool IsOutFormat(const string& path, const vector<string>& vecOutFormat);
    //?��ȡ�༭���ַ�����string
    string GetCEditString(const CEdit& m_edit);
    //?��ȡ���������ַ�����int
    int GetCComboBoxInt(const CComboBox& m_combo);
    //?��ȡ��ѡ�����ݵ�bool
    bool GetCButtonBool(const CButton& m_edit);
    //?��ȡutf-8��ÿ��ƫ��λ��
    //? line [in] �кţ���0��ʼ
    //? oneLine [in] ÿ������
    int GetUtf8Offset(int line, const string& oneLine);
    //?��ȡunicode��ÿ��ƫ��λ��
    //? line [in] �кţ���0��ʼ
    //? oneLine [in][out] ÿ�����ݣ�����stringĩβ���һ��\0
    int GetUnicodeOffset(int line, string& oneLine);
    //?�ԱȲ�����ַ���
    //? addOffset [in] ��Ҫ��ӵ��ַ����йؼ���ƫ����
    //? addString [in] ��Ҫ��ӵ��ַ���
    //? showOffset [in] ��Ҫչʾ���ַ�����Ӧ���ҵ��ؼ��ʵ�ƫ����
    //? path [in] ���ļ���·��
    //? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
    //? ifCurAdd [in][out] ��ǰ�Ƿ��Ѿ����
    void CompareShowAdd(int addOffset, const string& addString, int showOffset, const string& path, bool& bAddFileName, bool& ifCurAdd);

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
    CComboBox m_chara;
    int showChara;
public:
    
};
