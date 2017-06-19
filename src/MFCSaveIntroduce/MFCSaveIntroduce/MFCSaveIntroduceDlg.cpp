
// MFCSaveIntroduceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCSaveIntroduce.h"
#include "MFCSaveIntroduceDlg.h"
#include "afxdialogex.h"
#include "Person.h"
#include "ConfigInfo.h"
#include "CGetPath/CGetPathAPI.h"
#include "CStringManager/CStringManagerAPI.h"
#include "PicDlg.h"
#include "CScreen/CScreenAPI.h"
#include "CCharset/CCharsetAPI.h"

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


// CMFCSaveIntroduceDlg �Ի���



CMFCSaveIntroduceDlg::CMFCSaveIntroduceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCSaveIntroduceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSaveIntroduceDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_BUTTON6, picture1show);
	DDX_Control(pDX, IDC_BUTTON7, picture2show);
	DDX_Control(pDX, IDC_BUTTON8, picture3show);
	DDX_Control(pDX, IDC_COMBO14, house);
	DDX_Control(pDX, IDC_COMBO15, car);
	DDX_Control(pDX, IDC_EDIT9, household);
	DDX_Control(pDX, IDC_COMBO16, houseAttri);
	DDX_Control(pDX, IDC_EDIT10, houseAddr);
}

