
// MFCTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "afxdialogex.h"
#include "Person.h"
#include "ConfigInfo.h"
#include "CGetPath/CGetPathAPI.h"

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
	DDX_Control(pDX, IDC_EDIT1, name);
	DDX_Control(pDX, IDC_COMBO1, year);
	DDX_Control(pDX, IDC_COMBO2, month);
	DDX_Control(pDX, IDC_COMBO3, day);
	DDX_Control(pDX, IDC_COMBO4, sex);
	DDX_Control(pDX, IDC_COMBO5, marriage);
	DDX_Control(pDX, IDC_COMBO6, education);
	DDX_Control(pDX, IDC_EDIT3, jobName);
	DDX_Control(pDX, IDC_COMBO7, jobNature);
	DDX_Control(pDX, IDC_EDIT4, salary);
	DDX_Control(pDX, IDC_COMBO8, fatherJob);
	DDX_Control(pDX, IDC_COMBO9, fatherPension);
	DDX_Control(pDX, IDC_COMBO10, motherJob);
	DDX_Control(pDX, IDC_COMBO11, motherPension);
	DDX_Control(pDX, IDC_EDIT5, introduce);
	DDX_Control(pDX, IDC_BUTTON1, check);
	DDX_Control(pDX, IDC_COMBO12, tall);
	DDX_Control(pDX, IDC_COMBO13, weight);
	DDX_Control(pDX, IDC_EDIT6, mobile);
	DDX_Control(pDX, IDC_EDIT7, qq);
	DDX_Control(pDX, IDC_EDIT8, weChat);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTestDlg::OnBnClickedButton1)
	ON_MESSAGE(configInfo.storage[ConfigInfo::FillPersonInt].toValue<int>(), &CMFCTestDlg::OnSetPerson)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCTestDlg::OnBnClickedButton4)
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
	int nYear = 1950;
	CString strYear;
	while (nYear != 2010){
		strYear.Format("%d", nYear);
		year.AddString(strYear);
		nYear++;
	}
	int nMonth = 1;
	CString strMonth;
	while (nMonth != 13){
		strMonth.Format("%02d", nMonth);
		month.AddString(strMonth);
		nMonth++;
	}
	int nDay = 1;
	CString strDay;
	while (nDay != 32){
		strDay.Format("%02d", nDay);
		day.AddString(strDay);
		nDay++;
	}

	sex.AddString("��");
	sex.AddString("Ů");

	marriage.AddString("δ��");
	marriage.AddString("�̻�δ��");
	marriage.AddString("�ѻ�����");

	education.AddString("��ר");
	education.AddString("��ר");
	education.AddString("�Կ���ѧ");
	education.AddString("����");
	education.AddString("����");
	education.AddString("һ��");
	education.AddString("���ƺ�����ѧ");
	education.AddString("����˫ѧλ");
	education.AddString("ѧ˶");
	education.AddString("ר˶");
	education.AddString("˶ʿ˫ѧλ");
	education.AddString("˶ʿ������ѧ");
	education.AddString("��ʿ");
	education.AddString("��ʿ������ѧ");
	
	int nTall = 140;
	CString strTall;
	while (nTall != 220){
		strTall.Format("%d", nTall);
		tall.AddString(strTall);
		nTall++;
	}

	int nWeight = 40;
	CString strWeight;
	while (nWeight != 120){
		strWeight.Format("%d", nWeight);
		weight.AddString(strWeight);
		nWeight++;
	}

	jobNature.AddString("��Ӫ��ҵ");
	jobNature.AddString("���й�˾");
	jobNature.AddString("������ҵ");
	jobNature.AddString("������ҵ");

	fatherJob.AddString("��ְ");
	fatherJob.AddString("����");
	fatherJob.AddString("��Ӫ");
	fatherJob.AddString("ũ��");

	fatherPension.AddString("��");
	fatherPension.AddString("��");

	motherJob.AddString("��ְ");
	motherJob.AddString("����");
	motherJob.AddString("��Ӫ");
	motherJob.AddString("ũ��");

	motherPension.AddString("��");
	motherPension.AddString("��");

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
	Person person;
	int error = manager.Check(m_hWnd, &person);
	manager.ShowError(error);
	if (error != 0) return;
	manager.Save(&person);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


