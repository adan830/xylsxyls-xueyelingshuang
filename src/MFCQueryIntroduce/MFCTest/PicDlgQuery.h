#pragma once
#include "resource.h"
#include <string>
#include <vector>
#include "resource.h"
#include <afxdialogex.h>
#include "Person.h"
using namespace std;

// CPicDlg �Ի���

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
    vector<Person> vecPerson;
};