BEGIN_MESSAGE_MAP(CMFCSaveIntroduceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCSaveIntroduceDlg::OnBnClickedButton1)
    ON_MESSAGE(GetConfig(FillPersonInt, int), &CMFCSaveIntroduceDlg::OnSetPerson)
    ON_MESSAGE(GetConfig(ShowPersonInt, int), &CMFCSaveIntroduceDlg::OnShowPerson)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCSaveIntroduceDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCSaveIntroduceDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCSaveIntroduceDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CMFCSaveIntroduceDlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CMFCSaveIntroduceDlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CMFCSaveIntroduceDlg::OnBnClickedButton7)
    ON_BN_CLICKED(IDC_BUTTON8, &CMFCSaveIntroduceDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CMFCSaveIntroduceDlg ��Ϣ�������

BOOL CMFCSaveIntroduceDlg::OnInitDialog()
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
	while (nYear != 2010){
        year.AddString(CCharset::AnsiToUnicode(CStringManager::Format("%d", nYear)).c_str());
		nYear++;
	}
	int nMonth = 1;
	while (nMonth != 13){
        month.AddString(CCharset::AnsiToUnicode(CStringManager::Format("%02d", nMonth)).c_str());
		nMonth++;
	}
	int nDay = 1;
	while (nDay != 32){
		day.AddString(CCharset::AnsiToUnicode(CStringManager::Format("%02d", nDay)).c_str());
		nDay++;
	}

	sex.AddString(L"��");
	sex.AddString(L"Ů");

	marriage.AddString(L"δ��");
	marriage.AddString(L"�̻�δ��");
	marriage.AddString(L"�ѻ�����");

	education.AddString(L"��ר����");
	education.AddString(L"��ר");
	education.AddString(L"��ר");
	education.AddString(L"�Կ���ѧ");
	education.AddString(L"����");
	education.AddString(L"����");
	education.AddString(L"һ��");
	education.AddString(L"���ƺ�����ѧ");
	education.AddString(L"����˫ѧλ");
	education.AddString(L"ѧ˶");
	education.AddString(L"ר˶");
	education.AddString(L"˶ʿ˫ѧλ");
	education.AddString(L"˶ʿ������ѧ");
	education.AddString(L"��ʿ");
	education.AddString(L"��ʿ������ѧ");
	
	int nTall = 140;
	while (nTall != 220){
        tall.AddString(CCharset::AnsiToUnicode(CStringManager::Format("%d", nTall)).c_str());
		nTall++;
	}

	int nWeight = 40;
	while (nWeight != 120){
        weight.AddString(CCharset::AnsiToUnicode(CStringManager::Format("%d", nWeight)).c_str());
		nWeight++;
	}

	house.AddString(L"�޷�");
	house.AddString(L"�з��д���");
	house.AddString(L"�з��޴���");

	car.AddString(L"�޳�");
	car.AddString(L"�г�");

	houseAttri.AddString(L"����");
	houseAttri.AddString(L"��س���");
	houseAttri.AddString(L"���ũ��");

	jobNature.AddString(L"��Ӫ��ҵ");
	jobNature.AddString(L"���й�˾");
	jobNature.AddString(L"������ҵ");
	jobNature.AddString(L"������ҵ");

	fatherJob.AddString(L"��ְ");
	fatherJob.AddString(L"����");
	fatherJob.AddString(L"��Ӫ");
	fatherJob.AddString(L"ũ��");

	fatherPension.AddString(L"��");
	fatherPension.AddString(L"��");

	motherJob.AddString(L"��ְ");
	motherJob.AddString(L"����");
	motherJob.AddString(L"��Ӫ");
	motherJob.AddString(L"ũ��");

	motherPension.AddString(L"��");
	motherPension.AddString(L"��");

    picture1show.EnableWindow(FALSE);
    picture2show.EnableWindow(FALSE);
    picture3show.EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCSaveIntroduceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCSaveIntroduceDlg::OnPaint()
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
HCURSOR CMFCSaveIntroduceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCSaveIntroduceDlg::OnBnClickedButton1()
{
	Person person;
    int error = Manager::Check(m_hWnd, &person);
    Manager::ShowError(error);
	if (error != 0) return;
    Manager::SavePerson(&person);
    picture1 = person.picture1.c_str();
    picture2 = person.picture2.c_str();
    picture3 = person.picture3.c_str();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


LRESULT CMFCSaveIntroduceDlg::OnSetPerson(WPARAM wparam, LPARAM lparam){
	Person* person = (Person*)lparam;
	CString strName;
	name.GetWindowText(strName);
	person->name = ToString(strName);
	CString strYear, strMonth, strDay;
	year.GetWindowText(strYear);
	month.GetWindowText(strMonth);
	day.GetWindowText(strDay);
	CString bitrhResult = strYear + "-" + strMonth + "-" + strDay + " 00:00:00";
	person->birth.setTime(ToString(bitrhResult));
	CString strSex;
	sex.GetWindowText(strSex);
	person->sex = ToString(strSex);
	CString strMarriage;
	marriage.GetWindowText(strMarriage);
	person->marriage = ToString(strMarriage);
	CString strEducation;
	education.GetWindowText(strEducation);
	person->education = ToString(strEducation);
	CString strTall;
	tall.GetWindowText(strTall);
	person->tall = atoi(CCharset::UnicodeToAnsi(strTall.GetBuffer()).c_str());
	strTall.ReleaseBuffer();
	CString strWeight;
	weight.GetWindowText(strWeight);
	person->weight = atoi(CCharset::UnicodeToAnsi(strWeight.GetBuffer()).c_str());
	strWeight.ReleaseBuffer();
	CString strHouse;
	house.GetWindowText(strHouse);
	person->house = ToString(strHouse);
	CString strCar;
	car.GetWindowText(strCar);
	person->car = ToString(strCar);
	CString strHousehold;
	household.GetWindowText(strHousehold);
	person->household = ToString(strHousehold);
	CString strHouseAttri;
	houseAttri.GetWindowText(strHouseAttri);
	person->houseAttri = ToString(strHouseAttri);
	CString strHouseAddr;
	houseAddr.GetWindowText(strHouseAddr);
	person->houseAddr = ToString(strHouseAddr);
	CString strJobName;
	jobName.GetWindowText(strJobName);
	person->jobName = ToString(strJobName);
	CString strJobNature;
	jobNature.GetWindowText(strJobNature);
	person->jobNature = ToString(strJobNature);
	CString strSalary;
	salary.GetWindowText(strSalary);
	person->salary = atoi(ToString(strSalary).c_str());
	CString strMobile;
	mobile.GetWindowText(strMobile);
	person->mobile = ToString(strMobile);
	CString strQq;
	qq.GetWindowText(strQq);
	person->qq = ToString(strQq);
	CString strWeChat;
	weChat.GetWindowText(strWeChat);
	person->weChat = ToString(strWeChat);
	CString strFatherJob;
	fatherJob.GetWindowText(strFatherJob);
	person->fatherJob = ToString(strFatherJob);
	CString strFatherPension;
	fatherPension.GetWindowText(strFatherPension);
	person->fatherPension = ToString(strFatherPension);
	CString strMotherJob;
	motherJob.GetWindowText(strMotherJob);
	person->motherJob = ToString(strMotherJob);
	CString strMotherPension;
	motherPension.GetWindowText(strMotherPension);
	person->motherPension = ToString(strMotherPension);
	person->picture1 = ToString(picture1);
	person->picture2 = ToString(picture2);
	person->picture3 = ToString(picture3);
	CString strIntroduce;
	introduce.GetWindowText(strIntroduce);
	person->introduce = ToString(strIntroduce);
	return 0;
}

LRESULT CMFCSaveIntroduceDlg::OnShowPerson(WPARAM wparam, LPARAM lparam){
    Person* person = (Person*)lparam;
    name.SetWindowText(CCharset::AnsiToUnicode(person->name).c_str());
	year.SelectString(0, CCharset::AnsiToUnicode(CStringManager::Format("%d", person->birth.getYear())).c_str());
	month.SelectString(0, CCharset::AnsiToUnicode(CStringManager::Format("%02d", person->birth.getMonth())).c_str());
	day.SelectString(0, CCharset::AnsiToUnicode(CStringManager::Format("%02d", person->birth.getDay())).c_str());
	sex.SelectString(0, CCharset::AnsiToUnicode(person->sex).c_str());
	marriage.SelectString(0, CCharset::AnsiToUnicode(person->marriage).c_str());
	education.SelectString(0, CCharset::AnsiToUnicode(person->education).c_str());
	tall.SelectString(0, CCharset::AnsiToUnicode(CStringManager::Format("%d", person->tall)).c_str());
	weight.SelectString(0, CCharset::AnsiToUnicode(CStringManager::Format("%d", person->weight)).c_str());
	house.SelectString(0, CCharset::AnsiToUnicode(person->house).c_str());
	car.SelectString(0, CCharset::AnsiToUnicode(person->car).c_str());
	household.SetWindowText(CCharset::AnsiToUnicode(person->household).c_str());
	houseAttri.SelectString(0, CCharset::AnsiToUnicode(person->houseAttri).c_str());
	houseAddr.SetWindowText(CCharset::AnsiToUnicode(person->houseAddr).c_str());
	jobName.SetWindowText(CCharset::AnsiToUnicode(person->jobName).c_str());
	jobNature.SelectString(0, CCharset::AnsiToUnicode(person->jobNature).c_str());
	if (person->salary == 0)
	{
		salary.SetWindowText(L"");
	}
	else
	{
		salary.SetWindowText(CCharset::AnsiToUnicode(CStringManager::Format("%d", person->salary)).c_str());
	}
	mobile.SetWindowText(CCharset::AnsiToUnicode(person->mobile).c_str());
	qq.SetWindowText(CCharset::AnsiToUnicode(person->qq).c_str());
	weChat.SetWindowText(CCharset::AnsiToUnicode(person->weChat).c_str());
	fatherJob.SelectString(0, CCharset::AnsiToUnicode(person->fatherJob).c_str());
	fatherPension.SelectString(0, CCharset::AnsiToUnicode(person->fatherPension).c_str());
	motherJob.SelectString(0, CCharset::AnsiToUnicode(person->motherJob).c_str());
	motherPension.SelectString(0, CCharset::AnsiToUnicode(person->motherPension).c_str());
    picture1 = person->picture1.c_str();
    picture2 = person->picture2.c_str();
    picture3 = person->picture3.c_str();
	introduce.SetWindowText(CCharset::AnsiToUnicode(person->introduce).c_str());

    if (picture1 != "") picture1show.EnableWindow(TRUE);
    else picture1show.EnableWindow(FALSE);
    if (picture2 != "") picture2show.EnableWindow(TRUE);
    else picture2show.EnableWindow(FALSE);
    if (picture3 != "") picture3show.EnableWindow(TRUE);
    else picture3show.EnableWindow(FALSE);
    return 0;
}

string CMFCSaveIntroduceDlg::ToString(CString& str)
{
	string result = CCharset::UnicodeToAnsi(str.GetBuffer());
	str.ReleaseBuffer();
	return result;
}

void CMFCSaveIntroduceDlg::OnBnClickedButton2()
{
    picture1 = CCharset::AnsiToUnicode(CGetPath::GetFileFromWindow(m_hWnd)).c_str();
    if (picture1 == "-1") picture1 = "";
    if (picture1 != "") picture1show.EnableWindow(TRUE);
    else picture1show.EnableWindow(FALSE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCSaveIntroduceDlg::OnBnClickedButton3()
{
	picture2 = CCharset::AnsiToUnicode(CGetPath::GetFileFromWindow(m_hWnd)).c_str();
    if (picture2 == "-1") picture2 = "";
    if (picture2 != "") picture2show.EnableWindow(TRUE);
    else picture2show.EnableWindow(FALSE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCSaveIntroduceDlg::OnBnClickedButton4()
{
	picture3 = CCharset::AnsiToUnicode(CGetPath::GetFileFromWindow(m_hWnd)).c_str();
    if (picture3 == "-1") picture3 = "";
    if (picture3 != "") picture3show.EnableWindow(TRUE);
    else picture3show.EnableWindow(FALSE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCSaveIntroduceDlg::OnBnClickedButton5()
{
    Person person;
    int error = Manager::Query(m_hWnd, &person);
    Manager::ShowError(error);
    if (error != 0) return;
    Manager::ShowPerson(m_hWnd, &person);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCSaveIntroduceDlg::OnBnClickedButton6()
{
    ShowPicture(picture1);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMFCSaveIntroduceDlg::ShowPicture(const CString& picture){
    CPicDlg picDlg;
    bool result = false;
	CString pic = picture;
	if (picture.Find(L":") != -1)
	{
		result = picDlg.init(CCharset::UnicodeToAnsi(pic.GetBuffer()));
		pic.ReleaseBuffer();
	}
	else
	{
		result = picDlg.init(CGetPath::GetCurrentExePath() + CCharset::UnicodeToAnsi(pic.GetBuffer()));
		pic.ReleaseBuffer();
	}
    if (result == true) picDlg.DoModal();
}

void CMFCSaveIntroduceDlg::OnBnClickedButton7()
{
    ShowPicture(picture2);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCSaveIntroduceDlg::OnBnClickedButton8()
{
    ShowPicture(picture3);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}
