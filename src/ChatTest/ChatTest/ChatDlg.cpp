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

extern int nWindows;

CChatDlg::~CChatDlg()
{
	nWindows--;
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


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CChatDlg ��Ϣ�������


void CChatDlg::OnBnClickedButton1()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CChatDlg::OnCancel(){
	delete this;
}