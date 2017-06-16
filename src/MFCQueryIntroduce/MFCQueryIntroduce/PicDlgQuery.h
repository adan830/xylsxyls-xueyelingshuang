#pragma once
#include "resource.h"
#include <string>
#include <vector>
#include "resource.h"
#include <afxdialogex.h>
#include "Person.h"
#include "afxwin.h"
using namespace std;

// CPicDlg �Ի���

class CPicControl;
class CPicDlgQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CPicDlgQuery)

public:
	CPicDlgQuery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPicDlgQuery();

// �Ի�������
	enum { IDD = IDD_DIALOGPIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
public:
    void init(const vector<Person>& vecPerson);
public:
    virtual BOOL OnInitDialog();
    void ChangeText(int IDC, string text);
    void ShowPerson(int num);
    vector<Person> vecPerson;
    CPicControl* m_pic;
    CButton m_picPre;
    CButton m_picNext;
    CButton m_personPre;
    CButton m_personNext;
    int m_currentPerson;
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButtonpic();
    CButton m_picRc;
};
