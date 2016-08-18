// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatTest.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "CTCPClient.h"
#include "ChatDlg.h"

// CMainDlg �Ի���
CMainDlg* pMainDlg = NULL;

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	//pClient = &client;
}

//��һ��ȫ�ֱ������ж��Ƿ���Ҫ������������
int nWindows = 0;

CMainDlg::~CMainDlg()
{
	
}

void CMainDlg::OnCancel(){
	nWindows--;
	if(nWindows == 0){
		//����
		Cjson jsonReq;
		jsonReq["User"] = strUser;
		pClient->SendJsonReq(jsonReq,10005);
		this->OnOK();
	}
	else this->ShowWindow(SW_HIDE);
	return;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_Text);
	DDX_Control(pDX, IDC_EDIT1, m_Show);
	DDX_Control(pDX, IDC_LIST2, m_List);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
	ON_MESSAGE(10002,&CMainDlg::ShowText)
	ON_MESSAGE(10003,&CMainDlg::AddList)
	ON_MESSAGE(10004,&CMainDlg::ShowFriendList)
	ON_MESSAGE(10005,&CMainDlg::DeleteFriendList)
	ON_MESSAGE(10008,&CMainDlg::OpenNewWindow)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CMainDlg::OnDblclkList)
END_MESSAGE_MAP()

HWND MainHwnd = 0;

BOOL CMainDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0,WS_EX_APPWINDOW);

	MainHwnd = m_hWnd;
	nWindows++;
	pClient = &client;

	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_List.SetExtendedStyle(dwStyle); //������չ���
	//���List
	m_List.InsertColumn(0,"User",LVCFMT_CENTER,0);//������
	m_List.InsertColumn(1,"�����б�",LVCFMT_CENTER,190);//������
	//m_List.InsertColumn(2,"·��"    ,LVCFMT_CENTER,0);//������


	//�Ƚ��Լ����͸������ˣ�10003
	Cjson jsonReq;
	jsonReq["User"] = strUser;
	pClient->SendJsonReq(jsonReq,10003);
	Cjson jsonPackage;
	jsonPackage.SaveHwnd(m_hWnd);
	//����ˢ�º����б�10004
	pClient->SendJsonReq(jsonReq,10004,jsonPackage);
	//���ù��Ĭ�ϳ���λ��
	m_Text.SetFocus();
	return 0;
}

// CMainDlg ��Ϣ�������

//������Ϣ10002
void CMainDlg::OnBnClickedButton1()
{
	CString strText = "";
	m_Text.GetWindowText(strText);

	Cjson json;
	json["User"] = strUser;
	json["text"] = strText;
	pClient->SendJsonReq(json,10002);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

LPARAM CMainDlg::ShowText(WPARAM wparam,LPARAM lparam){
	Cjson jsonRsp = *(Cjson*)wparam;
	time_t t = time(0);
	char tmp[64] = {};
	strftime(tmp,sizeof(tmp),"%Hʱ%M��%S��\r\n",localtime(&t));
	m_Show.SetSel(-1);
	m_Show.ReplaceSel(jsonRsp["NickName"].toValue().strValue + "    " + tmp + jsonRsp["text"].toValue().strValue + "\r\n\r\n");
	return 0;
}

LPARAM CMainDlg::AddList(WPARAM wparam,LPARAM lparam){
	Cjson jsonRsp = *(Cjson*)wparam;
	int nLine = m_List.GetItemCount();
	m_List.InsertItem(nLine,jsonRsp["User"].toValue().strValue);
	m_List.SetItemText(nLine,1,jsonRsp["NickName"].toValue().strValue);
	return 0;
}

LPARAM CMainDlg::ShowFriendList(WPARAM wparam,LPARAM lparam){
	Cjson jsonRsp = *(Cjson*)wparam;
	int count = jsonRsp["NameCount"].toValue().nValue;
	int nLine = m_List.GetItemCount();
	int i = -1;
	while(i++ != count - 1){
		CString strName = "";
		strName.Format("User%d",i);
		m_List.InsertItem(nLine + i,jsonRsp[strName].toValue().strValue);
		strName.Format("NickName%d",i);
		m_List.SetItemText(nLine + i,1,jsonRsp[strName].toValue().strValue);
	}
	return 0;
}

LPARAM CMainDlg::DeleteFriendList(WPARAM wparam,LPARAM lparam){
	Cjson jsonRsp = *(Cjson*)wparam;
	CString strUser = jsonRsp["User"].toValue().strValue;
	int nLine = m_List.GetItemCount();
	int i = -1;
	while(i++ != nLine - 1){
		if(m_List.GetItemText(i,0) == strUser){
			m_List.DeleteItem(i);
			break;
		}
	}
	return 0;
}

LPARAM CMainDlg::OpenNewWindow(WPARAM wparam,LPARAM lparam){
	Cjson jsonReq = *(Cjson*)wparam;
	CString strUser = jsonReq["User"].toValue().strValue;
	CString strChatUser = jsonReq["ChatUser"].toValue().strValue;
	//����Ҳ����򴴽�һ����ģʽ����
	if(mapChatHwnd.find(strUser) == mapChatHwnd.end()){
		CChatDlg* pDlg = new CChatDlg;
		pDlg->strUser = strUser;
		pDlg->strChatUser = strChatUser;
		pDlg->Create(CChatDlg::IDD,pDlg);
		pDlg->SetWindowTextA(pDlg->strChatUser);
		pDlg->ShowWindow(SW_SHOW);
	}
	return 0;
}

void CMainDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult){
	CChatDlg* pDlg = new CChatDlg(NULL);
	pDlg->strUser = strUser;
	pDlg->strChatUser = m_List.GetItemText(m_List.GetSelectionMark(),0);
	pDlg->Create(CChatDlg::IDD,pDlg);
	pDlg->SetWindowTextA(pDlg->strChatUser);
	pDlg->ShowWindow(SW_SHOW);
}