LRESULT CMFCTestDlg::OnSetPerson(WPARAM wparam, LPARAM lparam){
	Person* person = (Person*)lparam;
	CString strName;
	name.GetWindowTextA(strName);
	person->name = (LPSTR)(LPCTSTR)strName;
	CString strYear, strMonth, strDay;
	year.GetWindowTextA(strYear);
	month.GetWindowTextA(strMonth);
	day.GetWindowTextA(strDay);
	person->birth.setTime((LPSTR)(LPCTSTR)(strYear + "-" + strMonth + "-" + strDay + " 00:00:00"));
	CString strSex;
	sex.GetWindowTextA(strSex);
	person->sex = (LPSTR)(LPCTSTR)strSex;
	CString strMarriage;
	marriage.GetWindowTextA(strMarriage);
	person->marriage = (LPSTR)(LPCTSTR)strMarriage;
	CString strEducation;
	education.GetWindowTextA(strEducation);
	person->education = (LPSTR)(LPCTSTR)strEducation;
	CString strTall;
	tall.GetWindowTextA(strTall);
	person->tall = (LPSTR)(LPCTSTR)strTall;
	CString strWeight;
	weight.GetWindowTextA(strWeight);
	person->weight = (LPSTR)(LPCTSTR)strWeight;
	CString strJobName;
	jobName.GetWindowTextA(strJobName);
	person->jobName = (LPSTR)(LPCTSTR)strJobName;
	CString strJobNature;
	jobNature.GetWindowTextA(strJobNature);
	person->jobNature = (LPSTR)(LPCTSTR)strJobNature;
	CString strSalary;
	salary.GetWindowTextA(strSalary);
	person->salary = atoi((LPSTR)(LPCTSTR)strSalary);
	CString strMobile;
	mobile.GetWindowTextA(strMobile);
	person->mobile = (LPSTR)(LPCTSTR)strMobile;
	CString strQq;
	qq.GetWindowTextA(strQq);
	person->qq = (LPSTR)(LPCTSTR)strQq;
	CString strWeChat;
	weChat.GetWindowTextA(strWeChat);
	person->weChat = (LPSTR)(LPCTSTR)strWeChat;
	CString strFatherJob;
	fatherJob.GetWindowTextA(strFatherJob);
	person->fatherJob = atoi((LPSTR)(LPCTSTR)strFatherJob);
	CString strFatherPension;
	fatherPension.GetWindowTextA(strFatherPension);
	person->fatherPension = atoi((LPSTR)(LPCTSTR)strFatherPension);
	CString strMotherJob;
	motherJob.GetWindowTextA(strMotherJob);
	person->motherJob = atoi((LPSTR)(LPCTSTR)strMotherJob);
	CString strMotherPension;
	motherPension.GetWindowTextA(strMotherPension);
	person->motherPension = atoi((LPSTR)(LPCTSTR)strMotherPension);
	person->picture1 = (LPSTR)(LPCTSTR)picture1;
	person->picture2 = (LPSTR)(LPCTSTR)picture2;
	person->picture3 = (LPSTR)(LPCTSTR)picture3;
	CString strIntroduce;
	introduce.GetWindowTextA(strIntroduce);
	person->introduce = (LPSTR)(LPCTSTR)strIntroduce;
	return 0;
}

void CMFCTestDlg::OnBnClickedButton2()
{
	CGetPath getpath;
	picture1 = getpath.GetFileFromWindow().c_str();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCTestDlg::OnBnClickedButton3()
{
	CGetPath getpath;
	picture2 = getpath.GetFileFromWindow().c_str();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCTestDlg::OnBnClickedButton4()
{
	CGetPath getpath;
	picture3 = getpath.GetFileFromWindow().c_str();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
