
// MFCTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "afxdialogex.h"
#include "CGetPath/CGetPathAPI.h"
#include "CStringManager/CStringManagerAPI.h"
#include "Ctxt/CtxtAPI.h"
#include "CEncodeDecode/CEncodeDecodeAPI.h"

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
	DDX_Control(pDX, IDC_EDIT1, m_EditPassword);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCTestDlg::OnBnClickedButton2)
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

void HandleOneFile(vector<vector<string>>& vectxt,string& strOneName,Ctxt& notelog,string& note){
	int ifHasHead = 0;
	
	int i = -1;
	while (i++ != vectxt.size() - 1){
		if (CStringManager::Find(vectxt.at(i).at(0), note) != -1 && i >= 3){
			if (ifHasHead == 0){
				notelog.AddWriteLine("<line break>");
				notelog.AddWriteLine("%s", strOneName.c_str());
				ifHasHead = 1;
			}
			notelog.AddWriteLine("%s", vectxt.at(i - 3).at(0).c_str());
			notelog.AddWriteLine("%s", vectxt.at(i - 2).at(0).c_str());
			notelog.AddWriteLine("%s", vectxt.at(i - 1).at(0).c_str());
			notelog.AddWriteLine("%s", vectxt.at(i - 0).at(0).c_str());
		}
	}
}

bool DeleteOneFile(vector<vector<string>>& vectxt, string& note){
	bool bResult = 0;
	int i = -1;
	auto itvectxt = vectxt.begin();
	while (i++ != vectxt.size() - 1){
		//˵���Ѿ��ҵ�
		if (CStringManager::Find(vectxt.at(i).at(0), note) != -1 && i >= 3){
			bResult = 1;
			i--;
			itvectxt = vectxt.erase(itvectxt);
			continue;
		}
		itvectxt++;
	}
	return bResult;
}

void Encode(Ctxt& notelog, const string& password){
	int i = -1;
	while (i++ != notelog.vectxt.size() - 1){
		notelog.vectxt.at(i).at(0) = CEncodeDecode::AESEncode(password, notelog.vectxt.at(i).at(0));
	}
}

