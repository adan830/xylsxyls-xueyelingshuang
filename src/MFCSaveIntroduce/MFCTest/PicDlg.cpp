// PicDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "PicDlg.h"
#include "afxdialogex.h"


// CPicDlg �Ի���

IMPLEMENT_DYNAMIC(CPicDlg, CDialogEx)

CPicDlg::CPicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPicDlg::IDD, pParent)
{
    
}

CPicDlg::~CPicDlg()
{
}

void CPicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPicDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPicDlg ��Ϣ�������


void CPicDlg::OnPaint()
{
    CPaintDC dc(this);
    //ֱ�Ӽ���ͼƬ�Ͳ���Ҫ��CDC��ͼ�ˣ���ȡ�ڴ���ʾ�豸�������
    HDC picHDC = ::CreateCompatibleDC(dc.m_hDC);
    //�������ͼ��ֱ��ѡ��ͼƬ���豸�������
    ::SelectObject(picHDC, picHBITMAP);
    ::TransparentBlt(dc.m_hDC, 0, 0, width, height, picHDC, 0, 0, width, height, SRCCOPY);
    //����Ҫ��ɾ��
    ::DeleteDC(picHDC);
}

bool CPicDlg::init(string picture){
    this->picture = picture;
    if (picture != ""){
        CImage img;
        img.Load(picture.c_str());
        picHBITMAP = img.Detach();
        if (picHBITMAP == nullptr) return false;
        //picHBITMAP = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), picture.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        BITMAP bi = { 0 };
        //��ȡλͼ��Ϣ��������ȣ���ߣ�������
        GetObject(picHBITMAP, sizeof(BITMAP), &bi);
        width = bi.bmWidth;
        height = bi.bmHeight;
        return true;
    }
    return false;
}

BOOL CPicDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    RECT rectClient;
    rectClient.left = 0;
    rectClient.top = 0;
    rectClient.right = width + 16;
    rectClient.bottom = height + 38;
    MoveWindow(&rectClient);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}

void CPicDlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    if (picHBITMAP != nullptr) DeleteObject(picHBITMAP);
    // TODO:  �ڴ˴������Ϣ����������
}
