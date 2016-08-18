// ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatTest.h"
#include "ChatDlg.h"
#include "afxdialogex.h"


// CChatDlg �Ի���

IMPLEMENT_DYNAMIC(CChatDlg, CDialogEx)

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatDlg::IDD, pParent)
{
	
}



CChatDlg::~CChatDlg()
{
	nWindows--;
	mapChatHwnd.erase(strUser);
	if(nWindows == 0){
		//����
		Cjson jsonReq;
		jsonReq["User"] = strUser;
		pClient->SendJsonReq(jsonReq,10005);
	}
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Show);
	DDX_Control(pDX, IDC_EDIT2, m_Text);
}

extern CTCPClient client;

BOOL CChatDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	nWindows++;
	pClient = &client;
	mapChatHwnd[strUser] = m_hWnd;
	return 1;
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatDlg::OnBnClickedButton1)
	ON_MESSAGE(10006,&CChatDlg::ChatShow)
END_MESSAGE_MAP()


// CChatDlg ��Ϣ�������


void CChatDlg::OnBnClickedButton1()
{
	CString strText = "";
	m_Text.GetWindowTextA(strText);

	//����10006
	Cjson jsonReq;
	jsonReq["User"] = strUser;
	jsonReq["ChatUser"] = strChatUser;
	jsonReq["text"] = strText;
	Cjson package;
	package.SaveHwnd(m_hWnd);
	pClient->SendJsonReq(jsonReq,10006,package);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CChatDlg::OnCancel(){
	delete this;
}

LPARAM CChatDlg::ChatShow(WPARAM wparam,LPARAM lparam){
	Cjson jsonRsp = *(Cjson*)wparam;
	CString strNickName = jsonRsp["NickName"].toValue().strValue;
	CString strText = jsonRsp["text"].toValue().strValue;
	//���ܳ��ֶ��������˵��ǵ��Ĵ���û�ص���������ʱ�򴫹�������һ����json
	if(strNickName == "-1" && strText == "-1") return 0;
	time_t t = time(0);
	char tmp[64] = {};
	strftime(tmp,sizeof(tmp),"%Hʱ%M��%S��\r\n",localtime(&t));
	m_Show.SetSel(-1);
	m_Show.ReplaceSel(strNickName + "    " + tmp + strText + "\r\n\r\n");
	return 0;
}