void CMFCTestDlg::OnBnClickedButton1()
{
	CGetPath getpath;
	string strpath = getpath.GetFolderFromWindow(m_hWnd);
	CString strPassword;
	m_EditPassword.GetWindowTextA(strPassword);
	vector<string> vecFile = CStringManager::split((LPSTR)(LPCTSTR)strPassword, ".");
	//�������̫�����ʽ����
	if (vecFile.size() <= 2) return;
	//��Կ
	string password = vecFile.at(0);
	//ע��
	string note = vecFile.at(1);

	Ctxt notelog("note.txt");
	notelog.OpenFile_a();

	int i = 1;
	while (i++ != vecFile.size() - 1){
		vector<string> vecPath = getpath.FindFilePath(vecFile.at(i), strpath, 2);
		int j = -1;
		while (j++ != vecPath.size() - 1){
			//��ȡ��ÿ���ļ�·��
			string strOnePath = vecPath.at(j);
			string strOneName = strOnePath;
			CStringManager::Replace(strOneName, strpath, "");
			Ctxt txt(strOnePath);
			txt.LoadTxt(2, "!@#$%^&*()");
			HandleOneFile(txt.vectxt, strOneName, notelog, note);
		}
	}
	notelog.CloseFile();
	if (IDYES == AfxMessageBox("��ʼ����ɣ��Ƿ�ʼ�Ż���", MB_YESNO)){
		i = 1;
		while (i++ != vecFile.size() - 1){
			vector<string> vecPath = getpath.FindFilePath(vecFile.at(i), strpath, 2);
			int j = -1;
			while (j++ != vecPath.size() - 1){
				//��ȡ��ÿ���ļ�·��
				string strOnePath = vecPath.at(j);
				string strOneName = CStringManager::Right(strOnePath, strOnePath.length() - CStringManager::ReserveFind(strOnePath, '\\') - 1);
				Ctxt txt(strOnePath);
				txt.LoadTxt(2, "!@#$%^&*()");
				bool bResult = DeleteOneFile(txt.vectxt, note);
				if (bResult == 1) txt.Save();
			}
		}
		notelog.LoadTxt(2, "!@#$%^&*()");
		Encode(notelog, password);
		notelog.Save();
		AfxMessageBox("�Ż����");
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void LoadNote(vector<vector<string>>& vectxt,string& strpath){
	int i = 0;
	Ctxt notelog("note.log");
	Ctxt* loadtxt = NULL;
	//���ļ�������ָ��
	int line = 0;
	//���ļ��ļ�¼ָ��
	int linein = 0;
	notelog.OpenFile_a();
	int ifHasHead = 0;
	while (i < (int)vectxt.size()){
		string strOneName;
		//����������з�
		if (vectxt.at(i).at(0) == "<line break>"){
			line = 0;
			linein = 0;
			//ͨ�����У�����ָ�� + 1
			i++;
			//���뵽�µ��ļ�֮���־λ��Ϊ0
			ifHasHead = 0;
			//��ȡ�ļ���
			strOneName = vectxt.at(i).at(0);
			CStringManager::Replace(strOneName, "\r", "");
			string strOneNameTemp = CStringManager::Right(strOneName, strOneName.length() - CStringManager::ReserveFind(strOneName, '\\') - 1);
			i++;
			//��������в������в��ǻ��з������ڲ�ѭ��
			while (i < (int)vectxt.size() && (vectxt.at(i).at(0) != "<line break>")){
				CGetPath getpath;
				vector<string> vecpath = getpath.FindFilePath(strOneNameTemp, strpath);
				//����Ҳ������ļ�·��˵����ɾ��
				if (vecpath.size() == 0){
					//��¼�ļ���
					notelog.AddWriteLine("%s", strOneName.c_str());
					//ѭ����¼ÿ��ֱ����һ���ļ�
					while (i < (int)vectxt.size() && (vectxt.at(i).at(0) != "<line break>")){
						notelog.AddWriteLine("%s", vectxt.at(i).at(0).c_str());
						i++;
					}
					break;
				}
				//��ø��ļ�·��
				string strOnePath;
				int j = -1;
				while (j++ != vecpath.size() - 1){
					if (CStringManager::Replace(vecpath.at(j), strOneName, strOneName) == 1){
						strOnePath = vecpath.at(j);
						break;
					}
				}
				loadtxt = new Ctxt(strOnePath);
				loadtxt->LoadTxt(2, "!@#$%^&*()");
				
				while (true){
					while (line < (int)(loadtxt->vectxt.size()) && i < (int)vectxt.size()){
						//���ǰ������ͬ
						if (loadtxt->vectxt.at(line).at(0) == vectxt.at(i).at(0) && loadtxt->vectxt.at(line + 1).at(0) == vectxt.at(i + 1).at(0) && loadtxt->vectxt.at(line + 2).at(0) == vectxt.at(i + 2).at(0)){
							auto itvectxt = loadtxt->vectxt.begin();
							//�������ӵ�ָ��λ��
							int lineTemp = line + 3;
							while (lineTemp-- != 0){
								itvectxt++;
							}
							vector<string> vecTemp;
							vecTemp.push_back(vectxt.at(i + 3).at(0));
							//����
							loadtxt->vectxt.insert(itvectxt, 1, vecTemp);
							//���¼�¼ָ��λ��
							linein = line + 1;
							line = linein;
							i = i + 4;
							continue;
						}
						line++;
					}
					//���note.log����ĩβ�������ļ�
					if (i == vectxt.size()){
						loadtxt->Save();
						delete loadtxt;
						notelog.CloseFile();
						return;
					}
					//���������һ���ļ�
					else if (vectxt.at(i).at(0) == "<line break>"){
						break;
					}
					//�����������˵�����б��Ķ��ˣ���Ҫ��¼����
					else{
						//��ӡ�����־λ��Ϊ1����ֹ�´ν���
						if (ifHasHead == 0){
							notelog.AddWriteLine("%s", strOneName.c_str());
							ifHasHead = 1;
						}
						notelog.AddWriteLine("%s", vectxt.at(i + 0).at(0).c_str());
						notelog.AddWriteLine("%s", vectxt.at(i + 1).at(0).c_str());
						notelog.AddWriteLine("%s", vectxt.at(i + 2).at(0).c_str());
						notelog.AddWriteLine("%s", vectxt.at(i + 3).at(0).c_str());
						i = i + 4;
						//�Ѽ�¼ָ�븳������ָ��
						line = linein;
					}
				}
				loadtxt->Save();
				delete loadtxt;
			}
		}
	}
	notelog.CloseFile();
}

void Decode(vector<vector<string>>& vectxt,const string& password){
	int i = -1;
	while (i++ != vectxt.size() - 1){
		vectxt.at(i).at(0) = CEncodeDecode::AESDecode(password, vectxt.at(i).at(0));
	}
}

void CMFCTestDlg::OnBnClickedButton2()
{
	CGetPath getpath;
	string strpath = getpath.GetFolderFromWindow(m_hWnd);
	CString strPassword;
	m_EditPassword.GetWindowTextA(strPassword);
	//��Կ
	string password = (LPSTR)(LPCTSTR)strPassword;
	vector<string> vecPath = getpath.FindFilePath("note", "", 2);
	if (vecPath.size() == 0) return;
	string strOnePath = vecPath.at(0);
	string strName = CStringManager::Right(strOnePath, strOnePath.length() - CStringManager::ReserveFind(strOnePath, '\\') - 1);
	Ctxt txt(strOnePath);
	txt.LoadTxt(2, "!@#$%^&*()");
	Decode(txt.vectxt, password);
	LoadNote(txt.vectxt, strpath);
	AfxMessageBox("�������");

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
