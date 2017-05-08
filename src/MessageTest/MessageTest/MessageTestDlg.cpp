
// MessageTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessageTest.h"
#include "MessageTestDlg.h"
#include "afxdialogex.h"
#include <string>
#include <afxwin.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMessageTestDlg �Ի���



CMessageTestDlg::CMessageTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMessageTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CMessageTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMessageTestDlg::OnBnClickedButton1)
    ON_WM_COPYDATA()
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CMessageTestDlg ��Ϣ�������

BOOL CMessageTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    SetTimer(10000, 100, NULL);
    int i = -1;
    while (i++ != maxData - 1){
        string str;
        str.resize(maxSize);
        vecCopyData.push_back(str);
    }

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMessageTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMessageTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMessageTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool SendToMessageTest(const char* fmt,...){
    std::string str;
    va_list args = NULL;
    va_start(args, fmt);
    int size = _vscprintf(fmt, args);
    str.resize(size);
    vsprintf_s(&str[0], size + 1, fmt, args);
    va_end(args);
    std::string window = "MessageTest";
    HWND receiveWindow = ::FindWindow(NULL, CString(window.c_str()));
    if (receiveWindow == NULL) return false;
    COPYDATASTRUCT copyData = { 0 };
    copyData.lpData = (PVOID)str.c_str();
    copyData.cbData = str.length();
    return ::SendMessage(receiveWindow, WM_COPYDATA, (WPARAM)NULL/*m_hWnd*/, (LPARAM)&copyData) == 1;
}

void CMessageTestDlg::OnBnClickedButton1()
{
    m_edit.SetWindowText(CString());
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

BOOL CMessageTestDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    //pWndΪ���ͷ�����
    if (current >= maxData){
        AfxMessageBox(L"��������С");
    }

    if (vecCopyData.at(current).length() <= pCopyDataStruct->cbData){
        vecCopyData.at(current).resize(pCopyDataStruct->cbData + 1);
    }
    
    memcpy(&vecCopyData.at(current)[0], (char *)pCopyDataStruct->lpData, pCopyDataStruct->cbData);
    vecCopyData.at(current)[pCopyDataStruct->cbData] = 0;
    current++;

    return true;
    return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

void CMessageTestDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    m_edit.GetWindowText(windowtext);
    string strNew;
    int i = -1;
    while (i++ != current - 1){
        strNew = string(vecCopyData.at(i).c_str()) + "\r\n" + strNew;
    }
    CString strText = CString(strNew.c_str()) + windowtext;
    if (strText != strLastText){
        m_edit.SetWindowText(CString(strNew.c_str()) + windowtext);
        strLastText = strText;
    }
    current = 0;
    CDialogEx::OnTimer(nIDEvent);
}
