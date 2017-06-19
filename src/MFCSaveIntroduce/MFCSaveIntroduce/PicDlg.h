#pragma once
#include "resource.h"
#include <string>
using namespace std;

// CPicDlg �Ի���

class CPicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPicDlg)

public:
	CPicDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPicDlg();

// �Ի�������
	enum { IDD = IDD_DIALOGPIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
public:
    bool init(const string& picture);
public:
    HBITMAP picHBITMAP;
    string picture;
    int width;
    int height;
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
};
