
// OneKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneKey.h"
#include "OneKeyDlg.h"
#include "afxdialogex.h"
#include "CHook/CHookAPI.h"
#include "D:\\SendToMessageTest.h"
#include "CStopWatch/CStopWatchAPI.h"
#include "CStringManager/CStringManagerAPI.h"
#include "CKeyBoard/CKeyboardAPI.h"
#include "CMouse/CMouseAPI.h"
#include "CTaskThreadManager/CTaskThreadManagerAPI.h"

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


// COneKeyDlg �Ի���



COneKeyDlg::COneKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COneKeyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COneKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COneKeyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &COneKeyDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

CStopWatch stopWatch;

class CSendTask : public CTask
{
public:
	void DoTask()
	{
		CKeyboard::InputString("d", 0);
		CKeyboard::KeyDown('N');
		CKeyboard::KeyDown('Q');
		CKeyboard::KeyUp('N');
		CKeyboard::KeyUp('Q');
		Sleep(300);
		CKeyboard::InputString("r", 0);
		Sleep(40);
		CMouse::RightManyClick(2, 100);
		CKeyboard::InputString("q", 0);
		CMouse::RightClick(40);
		CKeyboard::InputString("q", 0);
		CMouse::RightClick(150);
		CMouse::RightManyClick(2, 100);
		Sleep(500);
		CKeyboard::InputString("q", 0);
		CMouse::RightManyClick(6, 200);
	}
};

bool wDown = false;
bool eDown = false;

LRESULT WINAPI HookFun(int nCode, WPARAM wParam, LPARAM lParam)
{
	// �������������Ϣ�������
	const DWORD& vkCode = CHook::GetVkCode(lParam);
	if (CHook::IsKeyDown(wParam))
	{
		if (vkCode == 'W')
		{
			wDown = true;
		}
		else if (vkCode == 'E')
		{
			eDown = true;
		}

		if (wDown && eDown && stopWatch.GetWatchTime() > 500)
		{
			stopWatch.SetWatchTime(0);
			std::shared_ptr<CSendTask> spTask;
			spTask.reset(new CSendTask);
			auto& taskThread = CTaskThreadManager::Instance().GetThreadInterface(1);
			if (taskThread != nullptr)
			{
				taskThread->PostTask(spTask, 1);
			}
		}
	}
	else if (CHook::IsKeyUp(wParam))
	{
		if (vkCode == 'W')
		{
			wDown = false;
		}
		else if (vkCode == 'E')
		{
			eDown = false;
		}
	}

	// ���¼����ݵ���һ������
	return CallNextHookEx(CHook::s_hHook, nCode, wParam, lParam);
}

// COneKeyDlg ��Ϣ�������

BOOL COneKeyDlg::OnInitDialog()
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

	CTaskThreadManager::Instance().Init(1);
	CHook::Init(WH_KEYBOARD_LL, HookFun);
	//CHook::Init(WH_KEYBOARD_LL, HookFun);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COneKeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COneKeyDlg::OnPaint()
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
HCURSOR COneKeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COneKeyDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void COneKeyDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	CHook::Uninit();
	CTaskThreadManager::Instance().UninitAll();
}
