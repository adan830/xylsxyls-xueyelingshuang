#pragma once
#include <afxwin.h>
#include <list>
#include <gdiplusgraphics.h>
#include <gdiplus.h>
#include <wingdi.h>
using namespace Gdiplus;
using namespace std;

#define DlgOnPaintMessage(pPicControl) \
	if(pPicControl->nInit >= 0){\
	pPicControl->bifHasPaintMessage = 1;\
	pPicControl->Invalidate();\
	pPicControl->RedrawWindow();\
	}


class CPicControl : public CButton{
public:
	CPicControl();
	CString FontForm;
	int FontSize;

	list<CString> listPath;
	list<CRect> listPicRect;
	list<CRect> listRcRect;
	list<list<CString>> listlistText;
	list<list<COLORREF>> listlistColor;

	CString strPath;
	CRect picRect;
	CRect rcRect;
	CRect rcRectInClient;
	list<CString> prelistText;
	list<COLORREF> prelistColor;

	bool bDown;
	//0��ʾ��ʼ����1��ʾ�����麯������Ҫ������2��ʾ�ոĹ���ֱ���ػ�
	int nInit;
	bool bifHasPaintMessage;

	//�ؼ��ͻ��˴�С
	CRect rcClient;

	//list��˳���ǳ��水���ƶ�
	void init(CRect rcRect,UINT nID,CWnd* pParentWnd,
		list<CString> listPath = list<CString>(),list<CRect> listPicRect = list<CRect>(),list<CRect> listRcRect = list<CRect>(),
		list<list<CString>> listlistText = list<list<CString>>(),list<list<COLORREF>> listlistColor = list<list<COLORREF>>());
	//�ı�ͼƬ
	void ChangePicAndText(list<CString> listPath = list<CString>(),list<CRect> listPicRect = list<CRect>(),list<CRect> listRcRect = list<CRect>(),
		list<list<CString>> listlistText = list<list<CString>>(),list<list<COLORREF>> listlistColor = list<list<COLORREF>>());
	//Ĭ��ȫbutton�����ȫͼƬ
	void DrawPicCDC(Bitmap* pmemBitmap,CString strPath,CRect picRect = CRect(0,0,0,0),CRect rcRect = CRect(0,0,0,0),bool ifOnPaint = 0);
	//д����
	void DrawTextCDC(Bitmap* pmemBitmap,list<CString> listText,list<COLORREF> listColor,bool ifOnPaint = 0);
	//����
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//��ͼ������
	void DrawPicAndText(Bitmap* pmemBitmap);
	//��һ��ͼ
	static void DrawOnePic(Bitmap* pmemBitmap,CString strPath,CRect picRect,CRect rcRect);
	//��ͼ
	static void Draw(HDC hdc,Bitmap* pmemBitmap,int x,int y);
	//��ջ���
	void ClearBitmap(Bitmap* pmemBitmap);
	//��Dlg��OnPaint��ִ��
	static void DrawInDlgOnPaint(HDC hdc,CString strPath,CRect picRect,CRect rcRect,int x,...);


	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};