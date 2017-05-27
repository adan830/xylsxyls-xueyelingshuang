
// MFCTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Manager.h"
#include "Person.h"
#include "Search.h"
#include "CStringManager/CStringManagerAPI.h"
#include "ConfigInfo.h"

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


// CMFCTestDlg �Ի���



CMFCTestDlg::CMFCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, yearSmall);
	DDX_Control(pDX, IDC_COMBO2, monthSmall);
	DDX_Control(pDX, IDC_COMBO3, daySmall);
	DDX_Control(pDX, IDC_COMBO4, yearBig);
	DDX_Control(pDX, IDC_COMBO5, monthBig);
	DDX_Control(pDX, IDC_COMBO6, dayBig);
	DDX_Control(pDX, IDC_COMBO7, sex);
	DDX_Control(pDX, IDC_COMBO13, merriage);
	DDX_Control(pDX, IDC_COMBO8, tallSmall);
	DDX_Control(pDX, IDC_COMBO9, tallBig);
	DDX_Control(pDX, IDC_COMBO14, house);
	DDX_Control(pDX, IDC_COMBO10, weightSmall);
	DDX_Control(pDX, IDC_COMBO11, weightBig);
	DDX_Control(pDX, IDC_COMBO12, education);
	DDX_Control(pDX, IDC_EDIT1, salary);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTestDlg::OnBnClickedButton1)
    ON_MESSAGE(GetConfig(FillSearchInt, int), &CMFCTestDlg::OnSetSearchInfo)
END_MESSAGE_MAP()


// CMFCTestDlg ��Ϣ�������

BOOL CMFCTestDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCTestDlg::OnPaint()
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
HCURSOR CMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTestDlg::OnBnClickedButton1()
{
	//::SendMessage(GetDlgItem(IDC_STATIC1)->m_hWnd, WM_SETTEXT, 0, (LPARAM)"shit");
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	Search search;
	Manager::SearchInfo(m_hWnd, &search);
	vector<Person> vecPerson = Manager::Find(search);
	AfxMessageBox(CStringManager::Format("һ���ҵ�%d��",vecPerson.size()).c_str());
	Manager::ShowDlg(vecPerson);
}

LRESULT CMFCTestDlg::OnSetSearchInfo(WPARAM wparam, LPARAM lparam){
	Search* search = (Search*)lparam;
	CString strYearSmall;
	yearSmall.GetWindowTextA(strYearSmall);
	CString strMonthSmall;
	monthSmall.GetWindowTextA(strMonthSmall);
	CString strDaySmall;
	daySmall.GetWindowTextA(strDaySmall);
	search->smallBirth = IntDateTime(atoi(CStringManager::Format("%d%02d%02d", atoi(strYearSmall), atoi(strMonthSmall), atoi(strDaySmall)).c_str()), 0);

	CString strYearBig;
	yearBig.GetWindowTextA(strYearBig);
	CString strMonthBig;
	monthBig, GetWindowTextA(strMonthBig);
	CString strDayBig;
	dayBig.GetWindowTextA(strDayBig);
	search->bigBirth = IntDateTime(atoi(CStringManager::Format("%d%02d%02d", atoi(strYearBig), atoi(strMonthBig), atoi(strDayBig)).c_str()), 0);

	CString strSex;
	sex.GetWindowTextA(strSex);
	search->sex = (LPSTR)(LPCTSTR)strSex;

	CString strMerriage;
	merriage.GetWindowTextA(strMerriage);
	search->marriage = (LPSTR)(LPCTSTR)strMerriage;

	CString strTallSmall;
	tallSmall.GetWindowTextA(strTallSmall);
	search->smallTall = atoi(strTallSmall);

	CString strTallBig;
	tallBig.GetWindowTextA(strTallBig);
	search->bigTall = atoi(strTallBig);

	CString strHouse;
	house.GetWindowTextA(strHouse);
	search->house = (LPSTR)(LPCTSTR)strHouse;

	CString strWeightSmall;
	weightSmall.GetWindowTextA(strWeightSmall);
	search->smallWeight = atoi(strWeightSmall);

	CString strWeightBig;
	weightBig.GetWindowTextA(strWeightBig);
	search->bigWeight = atoi(strWeightBig);

	CString strEducation;
	education.GetWindowTextA(strEducation);
	search->education = (LPSTR)(LPCTSTR)strEducation;

	CString strSalary;
	salary.GetWindowTextA(strSalary);
	search->salary = atoi(strSalary);
	return 0;
}