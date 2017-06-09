
// MessageTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessageTest.h"
#include "MessageTestDlg.h"
#include "afxdialogex.h"
#include <string>
#include <afxwin.h>
#include "resource.h"
#include <fstream>
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
    DDX_Control(pDX, IDC_BUTTON3, m_fileBtn);
}

BEGIN_MESSAGE_MAP(CMessageTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMessageTestDlg::OnBnClickedButton1)
    ON_WM_COPYDATA()
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON2, &CMessageTestDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMessageTestDlg::OnBnClickedButton3)
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
    m_event = new CEvent(0, 0);
    threadWork = new thread(std::bind(&CMessageTestDlg::WorkThread, this));
    SetTimer(10000, 100, NULL);

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

static bool SendToMessageTest(const char* fmt, ...)
{
    std::string str;
    va_list args = NULL;
    va_start(args, fmt);
    int size = _vscprintf(fmt, args);
    str.resize(size);
    vsprintf_s(&str[0], size + 1, fmt, args);
    va_end(args);
#ifdef _UNICODE
    HWND receiveWindow = ::FindWindow(NULL, L"MessageTest");
#else
    HWND receiveWindow = ::FindWindow(NULL, "MessageTest");
#endif
    if (receiveWindow == NULL) return false;
    COPYDATASTRUCT copyData = { 0 };
    copyData.lpData = (PVOID)str.c_str();
    copyData.cbData = (DWORD)str.length();
    return ::SendMessage(receiveWindow, WM_COPYDATA, (WPARAM)NULL/*m_hWnd*/, (LPARAM)&copyData) == 1;
}

void CMessageTestDlg::OnBnClickedButton1()
{
    windowtext.Empty();
    m_edit.SetWindowText(CString());
    mu.lock();
    int size = listCopyData.size();
    mu.unlock();
    lines = 0;
    CString strSize;
    strSize.Format(L"��ǰ������ʣ��չʾ����%d", size);
    ::SendMessage(GetDlgItem(IDC_STATIC_LIST)->m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPSTR)(LPCTSTR)strSize);
    strSize.Format(L"��ǰ��Ļ������%d", 0);
    ::SendMessage(GetDlgItem(IDC_STATIC_SCREEN)->m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPSTR)(LPCTSTR)strSize);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

BOOL CMessageTestDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    //pWndΪ���ͷ�����

    int dataSize = pCopyDataStruct->cbData;
    int allocSize = dataSize + 1;
    if (curDataSize < allocSize)
    {
        free(szData);
        szData = (char*)malloc(allocSize);
        curDataSize = allocSize;
    }
    memcpy(szData, (char *)pCopyDataStruct->lpData, dataSize);
    szData[dataSize] = 0;
    mu.lock();
    listCopyData.push_back(szData);
    //m_event->SetEvent();
    mu.unlock();

    return true;
    return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

void CMessageTestDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (bFile == true && bShowString == true)
    {
        bShowString = false;
        mu.lock();
        int size = listCopyData.size();
        mu.unlock();
        CString strSize;
        strSize.Format(L"��ǰ������ʣ��չʾ����%d", size);
        ::SendMessage(GetDlgItem(IDC_STATIC_LIST)->m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPSTR)(LPCTSTR)strSize);
        return;
    }
    if (bShowString == true)
    {
        bShowString = false;
        windowtext = CString(showString.c_str()) + windowtext;
        //int showstringlength = showString.length();
        //�ȴ������ַ�������
        //controller.ChokeSetChoke(stringover
        //�������ѭ��ʱ�м���ʧ�ܣ������´ν���ʱ����ϴ�δ�ɹ���ʾ��������ʾ
        m_edit.SetWindowText(windowtext);
        showString.clear();
        mu.lock();
        int size = listCopyData.size();
        mu.unlock();
        //controller.SetUnChoke(stringover);
        CString strSize;
        strSize.Format(L"��ǰ������ʣ��չʾ����%d", size);
        ::SendMessage(GetDlgItem(IDC_STATIC_LIST)->m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPSTR)(LPCTSTR)strSize);
        strSize.Format(L"��ǰ��Ļ������%d", lines);
        ::SendMessage(GetDlgItem(IDC_STATIC_SCREEN)->m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPSTR)(LPCTSTR)strSize);
    }
    CDialogEx::OnTimer(nIDEvent);
}

void CMessageTestDlg::WorkThread()
{
    while (bWorkThread)
    {
        //Sleep(1);
        mu.lock();
        bool isEmpty = listCopyData.empty();
        mu.unlock();
        if (isEmpty == true)
        {
            Sleep(1);
            //::WaitForSingleObject(m_event->m_hObject, INFINITE);
            continue;
        }
        bShowString = true;
        mu.lock();
        auto& it = listCopyData.begin();
        string oneData = *(it);
        listCopyData.erase(it);
        mu.unlock();
        if (bFile == true)
        {
            *((ofstream*)file) << oneData << endl;
        }
        else
        {
            showString.insert(0, oneData + "\r\n");
            ++lines;
        }
    }
}

void CMessageTestDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    bWorkThread = false;
    threadWork->join();
    controller.ReleaseObstacles();
    delete m_event;
    // TODO:  �ڴ˴������Ϣ����������
}


void CMessageTestDlg::OnBnClickedButton2()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    m_edit.GetWindowText(windowtext);
    mu.lock();
    int size = listCopyData.size();
    mu.unlock();
    lines = windowtext.Replace(L"\r\n", L"\r\n");
    //controller.SetUnChoke(stringover);
    CString strSize;
    strSize.Format(L"��ǰ������ʣ��չʾ����%d", size);
    ::SendMessage(GetDlgItem(IDC_STATIC_LIST)->m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPSTR)(LPCTSTR)strSize);
    strSize.Format(L"��ǰ��Ļ������%d", lines);
    ::SendMessage(GetDlgItem(IDC_STATIC_SCREEN)->m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPSTR)(LPCTSTR)strSize);
}


void CMessageTestDlg::OnBnClickedButton3()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    bFile = !bFile;
    if (file == nullptr)
    {
        file = ::new ofstream(L"MessageTestFile.txt", ios::app);
    }
    if (bFile == false)
    {
        if (file != nullptr)
        {
            delete (ofstream*)file;
        }
        file = nullptr;
        m_fileBtn.SetWindowText(L"תΪд���ļ�");
    }
    else
    {
        m_fileBtn.SetWindowText(L"תΪд����Ļ");
    }
}
