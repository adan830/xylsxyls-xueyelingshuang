
// ChatTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatTest.h"
#include "ChatTestDlg.h"
#include "afxdialogex.h"
#include "Cjson/CjsonAPI.h"
#include "RegDlg.h"
#include "MainDlg.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
CChatTestDlg* pChatTestDlg = NULL;

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


// CChatTestDlg �Ի���



CChatTestDlg::CChatTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_User);
	DDX_Control(pDX, IDC_EDIT3, m_PassWord);
}

BEGIN_MESSAGE_MAP(CChatTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CChatTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatTestDlg::OnBnClickedButton2)
	ON_MESSAGE(10000,OpenMainDlg)
END_MESSAGE_MAP()


// CChatTestDlg ��Ϣ�������

BOOL CChatTestDlg::OnInitDialog()
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
	pChatTestDlg = this;
	AfxSocketInit();
	//�����ӷ����������������û�����֪�û�
	BOOL nConnect = client.init("192.168.2.188",3000,2,10240,2,1);
	if(nConnect == 0) AfxMessageBox("������δ����");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatTestDlg::OnPaint()
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
HCURSOR CChatTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CTCPClient client;

//��¼����Ϣ��10000
void CChatTestDlg::OnBnClickedButton1()
{
	CString strUser = "";
	m_User.GetWindowTextA(strUser);
	CString strPassWord = "";
	m_PassWord.GetWindowTextA(strPassWord);

	//������������
	Cjson json;
	json["User"] = strUser;
	json["PassWord"] = strPassWord;
	Cjson package;
	package["User"] = strUser;
	package.SaveHwnd(m_hWnd);
	client.SendJsonReq(json,10000,package);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//ע��
void CChatTestDlg::OnBnClickedButton2()
{
	CRegDlg dlg;
	dlg.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

LPARAM CChatTestDlg::OpenMainDlg(WPARAM wparam,LPARAM lparam){
	Cjson jsonRsp = *(Cjson*)wparam;
	delete (Cjson*)wparam;
	Cjson jsonPackage = *(Cjson*)lparam;
	delete (Cjson*)lparam;
	if(jsonRsp["strRsp"].toValue().strValue == "��¼�ɹ�"){
		this->OnOK();
		CMainDlg dlg;
		dlg.strUser = jsonPackage["User"].toValue().strValue;
		dlg.DoModal();
	}
	else AfxMessageBox(jsonRsp["strRsp"].toValue().strValue);
	return 0;
}