// PicDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "PicDlgQuery.h"
#include "afxdialogex.h"


// CPicDlg �Ի���

IMPLEMENT_DYNAMIC(CPicDlgQuery, CDialogEx)

CPicDlgQuery::CPicDlgQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPicDlgQuery::IDD, pParent)
{
    
}

CPicDlgQuery::~CPicDlgQuery()
{
}

void CPicDlgQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPicDlgQuery, CDialogEx)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CPicDlg ��Ϣ�������


void CPicDlgQuery::OnPaint()
{
    CPaintDC dc(this);
}

void CPicDlgQuery::init(const vector<Person>& vecPerson){
    this->vecPerson = vecPerson;
}

BOOL CPicDlgQuery::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}
