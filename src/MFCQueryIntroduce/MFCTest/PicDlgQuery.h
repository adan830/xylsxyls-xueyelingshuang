#pragma once
#include "resource.h"
#include <string>
#include "resource.h"
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
    bool init(string picture);
public:
    HBITMAP picHBITMAP;
    string picture;
    int width;
    int height;
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
};
