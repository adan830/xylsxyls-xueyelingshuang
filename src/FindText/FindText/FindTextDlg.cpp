
// MFCTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FindText.h"
#include "FindTextDlg.h"
#include "afxdialogex.h"
#include "CGetPath/CGetPathAPI.h"
#include "CCharset/CCharsetAPI.h"
#include "Ctxt/CtxtAPI.h"
#include "CStringManager/CStringManagerAPI.h"
#include <Winuser.h>

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



CFindTextDlg::CFindTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindTextDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindTextDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT3, m_path);
    DDX_Control(pDX, IDC_EDIT2, m_outFormat);
    DDX_Control(pDX, IDC_EDIT1, m_text);
    DDX_Control(pDX, IDC_EDIT4, m_find);
    DDX_Control(pDX, IDC_CHECK1, m_case);
    DDX_Control(pDX, IDC_BUTTON1, m_btnFind);
}

BEGIN_MESSAGE_MAP(CFindTextDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFindTextDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CFindTextDlg::OnBnClickedButton2)
    ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CMFCTestDlg ��Ϣ�������

BOOL CFindTextDlg::OnInitDialog()
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
    
    m_strOutFormat = ".exe";
    m_strPath = "D:\\xueyelingshuang\\src\\��������\\";
    m_outFormat.SetWindowText(CCharset::AnsiToUnicode(m_strOutFormat).c_str());
    m_case.SetCheck(1);
    m_case.EnableWindow(FALSE);
    ::SetFocus(m_text.m_hWnd);
	ModifyStyle(0, WS_MINIMIZEBOX);
	//ModifyStyle(0, WS_MAXIMIZEBOX);
	GetSystemMenu(FALSE)->InsertMenu(-1, MF_BYPOSITION, SC_MINIMIZE, _T("��С��"));
	//GetSystemMenu(FALSE)->InsertMenu(-1, MF_BYPOSITION, SC_MAXIMIZE, _T("���"));
	GetSystemMenu(FALSE)->InsertMenu(-1, MF_BYPOSITION, SC_RESTORE, _T("��ԭ"));
    ::SendMessage(m_hWnd, DM_SETDEFID, (WPARAM)IDC_BUTTON1, NULL);
	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFindTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFindTextDlg::OnPaint()
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
HCURSOR CFindTextDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFindTextDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    //m_find.SetWindowText(L"������...");
    //m_find.UpdateWindow();
    m_strFind = "";

    CString text;
    m_text.GetWindowText(text);
    string strText = CCharset::UnicodeToAnsi(text.GetBuffer());
    text.ReleaseBuffer();
    bool bCase = m_case.GetCheck() == 1;
    CString strPath;
    m_path.GetWindowText(strPath);
    if (strPath != "")
    {
        m_strPath = CCharset::UnicodeToAnsi(strPath.GetBuffer());
        strPath.ReleaseBuffer();
    }
    CString strOutPath;
    m_outFormat.GetWindowText(strOutPath);
    m_strOutFormat = CCharset::UnicodeToAnsi(strOutPath.GetBuffer());
    strOutPath.ReleaseBuffer();
    vector<string>vecOutFormat = CStringManager::split(m_strOutFormat,".");

    string strLineFlag = "-------------------------------------------------"
                         "-------------------------------------------------"
                         "-----------------------------------------------------\r\n";
    vector<string> vecPath = CGetPath::FindFilePath("", m_strPath, 3);
    int i = -1;
    while (i++ != vecPath.size() - 1)
    {
        bool isOutFormat = IsOutFormat(vecPath.at(i), vecOutFormat);
        if (isOutFormat == true)
        {
            continue;
        }
        Ctxt txt(vecPath.at(i));
        txt.LoadTxt(2, "~!@#$%^&*()");
        bool bAddFileName = false;

        //�ȿ��ļ���
        if (vecPath.at(i).find(strText) != -1)
        {
            bAddFileName = true;
            //��������ļ�����һ�п���
            m_strFind.append(strLineFlag + vecPath.at(i) + "\r\n\r\n");
        }

        int line = -1;
        while (line++ != txt.vectxt.size() - 1)
        {
            string& oneLine = txt.vectxt.at(line).at(0);
            string str0;
            str0.resize(1);
            str0[0] = '\0';
            CStringManager::Replace(oneLine, str0, "");
            //�������һ�����ҵ��ؼ���
            if (oneLine.find(strText) != -1)
            {
                if (bAddFileName == false)
                {
                    bAddFileName = true;
                    //��������ļ�����һ�п���
                    m_strFind.append(strLineFlag + vecPath.at(i) + "\r\n\r\n");
                }
                //�������һ��
                m_strFind.append(oneLine + "\r\n");
            }
        }
        //����һ������Ϣ���ļ�������п���
        if (bAddFileName == true)
        {
            m_strFind.append("\r\n\r\n");
        }
    }
    if (m_strFind == "")
    {
        m_strFind = "��";
    }
    m_find.SetWindowText(CCharset::AnsiToUnicode(m_strFind).c_str());
}

void CFindTextDlg::OnBnClickedButton2()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    m_strPath = CGetPath::GetFolderFromWindow(m_hWnd);
    m_path.SetWindowText(CCharset::AnsiToUnicode(m_strPath).c_str());
}

bool CFindTextDlg::IsOutFormat(const string& path, const vector<string>& vecOutFormat)
{
    int i = 0;
    while (i++ != vecOutFormat.size() - 1)
    {
        if (CStringManager::Right(path, vecOutFormat.at(i).size() + 1) == ("." + vecOutFormat.at(i)))
        {
            return true;
        }
    }
    return false;
}

BOOL CFindTextDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    RECT findRect;
    ::GetWindowRect(m_find.m_hWnd, &findRect);
    BOOL isInFindRect = ::PtInRect(&findRect,pt);
    if (isInFindRect == 1)
    {
        ::SendMessage(m_find.m_hWnd, WM_MOUSEWHEEL, MAKEWPARAM(nFlags, zDelta), MAKELPARAM(pt.x, pt.y));
    }
    return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}