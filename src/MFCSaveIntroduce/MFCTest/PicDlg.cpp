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
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CPicDlg ��Ϣ�������


void CPicDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO:  �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
    //ֱ�Ӽ���ͼƬ�Ͳ���Ҫ��CDC��ͼ�ˣ���ȡ�ڴ���ʾ�豸�������
    HDC picHDC = ::CreateCompatibleDC(dc.m_hDC);
    //�������ͼ��ֱ��ѡ��ͼƬ���豸�������
    ::SelectObject(picHDC, picHBITMAP);
    //CImage img;
    //img.Attach(picHBITMAP);
    //img.Save("D:\\232.bmp");
    ::TransparentBlt(dc.m_hDC, 0, 0, width, height, picHDC, 0, 0, width, height, SRCCOPY);
    ::ReleaseDC(m_hWnd, picHDC);
}

void CPicDlg::init(string picture){
    this->picture = picture;
    if (picture != ""){
        picHBITMAP = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), picture.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        BITMAP bi = { 0 };
        //��ȡλͼ��Ϣ��������ȣ���ߣ�������
        GetObject(picHBITMAP, sizeof(BITMAP), &bi);
        width = bi.bmWidth;
        height = bi.bmHeight;
    }
}

BOOL CPicDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    RECT rectClient;
    rectClient.left = 0;
    rectClient.top = 0;
    rectClient.right = width;
    rectClient.bottom = height;
    MoveWindow(&rectClient);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}


BOOL CPicDlg::OnEraseBkgnd(CDC* pDC)
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

    //ֱ�Ӽ���ͼƬ�Ͳ���Ҫ��CDC��ͼ�ˣ���ȡ�ڴ���ʾ�豸�������
    HDC picHDC = ::CreateCompatibleDC(pDC->m_hDC);
    //�������ͼ��ֱ��ѡ��ͼƬ���豸�������
    ::SelectObject(picHDC, picHBITMAP);
    //CImage img;
    //img.Attach(picHBITMAP);
    //img.Save("D:\\232.bmp");
    ::TransparentBlt(pDC->m_hDC, 0, 0, width, height, picHDC, 0, 0, width, height, SRCCOPY);
    ::ReleaseDC(m_hWnd, picHDC);
    Invalidate(FALSE);
    return FALSE;
    return CDialogEx::OnEraseBkgnd(pDC);
}


void CPicDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    Invalidate(FALSE);
    // TODO:  �ڴ˴������Ϣ����������
}
