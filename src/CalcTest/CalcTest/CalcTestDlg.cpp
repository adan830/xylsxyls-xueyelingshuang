
// CalcTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CalcTest.h"
#include "CalcTestDlg.h"
#include "afxdialogex.h"
#include "IntDateTime/IntDateTimeAPI.h"
#include "Ctxt/CtxtAPI.h"
#include "AddTime.h"
#include "CStringManager/CStringManagerAPI.h"

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


// CCalcTestDlg �Ի���



CCalcTestDlg::CCalcTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalcTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalcTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalcTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalcTestDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CCalcTestDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON5, &CCalcTestDlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON3, &CCalcTestDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CCalcTestDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCalcTestDlg ��Ϣ�������

BOOL CCalcTestDlg::OnInitDialog()
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

void CCalcTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalcTestDlg::OnPaint()
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
HCURSOR CCalcTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalcTestDlg::OnBnClickedButton1()
{
    //��ȡ��ʼʱ��
    IntDateTime cur;
    //�����ļ�
    string write = cur.toString();
    Ctxt txt(curPath + fileName);
    txt.LoadTxt(2, "~!@#$%^&*()");
    int size = txt.vectxt.size();
    if (size == 0)
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 98)
        {
            txt.AddLine("1%s", write.c_str());
            AfxMessageBox(_T("�ɹ�"));
            return;
        }
    }
    //���ҳ����һ���ǲ��ǽ���ʱ�䣬�������ֱ����ӣ����������Ҫ���������ʱ��
    string strLastTime = txt.vectxt.at(size - 1).at(0);
    if (strLastTime[0] == '0')
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 98)
        {
            txt.AddLine("1%s", write.c_str());
            AfxMessageBox(_T("�ɹ�"));
            return;
        }
    }
    else
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 100)
        {
            IntDateTime lastTime(&strLastTime[1]);
            //��������ʱ����ϴεĿ�ʼʱ�䳬��һ�����ϴο�ʼʱ������˵����������
            if (editTime - lastTime > 86400 || editTime < lastTime || write < editTime)
            {
                AfxMessageBox(_T("��������"));
            }
            //�����ȷ������ʱ��
            else
            {
                CAddTime addTimeDlg;
                addTimeDlg.SetEditTime(&editTime);
                int result = addTimeDlg.DoModal();
                if (result == 98)
                {
                    txt.AddLine("0%s", editTime.toString().c_str());
                    txt.AddLine("1%s", write.c_str());
                    AfxMessageBox(_T("�ɹ�"));
                    return;
                }
            }
        }
    }
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCalcTestDlg::OnBnClickedButton2()
{
    //��ȡ��ǰʱ��
    IntDateTime cur;
    //�����ļ�
    string write = cur.toString();

    Ctxt txt(curPath + fileName);
    txt.LoadTxt(2, "~!@#$%^&*()");
    int size = txt.vectxt.size();
    if (size == 0)
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 99)
        {
            result = 100;
            editTime = cur;
            editTime.time_ = 180000000;
        }
        if (result == 100)
        {
            CAddTime addTimeDlg;
            addTimeDlg.SetEditTime(&editTime);
            int result = addTimeDlg.DoModal();
            if (result == 98)
            {
                txt.AddLine("1%s", editTime.toString().c_str());
                txt.AddLine("0%s", write.c_str());
                AfxMessageBox(_T("�ɹ�"));
                return;
            }
        }
        return;
    }
    //���ҳ����һ���ǲ��ǿ�ʼʱ�䣬�������ֱ����ӣ����������Ҫ�����뿪ʼʱ��
    string strLastTime = txt.vectxt.at(size - 1).at(0);
    if (strLastTime[0] == '1' && cur - strLastTime < 86400)
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 98)
        {
            txt.AddLine("0%s", write.c_str());
            AfxMessageBox(_T("�ɹ�"));
            return;
        }
    }
    else
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 99)
        {
            result = 100;
            editTime = cur;
            editTime.time_ = 180000000;
        }
        if (result == 100)
        {
            IntDateTime lastTime(&strLastTime[1]);
            //��������ʱ������һ��ʱ������߱ȵ�ǰʱ������ߵ�ǰʱ��Ϳ�ʼʱ�������һ��
            if (editTime < lastTime || editTime > cur || cur - editTime > 86400)
            {
                AfxMessageBox(_T("��������"));
            }
            //�����ȷ������ʱ��
            else
            {
                CAddTime addTimeDlg;
                addTimeDlg.SetEditTime(&editTime);
                int result = addTimeDlg.DoModal();
                if (result == 98)
                {
                    txt.AddLine("1%s", editTime.toString().c_str());
                    txt.AddLine("0%s", write.c_str());
                    AfxMessageBox(_T("�ɹ�"));
                    return;
                }
            }
        }
    }
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCalcTestDlg::OnBnClickedButton5()
{
    Ctxt txt(curPath + fileName);
    txt.LoadTxt(2, "~!@#$%^&*()");
    int allTime = 0;
    int i = -1;
    while (i++ != txt.vectxt.size() - 1)
    {
        if (i + 1 == txt.vectxt.size())
        {
            break;
        }
        string beginTime = txt.vectxt.at(i).at(0);
        string endTime = txt.vectxt.at(++i).at(0);
        IntDateTime begin(&beginTime[1]);
        IntDateTime end(&endTime[1]);
        allTime = allTime + (end - begin);
    }
    double day = allTime / 3600.0 / 8.0;

    Ctxt mytxt(curPath + myFileName);
    mytxt.LoadTxt(2, "~!@#$%^&*()");
    int myAllTime = 0;
    i = -1;
    while (i++ != mytxt.vectxt.size() - 1)
    {
        if (i + 1 == mytxt.vectxt.size())
        {
            break;
        }
        string beginTime = mytxt.vectxt.at(i).at(0);
        string endTime = mytxt.vectxt.at(++i).at(0);
        IntDateTime begin(&beginTime[1]);
        IntDateTime end(&endTime[1]);
        myAllTime = myAllTime + (end - begin);
    }
    double myDay = myAllTime / 3600.0 / 8.0;

    CString strDay;
    strDay.Format(_T("����������ʣ����Ҫ%lf�����\n�����������Բⲿ����Ҫ%lf�����"), day, myDay);
    AfxMessageBox(strDay);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCalcTestDlg::OnBnClickedButton3()
{
    //��ȡ��ʼʱ��
    IntDateTime cur;
    //�����ļ�
    string write = cur.toString();
    Ctxt txt(curPath + myFileName);
    txt.LoadTxt(2, "~!@#$%^&*()");
    int size = txt.vectxt.size();
    if (size == 0)
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 98)
        {
            txt.AddLine("1%s", write.c_str());
            AfxMessageBox(_T("�ɹ�"));
            return;
        }
    }
    //���ҳ����һ���ǲ��ǽ���ʱ�䣬�������ֱ����ӣ����������Ҫ���������ʱ��
    string strLastTime = txt.vectxt.at(size - 1).at(0);
    if (strLastTime[0] == '0')
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 98)
        {
            txt.AddLine("1%s", write.c_str());
            AfxMessageBox(_T("�ɹ�"));
            return;
        }
    }
    else
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 100)
        {
            IntDateTime lastTime(&strLastTime[1]);
            //��������ʱ����ϴεĿ�ʼʱ�䳬��һ�����ϴο�ʼʱ������˵����������
            if (editTime - lastTime > 86400 || editTime < lastTime || write < editTime)
            {
                AfxMessageBox(_T("��������"));
            }
            //�����ȷ������ʱ��
            else
            {
                CAddTime addTimeDlg;
                addTimeDlg.SetEditTime(&editTime);
                int result = addTimeDlg.DoModal();
                if (result == 98)
                {
                    txt.AddLine("0%s", editTime.toString().c_str());
                    txt.AddLine("1%s", write.c_str());
                    AfxMessageBox(_T("�ɹ�"));
                    return;
                }
            }
        }
    }
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCalcTestDlg::OnBnClickedButton4()
{
    //��ȡ��ǰʱ��
    IntDateTime cur;
    //�����ļ�
    string write = cur.toString();

    Ctxt txt(curPath + myFileName);
    txt.LoadTxt(2, "~!@#$%^&*()");
    int size = txt.vectxt.size();
    if (size == 0)
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 100)
        {
            CAddTime addTimeDlg;
            addTimeDlg.SetEditTime(&editTime);
            int result = addTimeDlg.DoModal();
            if (result == 98)
            {
                txt.AddLine("1%s", editTime.toString().c_str());
                txt.AddLine("0%s", write.c_str());
                AfxMessageBox(_T("�ɹ�"));
                return;
            }
        }
        return;
    }
    //���ҳ����һ���ǲ��ǿ�ʼʱ�䣬�������ֱ����ӣ����������Ҫ�����뿪ʼʱ��
    string strLastTime = txt.vectxt.at(size - 1).at(0);
    if (strLastTime[0] == '1' && cur - strLastTime < 86400)
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 98)
        {
            txt.AddLine("0%s", write.c_str());
            AfxMessageBox(_T("�ɹ�"));
            return;
        }
    }
    else
    {
        CAddTime addTimeDlg;
        addTimeDlg.SetEditTime(&editTime);
        int result = addTimeDlg.DoModal();
        if (result == 100)
        {
            IntDateTime lastTime(&strLastTime[1]);
            //��������ʱ������һ��ʱ������߱ȵ�ǰʱ������ߵ�ǰʱ��Ϳ�ʼʱ�������һ��
            if (editTime < lastTime || editTime > cur || cur - editTime > 86400)
            {
                AfxMessageBox(_T("��������"));
            }
            //�����ȷ������ʱ��
            else
            {
                CAddTime addTimeDlg;
                addTimeDlg.SetEditTime(&editTime);
                int result = addTimeDlg.DoModal();
                if (result == 98)
                {
                    txt.AddLine("1%s", editTime.toString().c_str());
                    txt.AddLine("0%s", write.c_str());
                    AfxMessageBox(_T("�ɹ�"));
                    return;
                }
            }
        }
    }
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}
