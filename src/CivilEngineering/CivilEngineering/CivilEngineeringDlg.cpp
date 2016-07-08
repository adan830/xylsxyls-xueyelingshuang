
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
	m_OsmoticCoefficient.SetWindowTextA("7e-5");
	m_x.SetWindowTextA("150");
	m_y.SetWindowTextA("25");
	m_z.SetWindowTextA("25");
	m_biggestx.SetWindowTextA("50");

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
#include "CiniAPI.h"
#include <afxmt.h>

#define Create_Thread(FunName,ParameterName,ThreadID) CreateThread(NULL, 0, FunName, (LPVOID)ParameterName, 0, &ThreadID)

DWORD WINAPI MakeFun(LPVOID lpParam){
	CCivilEngineeringDlg *pThis = (CCivilEngineeringDlg *)lpParam;

	CMutex mutex;
	mutex.Lock();
	CString strPointSpeed            = ""; pThis->m_PointSpeed.GetWindowTextA(strPointSpeed);
	CString strPointPosition         = ""; pThis->m_PointPosition.GetWindowTextA(strPointPosition);
	CString strBallPositionAndRadius = ""; pThis->m_BallPositionAndRadius.GetWindowTextA(strBallPositionAndRadius);
	//��ȡ��͸ϵ��
	CString strOsmoticCoefficient = ""; pThis->m_OsmoticCoefficient.GetWindowTextA(strOsmoticCoefficient); double OsmoticCoefficient = atof(strOsmoticCoefficient);
	//���x�Ƚϵ����ֵ
	CString strBiggestX = 0; pThis->m_biggestx.GetWindowTextA(strBiggestX); double biggestx = atof(strBiggestX);
	//����ƽ����
	CString strx = ""; pThis->m_x.GetWindowTextA(strx); double movex = atof(strx);
	CString stry = ""; pThis->m_y.GetWindowTextA(stry); double movey = atof(stry);
	CString strz = ""; pThis->m_z.GetWindowTextA(strz); double movez = atof(strz);
	mutex.Unlock();

	//��������ļ���ڵ������4����
	CGetPath getpath;
	Cini setini(getpath.GetCurrentExePath() + "set.ini");
	int node = atoi(setini.ReadIni("PointPosition_node"));
	int nodex = atoi(setini.ReadIni("PointPosition_nodex"));
	int nodey = atoi(setini.ReadIni("PointPosition_nodey"));
	int nodez = atoi(setini.ReadIni("PointPosition_nodez"));
	//�򿪲����ļ�
	Ctxt txttest(getpath.GetCurrentExePath() + "test.txt");
	

	Ctxt txtBallPositionAndRadius(strBallPositionAndRadius);
	//�ֱ�õ� ���ţ���뾶��x��y��z
	txtBallPositionAndRadius.LoadTxt(1,setini.ReadIni("BallPositionAndRadius"));
	txttest.OpenFile_a();
	txttest.AddWriteLine(100,"����=%s,�뾶=%s,x=%s,y=%s,z=%s",txtBallPositionAndRadius.vectxt.at(2).at(0),txtBallPositionAndRadius.vectxt.at(2).at(1),txtBallPositionAndRadius.vectxt.at(2).at(2),txtBallPositionAndRadius.vectxt.at(2).at(3),txtBallPositionAndRadius.vectxt.at(2).at(4));
	txttest.AddWriteLine(100,"����=%s,�뾶=%s,x=%s,y=%s,z=%s",txtBallPositionAndRadius.vectxt.at(3).at(0),txtBallPositionAndRadius.vectxt.at(3).at(1),txtBallPositionAndRadius.vectxt.at(3).at(2),txtBallPositionAndRadius.vectxt.at(3).at(3),txtBallPositionAndRadius.vectxt.at(3).at(4));
	txttest.AddWriteLine(100,"����=%s,�뾶=%s,x=%s,y=%s,z=%s",txtBallPositionAndRadius.vectxt.at(4).at(0),txtBallPositionAndRadius.vectxt.at(4).at(1),txtBallPositionAndRadius.vectxt.at(4).at(2),txtBallPositionAndRadius.vectxt.at(4).at(3),txtBallPositionAndRadius.vectxt.at(4).at(4));
	txttest.AddWriteLine(100,"����=%s,�뾶=%s,x=%s,y=%s,z=%s",txtBallPositionAndRadius.vectxt.at(5).at(0),txtBallPositionAndRadius.vectxt.at(5).at(1),txtBallPositionAndRadius.vectxt.at(5).at(2),txtBallPositionAndRadius.vectxt.at(5).at(3),txtBallPositionAndRadius.vectxt.at(5).at(4));
	txttest.AddWriteLine(100,"����=%s,�뾶=%s,x=%s,y=%s,z=%s",txtBallPositionAndRadius.vectxt.at(6).at(0),txtBallPositionAndRadius.vectxt.at(6).at(1),txtBallPositionAndRadius.vectxt.at(6).at(2),txtBallPositionAndRadius.vectxt.at(6).at(3),txtBallPositionAndRadius.vectxt.at(6).at(4));
	txttest.CloseFile();
	AfxMessageBox("PFC���ݼ������");

	Ctxt txtPointPosition(strPointPosition);
	//�ֱ�õ� �ڵ��ţ�x��y��z���ֱ�Ϊat 3��6,��8��10
	txtPointPosition.LoadTxt(2," ");
	bool x = txttest.OpenFile_a();
	txttest.AddWriteLine(100,"�ڵ���=%s,x=%s,y=%s,z=%s",txtPointPosition.vectxt.at(0).at(node),txtPointPosition.vectxt.at(0).at(nodex),txtPointPosition.vectxt.at(0).at(nodey),txtPointPosition.vectxt.at(0).at(nodez));
	txttest.AddWriteLine(100,"�ڵ���=%s,x=%s,y=%s,z=%s",txtPointPosition.vectxt.at(1).at(node),txtPointPosition.vectxt.at(1).at(nodex),txtPointPosition.vectxt.at(1).at(nodey),txtPointPosition.vectxt.at(1).at(nodez));
	txttest.AddWriteLine(100,"�ڵ���=%s,x=%s,y=%s,z=%s",txtPointPosition.vectxt.at(2).at(node),txtPointPosition.vectxt.at(2).at(nodex),txtPointPosition.vectxt.at(2).at(nodey),txtPointPosition.vectxt.at(2).at(nodez));
	txttest.AddWriteLine(100,"�ڵ���=%s,x=%s,y=%s,z=%s",txtPointPosition.vectxt.at(3).at(node),txtPointPosition.vectxt.at(3).at(nodex),txtPointPosition.vectxt.at(3).at(nodey),txtPointPosition.vectxt.at(3).at(nodez));
	txttest.AddWriteLine(100,"�ڵ���=%s,x=%s,y=%s,z=%s",txtPointPosition.vectxt.at(4).at(node),txtPointPosition.vectxt.at(4).at(nodex),txtPointPosition.vectxt.at(4).at(nodey),txtPointPosition.vectxt.at(4).at(nodez));
	txttest.CloseFile();
	AfxMessageBox("ABAQUS�ڵ�����������");

	Ctxt txtPointSpeed(strPointSpeed);
	//�ֱ�õ� �ڵ��ţ�jx��jy��jz
	txtPointSpeed.LoadTxt(1,setini.ReadIni("PointSpeed"));
	txttest.OpenFile_a();
	txttest.AddWriteLine(100,"�ڵ���=%s,jx=%s,jy=%s,jz=%s",txtPointSpeed.vectxt.at(3).at(0),txtPointSpeed.vectxt.at(3).at(1),txtPointSpeed.vectxt.at(3).at(2),txtPointSpeed.vectxt.at(3).at(3));
	txttest.AddWriteLine(100,"�ڵ���=%s,jx=%s,jy=%s,jz=%s",txtPointSpeed.vectxt.at(4).at(0),txtPointSpeed.vectxt.at(4).at(1),txtPointSpeed.vectxt.at(4).at(2),txtPointSpeed.vectxt.at(4).at(3));
	txttest.AddWriteLine(100,"�ڵ���=%s,jx=%s,jy=%s,jz=%s",txtPointSpeed.vectxt.at(5).at(0),txtPointSpeed.vectxt.at(5).at(1),txtPointSpeed.vectxt.at(5).at(2),txtPointSpeed.vectxt.at(5).at(3));
	txttest.AddWriteLine(100,"�ڵ���=%s,jx=%s,jy=%s,jz=%s",txtPointSpeed.vectxt.at(6).at(0),txtPointSpeed.vectxt.at(6).at(1),txtPointSpeed.vectxt.at(6).at(2),txtPointSpeed.vectxt.at(6).at(3));
	txttest.AddWriteLine(100,"�ڵ���=%s,jx=%s,jy=%s,jz=%s",txtPointSpeed.vectxt.at(7).at(0),txtPointSpeed.vectxt.at(7).at(1),txtPointSpeed.vectxt.at(7).at(2),txtPointSpeed.vectxt.at(7).at(3));
	txttest.AddWriteLine(100,"\r\n");
	txttest.CloseFile();
	AfxMessageBox("ABAQUS�ڵ����ټ�����ϣ����ȷ����ʼ����");

	//д���ļ�
	Ctxt printFile(getpath.GetCurrentExePath() + "��͸��.txt");
	printFile.OpenFile_a();
	printFile.AddWriteLine(2000,"����                         ����                         Fx            Fy           Fz");
	//�������꼰�뾶�ĵ�һ�п�ʼ����
	int iLine = 0;
	while(iLine++ != txtBallPositionAndRadius.vectxt.size() - 2){
		//�洢��С���������
		double ShortestDistance = 512000;
		int ShortestNumber = 0;
		//�Ȼ�õ�һ�е�����
		double x = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(2));
		double y = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(3));
		double z = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(4));
		//����ƽ����
		x = x + movex;
		y = y + movey;
		z = z + movez;
		//��ʼ�ӽڵ�����������Ѱ������Ƚ��������
		int iSize = txtPointPosition.vectxt.size();
		int iNum = -1;
		while(iNum++ != iSize - 1){
			//���x����������Ͳ��Ƚ���
			if(abs(x - atof(txtPointPosition.vectxt.at(iNum).at(nodex))) > biggestx) continue;
			//��ȥ��,
			txtPointPosition.vectxt.at(iNum).at(nodex).Replace(",","");
			txtPointPosition.vectxt.at(iNum).at(nodey).Replace(",","");
			txtPointPosition.vectxt.at(iNum).at(nodez).Replace(",","");
			//�����һ�п�ʼ�õ��ڵ����������
			double tempx = atof(txtPointPosition.vectxt.at(iNum).at(nodex));
			double tempy = atof(txtPointPosition.vectxt.at(iNum).at(nodey));
			double tempz = atof(txtPointPosition.vectxt.at(iNum).at(nodez));
			//�õ������ƽ��
			double distance = (x - tempx) * (x - tempx) + (y - tempy) * (y - tempy) + (z - tempz) * (z - tempz);
			if(distance < ShortestDistance){
				ShortestDistance = distance;
				ShortestNumber = atoi(txtPointPosition.vectxt.at(iNum).at(node));
			}
		}
		//�ӽڵ�����õ�����̾���ڵ���ȥ�ڵ�������Ѱ��
		double jx = atof(txtPointSpeed.vectxt.at(ShortestNumber + 2).at(1));
		double jy = atof(txtPointSpeed.vectxt.at(ShortestNumber + 2).at(2));
		double jz = atof(txtPointSpeed.vectxt.at(ShortestNumber + 2).at(3));
		//�õ���뾶
		double Radius = atof(txtBallPositionAndRadius.vectxt.at(iLine + 1).at(1));
		//�õ�Fx��Fy��Fz
		double Fx = 4 / 3 * 3.1416 * Radius * Radius * Radius * jx / OsmoticCoefficient;
		double Fy = 4 / 3 * 3.1416 * Radius * Radius * Radius * jy / OsmoticCoefficient;
		double Fz = 4 / 3 * 3.1416 * Radius * Radius * Radius * jz / OsmoticCoefficient;
		printFile.AddWriteLine(200,"%s  (%s %s %s)  %e %e %e",txtBallPositionAndRadius.vectxt.at(iLine + 1).at(0),
			txtBallPositionAndRadius.vectxt.at(iLine + 1).at(2),txtBallPositionAndRadius.vectxt.at(iLine + 1).at(3),txtBallPositionAndRadius.vectxt.at(iLine + 1).at(4),Fx,Fy,Fz);

		mutex.Lock();
		CString percentage = "";
		percentage.Format("%lf",(iLine + 1.0) / txtBallPositionAndRadius.vectxt.size() * 100);
		pThis->m_NowNumber.SetWindowTextA(percentage.Mid(0,4) + "%");
		if(iLine == txtBallPositionAndRadius.vectxt.size() - 2) pThis->m_NowNumber.SetWindowTextA("100%");
		mutex.Unlock();
	}
	printFile.CloseFile();
	return 0;
}

void CCivilEngineeringDlg::OnBnClickedButton1()
{
	DWORD ThreadID = 0;
	Create_Thread(MakeFun,this,ThreadID);
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
