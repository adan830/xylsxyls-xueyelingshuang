// RegDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatTest.h"
#include "RegDlg.h"
#include "afxdialogex.h"
#include "Cjson/CjsonAPI.h"
#include "CTCPClient.h"

// CRegDlg �Ի���
CRegDlg* pRegDlg = NULL;

IMPLEMENT_DYNAMIC(CRegDlg, CDialogEx)

CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegDlg::IDD, pParent)
{
	pClient = &client;
}

CRegDlg::~CRegDlg()
{
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_NewUser);
	DDX_Control(pDX, IDC_EDIT2, m_NewPassWordOne);
	DDX_Control(pDX, IDC_EDIT3, m_NewPassWordTwo);
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegDlg::OnBnClickedButton1)
	ON_MESSAGE(10001,Close)
END_MESSAGE_MAP()


// CRegDlg ��Ϣ�������

//ע�ᣬ��Ϣ��10001
void CRegDlg::OnBnClickedButton1()
{
	CString strNewUser = "";
	m_NewUser.GetWindowTextA(strNewUser);
	CString strNewPassWordOne = "";
	m_NewPassWordOne.GetWindowTextA(strNewPassWordOne);
	CString strNewPassWordTwo = "";
	m_NewPassWordTwo.GetWindowTextA(strNewPassWordTwo);

	if(strNewPassWordOne != strNewPassWordTwo){
		AfxMessageBox("�����������벻һ��");
		return;
	}

	Cjson json;
	json["NewUser"] = strNewUser;
	json["NewPassWord"] = strNewPassWordOne;

	Cjson jsonPackage;
	jsonPackage.SaveHwnd(m_hWnd);
	pClient->SendJsonReq(json,10001,jsonPackage);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

LPARAM CRegDlg::Close(WPARAM wparam,LPARAM lparam){
	Cjson jsonRsp = *(Cjson*)wparam;
	if(jsonRsp["strRsp"].toValue().strValue == "ע��ɹ�"){
		this->OnOK();
	}
	else AfxMessageBox(jsonRsp["strRsp"].toValue().strValue);
	return 0;
}