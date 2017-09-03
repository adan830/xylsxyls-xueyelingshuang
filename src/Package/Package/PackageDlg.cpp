
// PackageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Package.h"
#include "PackageDlg.h"
#include "afxdialogex.h"
#include "CTaskThreadManager/CTaskThreadManagerAPI.h"
#include "CEncodeDecode/CEncodeDecodeAPI.h"
#include "Ctxt/CtxtAPI.h"
#include "CGetPath/CGetPathAPI.h"
#include "CTaskFactory.h"

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


// CPackageDlg �Ի���



CPackageDlg::CPackageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPackageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPackageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPackageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPackageDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_ENCODE_SUCCESS, &CPackageDlg::OnEncodeSuccess)
	ON_BN_CLICKED(IDC_BUTTON2, &CPackageDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPackageDlg ��Ϣ�������

BOOL CPackageDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPackageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPackageDlg::OnPaint()
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
HCURSOR CPackageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPackageDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::string encodePath = CGetPath::GetCurrentExePath() + "../../../attacklogy/";
	vector<std::string> vecPath = CGetPath::FindFilePath("", encodePath, 3);

	for (auto itPath = vecPath.begin(); itPath != vecPath.end();)
	{
		if (itPath->find(".git") != -1)
		{
			itPath = vecPath.erase(itPath);
			continue;
		}
		else if (itPath->find("README.md") != -1)
		{
			itPath = vecPath.erase(itPath);
			continue;
		}
		else if (itPath->find("AttackData") != -1)
		{
			itPath = vecPath.erase(itPath);
			continue;
		}
		++itPath;
	}

	std::shared_ptr<CTask> spTask;
	int32_t i = -1;
	while (i++ != vecPath.size() - 1)
	{
		spTask.reset(::new CEncodeDecodeTask(1, vecPath[i], (i == vecPath.size() - 1) ? m_hWnd : nullptr, true));
		auto taskThread = CTaskThreadManager::Instance().GetThreadInterface(1);
		taskThread->PostTask(spTask, 1);
	}
}

LRESULT CPackageDlg::OnEncodeSuccess(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("���");
	return 0;
}

void CPackageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	CTaskThreadManager::Instance().Uninit(1);
}


void CPackageDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	std::string encodePath = CGetPath::GetCurrentExePath() + "../../../attacklogy/";
	vector<std::string> vecPath = CGetPath::FindFilePath("", encodePath, 3);

	for (auto itPath = vecPath.begin(); itPath != vecPath.end();)
	{
		if (itPath->find(".git") != -1)
		{
			itPath = vecPath.erase(itPath);
			continue;
		}
		else if (itPath->find("README.md") != -1)
		{
			itPath = vecPath.erase(itPath);
			continue;
		}
		else if (itPath->find("AttackSrc") != -1)
		{
			itPath = vecPath.erase(itPath);
			continue;
		}
		++itPath;
	}

	std::shared_ptr<CTask> spTask;
	int32_t i = -1;
	while (i++ != vecPath.size() - 1)
	{
		spTask.reset(::new CEncodeDecodeTask(1, vecPath[i], (i == vecPath.size() - 1) ? m_hWnd : nullptr, false));
		auto taskThread = CTaskThreadManager::Instance().GetThreadInterface(1);
		taskThread->PostTask(spTask, 1);
	}
}
