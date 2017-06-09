
// MessageTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include "Controller/ControllerAPI.h"
using namespace std;

// CMessageTestDlg �Ի���
class CMessageTestDlg : public CDialogEx
{
// ����
public:
	CMessageTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MessageTest_DIALOG };

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
    enum
    {
        stringover
    };
public:
	afx_msg void OnBnClickedButton1();
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
    CEdit m_edit;
    int current = 0;
    int maxData = 1024;
    int maxSize = 1024;
    vector<string> vecCopyData;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CString windowtext;
    CString strLastText;

    list<string> listCopyData;
    string showString;
    thread* threadWork = nullptr;
    atomic<bool> bWorkThread = 1;
    Controller controller;
    Obstacles* threadObs = controller.CreateObstacles(stringover, false);
    
    char* szData = nullptr;
    int curDataSize = 0;
    atomic<bool> bShowString = false;
    mutex mu;
    CEvent* m_event;
    atomic<int> lines;
    atomic<bool> bFile = false;
    void* file;
    void WorkThread();
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    CButton m_fileBtn;
};
