
// CivilEngineeringDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CivilEngineering.h"
#include "CivilEngineeringDlg.h"
#include "afxdialogex.h"

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


// CCivilEngineeringDlg �Ի���



CCivilEngineeringDlg::CCivilEngineeringDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCivilEngineeringDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCivilEngineeringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_BallPositionAndRadius);
	DDX_Control(pDX, IDC_EDIT2, m_PointPosition);
	DDX_Control(pDX, IDC_EDIT8, m_PointSpeed);
	DDX_Control(pDX, IDC_EDIT5, m_x);
	DDX_Control(pDX, IDC_EDIT6, m_y);
	DDX_Control(pDX, IDC_EDIT7, m_z);
	DDX_Control(pDX, IDC_EDIT4, m_biggestx);
	DDX_Control(pDX, IDC_EDIT3, m_OsmoticCoefficient);
	DDX_Control(pDX, IDC_EDIT9, m_NowNumber);
}

BEGIN_MESSAGE_MAP(CCivilEngineeringDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCivilEngineeringDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCivilEngineeringDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCivilEngineeringDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCivilEngineeringDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCivilEngineeringDlg ��Ϣ�������

BOOL CCivilEngineeringDlg::OnInitDialog()
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
	m_OsmoticCoefficient.SetWindowTextA("1");
	m_x.SetWindowTextA("0");
	m_y.SetWindowTextA("0");
	m_z.SetWindowTextA("0");
	m_biggestx.SetWindowTextA("8");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCivilEngineeringDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCivilEngineeringDlg::OnPaint()
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
HCURSOR CCivilEngineeringDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "CtxtAPI.h"
#include "CGetPathAPI.h"

void CCivilEngineeringDlg::OnBnClickedButton1()
{
	CString strPointSpeed            = ""; m_PointSpeed.GetWindowTextA(strPointSpeed);
	CString strPointPosition         = ""; m_PointPosition.GetWindowTextA(strPointPosition);
	CString strBallPositionAndRadius = ""; m_BallPositionAndRadius.GetWindowTextA(strBallPositionAndRadius);
	Ctxt txtPointSpeed;
	//�ֱ�õ� �ڵ��ţ�jx��jy��jz
	txtPointSpeed.LoadTxt(strPointSpeed,1,"11-16,20-32,36-48,52-64");
	Ctxt txtPointPosition;
	//�ֱ�õ� �ڵ��ţ�x��y��z���ֱ�Ϊat 3��6,��8��10
	txtPointPosition.LoadTxt(strPointPosition,2," ");
	Ctxt txtBallPositionAndRadius;
	//�ֱ�õ� ���ţ���뾶��x��y��z
	txtBallPositionAndRadius.LoadTxt(strBallPositionAndRadius,1,"1-8,9-22,48-61,62-75,76-89");
	AfxMessageBox("��ʼ����ϣ����ȷ����ʼ����");
	//д���ļ�
	Ctxt printFile;
	CGetPath getpath;
	printFile.AddWriteLine(getpath.GetCurrentExePath() + "123456.txt",2000,"����                         ����                         Fx            Fy           Fz");
	//�������꼰�뾶�ĵ�һ�п�ʼ����
	int iLine = 0;
	while(iLine++ != txtBallPositionAndRadius.vectxt.size() - 2){
		//�洢��С���������
		double ShortestDistance = 10000;
		int ShortestNumber = 0;
		//�Ȼ�õ�һ�е�����
		double x = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(2));
		double y = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(3));
		double z = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(4));
		//����ƽ����
		CString strx = ""; m_x.GetWindowTextA(strx); x = x + atof(strx);
		CString stry = ""; m_y.GetWindowTextA(stry); y = y + atof(stry);
		CString strz = ""; m_z.GetWindowTextA(strz); z = z + atof(strz);
		//���x�Ƚϵ����ֵ
		CString strBiggestX = 0; m_biggestx.GetWindowTextA(strBiggestX); double biggestx = atof(strBiggestX);
		int iSize = txtPointPosition.vectxt.size();
		while(iSize-- != 0){
			//���x����������Ͳ��Ƚ���
			if(abs(x - atof(txtPointPosition.vectxt.at(iSize).at(6))) > biggestx) break;
			//��ȥ��.��,
			txtPointPosition.vectxt.at(iSize).at(6).Replace(".",""); txtPointPosition.vectxt.at(iSize).at(6).Replace(",","");
			txtPointPosition.vectxt.at(iSize).at(8).Replace(".",""); txtPointPosition.vectxt.at(iSize).at(8).Replace(",","");
			txtPointPosition.vectxt.at(iSize).at(10).Replace(".",""); txtPointPosition.vectxt.at(iSize).at(10).Replace(",","");
			//�����һ�п�ʼ�õ��ڵ����������
			double tempx = atof(txtPointPosition.vectxt.at(iSize).at(6));
			double tempy = atof(txtPointPosition.vectxt.at(iSize).at(8));
			double tempz = atof(txtPointPosition.vectxt.at(iSize).at(10));
			//�õ������ƽ��
			double distance = (x - tempx) * (x - tempx) + (y - tempy) * (y - tempy) + (z - tempz) * (z - tempz);
			if(distance < ShortestDistance){
				ShortestDistance = distance;
				ShortestNumber = atoi(txtPointPosition.vectxt.at(iSize).at(3));
			}
		}
		//�ӽڵ�����õ�����̾���ڵ���ȥ�ڵ�������Ѱ��
		double jx = atof(txtPointSpeed.vectxt.at(ShortestNumber + 2).at(1));
		double jy = atof(txtPointSpeed.vectxt.at(ShortestNumber + 2).at(2));
		double jz = atof(txtPointSpeed.vectxt.at(ShortestNumber + 2).at(3));
		//��ȡ��͸ϵ��
		CString strOsmoticCoefficient = ""; m_OsmoticCoefficient.GetWindowTextA(strOsmoticCoefficient); double OsmoticCoefficient = atof(strOsmoticCoefficient);
		//�õ���뾶
		double Radius = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(1));
		//�õ�Fx��Fy��Fz
		double Fx = 4 / 3 * 3.1416 * Radius * Radius * Radius * jx / OsmoticCoefficient;
		double Fy = 4 / 3 * 3.1416 * Radius * Radius * Radius * jy / OsmoticCoefficient;
		double Fz = 4 / 3 * 3.1416 * Radius * Radius * Radius * jz / OsmoticCoefficient;
		printFile.AddWriteLine(getpath.GetCurrentExePath() + "123456.txt",2000,"%s  (%s %s %s)  %e %e %e",
			txtBallPositionAndRadius.vectxt.at(iLine + 1).at(0),
			txtBallPositionAndRadius.vectxt.at(iLine + 1).at(2),txtBallPositionAndRadius.vectxt.at(iLine + 1).at(3),txtBallPositionAndRadius.vectxt.at(iLine + 1).at(4),Fx,Fy,Fz);
		m_NowNumber.SetWindowTextA(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(0));
	}
	/*
	double aa = 0;
	CString strr = " 1.53061E-105";
	aa = atof(strr);
	double a = 1.53061E-105;
	double b = a * a;
	double c = 1.53062E-106;
	double d = c * c;
	CString str = "";
	str.Format("%lf",b);
	if(b < d) AfxMessageBox(str);*/
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCivilEngineeringDlg::OnBnClickedButton2()
{
	CGetPath getpath;
	m_BallPositionAndRadius.SetWindowTextA(getpath.GetFileFromWindow());
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCivilEngineeringDlg::OnBnClickedButton3()
{
	CGetPath getpath;
	m_PointPosition.SetWindowTextA(getpath.GetFileFromWindow());
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCivilEngineeringDlg::OnBnClickedButton4()
{
	CGetPath getpath;
	m_PointSpeed.SetWindowTextA(getpath.GetFileFromWindow());
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
