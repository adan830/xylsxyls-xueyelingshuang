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
	list<CString> prelistText;
	list<COLORREF> prelistColor;

	bool bDown;
	//0��ʾ��ʼ����1��ʾ�����麯������Ҫ������2��ʾ�ոĹ���ֱ���ػ�
	int nInit;
	bool bifHasPaintMessage;
	//list��˳���ǳ��水���ƶ�
	void init(CRect rcRect,UINT nID,CWnd* pParentWnd,
		list<CString> listPath = list<CString>(),list<CRect> listPicRect = list<CRect>(),list<CRect> listRcRect = list<CRect>(),
		list<list<CString>> listlistText = list<list<CString>>(),list<list<COLORREF>> listlistColor = list<list<COLORREF>>());
	//�ı�ͼƬ
	void ChangePicAndText(list<CString> listPath = list<CString>(),list<CRect> listPicRect = list<CRect>(),list<CRect> listRcRect = list<CRect>(),
		list<list<CString>> listlistText = list<list<CString>>(),list<list<COLORREF>> listlistColor = list<list<COLORREF>>());
	//Ĭ��ȫbutton�����ȫͼƬ
	void DrawPicCDC(CString strPath,CRect picRect = CRect(0,0,0,0),CRect rcRect = CRect(0,0,0,0));
	//д����
	void DrawTextCDC(list<CString> listText,list<COLORREF> listColor);
	//����
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};