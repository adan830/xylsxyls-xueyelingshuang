#include "stdafx.h"
#include "CPicControl.h"

CPicControl::CPicControl(){
	FontForm = "����";
	//#define FontForm "����"
	FontSize = 13;
	//#define FontSize 13
	this->nInit = -1;
}

void CPicControl::init(CRect rcRectInClient,UINT nID,CWnd* pParentWnd,list<CString> listPath,list<CRect> listPicRect,list<CRect> listRcRect,list<list<CString>> listlistText,list<list<COLORREF>> listlistColor){
	Create("",/////��ť����ʾ���ı�  
		WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,///���û���ƶ�WS_VISIBLE��Ҫ����ShowWindow������ʾ����  WS_CHILD|
		rcRectInClient,/////���Ͻǵ�����(0��0),����Ϊ100��100  
		pParentWnd,//������  
		nID);

	this->rcRectInClient = rcRectInClient;
	this->bDown = 0;
	this->nInit = 0;
	this->bifHasPaintMessage = 0;
	GetClientRect(&rcClient);
	ChangePicAndText(listPath,listPicRect,listRcRect,listlistText,listlistColor);
	return;
}

void CPicControl::ChangePicAndText(list<CString> listPath,list<CRect> listPicRect,list<CRect> listRcRect,list<list<CString>> listlistText,list<list<COLORREF>> listlistColor){
	this->listPath = listPath;
	this->listPicRect = listPicRect;
	this->listRcRect = listRcRect;
	this->listlistText = listlistText;
	this->listlistColor = listlistColor;

	if(listPath.size() < 3){
		int i = listPath.size();
		while(i++ != 3) this->listPath.push_back("");
	}
	if(listPicRect.size() < 3){
		int i = listPicRect.size();
		while(i++ != 3) this->listPicRect.push_back(CRect());
	}
	if(listRcRect.size() < 3){
		int i = listRcRect.size();
		while(i++ != 3) this->listRcRect.push_back(CRect());
	}
	if(listlistText.size() < 3){
		int i = listlistText.size();
		while(i++ != 3) this->listlistText.push_back(list<CString>());
	}
	if(listlistColor.size() < 3){
		int i = listlistColor.size();
		while(i++ != 3) this->listlistColor.push_back(list<COLORREF>());
	}

	//����Ҫ���ڴ�һ�Ż�����û���ⲽGDI+�޷���ͼ��������СӦ����ΪClient��С
	Bitmap memBitmap(rcClient.Width(),rcClient.Height());

	DrawPicCDC(&memBitmap,*(this->listPath.begin()),*(this->listPicRect.begin()),*(this->listRcRect.begin()));
	DrawTextCDC(&memBitmap,*(this->listlistText.begin()),*(this->listlistColor.begin()));
	Draw(GetDC()->m_hDC,&memBitmap,0,0);
	if(nInit == 2) nInit = 1;
	return;
}

void CPicControl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	nInit = 1;
	//����Ҫ���ڴ�һ�Ż�����û���ⲽGDI+�޷���ͼ��������СӦ����ΪClient��С
	Bitmap memBitmap(rcClient.Width(),rcClient.Height());
	DrawPicAndText(&memBitmap);
	Draw(GetDC()->m_hDC,&memBitmap,0,0);
	nInit = 1;
	// TODO:  ������Ĵ����Ի���ָ����
}

void CPicControl::ClearBitmap(Bitmap* pmemBitmap){
	Graphics emptyMemGraphics(pmemBitmap);
	SolidBrush brush(TRANSPARENT);
	emptyMemGraphics.FillRectangle(&brush,rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height());
}

void CPicControl::DrawInDlgOnPaint(HDC hdc,CString strPath,CRect picRect,CRect rcRect,int number,...){
	va_list parameterlist;
	va_start(parameterlist,number);
	if(picRect == CRect() && strPath != ""){
		CStringW strWide = CT2CW(strPath);
		Image image(strWide);
		picRect.SetRect(0,0,image.GetWidth(),image.GetHeight());
	}

	CPicControl* pPicControlFirst = NULL;
	if(number > 0 && rcRect == CRect()){
		//����пؼ�������ʾ��Ϊ��CRect��ô��ȡ�����ڵĴ�С
		pPicControlFirst = va_arg(parameterlist,CPicControl*);
		if(pPicControlFirst->nInit != -1) pPicControlFirst->GetParent()->GetClientRect(&rcRect);
	}
	Bitmap memBitmap(rcRect.Width(),rcRect.Height());
	//������
	if(strPath != "") DrawOnePic(&memBitmap,strPath,picRect,rcRect);
	//�����Ϊ�գ�˵��ȷʵ��ȡ����һ���ؼ������뻭�ڱ���֮��
	if(pPicControlFirst->nInit != -1){
		pPicControlFirst->DrawPicCDC(&memBitmap,*pPicControlFirst->listPath.begin(),
			*pPicControlFirst->listPicRect.begin(),pPicControlFirst->rcRectInClient,TRUE);
		pPicControlFirst->DrawTextCDC(&memBitmap,*pPicControlFirst->listlistText.begin(),
			*pPicControlFirst->listlistColor.begin(),TRUE);
		number--;
	}
	//��ʼ�����߻�ʣ���
	while(number-- != 0){
		CPicControl* pPicControl = va_arg(parameterlist,CPicControl*);
		if(pPicControl->nInit != -1){
			pPicControl->DrawPicCDC(&memBitmap,*pPicControl->listPath.begin(),*pPicControl->listPicRect.begin(),pPicControl->rcRectInClient,TRUE);
			pPicControl->DrawTextCDC(&memBitmap,*pPicControl->listlistText.begin(),*pPicControl->listlistColor.begin(),TRUE);
		}
	}
	Draw(hdc,&memBitmap,0,0);
	va_end(parameterlist);
	return;
}

void CPicControl::DrawPicAndText(Bitmap* pmemBitmap){

	CString strDownPath = *(++listPath.begin());
	//����ǰ���״̬���Ұ���״̬·����Ϊ����ô��ʾ����״̬�����������ʾ����״̬
	if(bDown == 1 && strDownPath != ""){
		DrawPicCDC(pmemBitmap,*(++listPath.begin()),*(++listPicRect.begin()),*(++listRcRect.begin()));
	}
	else if(*(listPath.begin()) != ""){
		DrawPicCDC(pmemBitmap,*(listPath.begin()),*(listPicRect.begin()),*(listRcRect.begin()));
	}

	//�����������Ҫ��ʾ
	if(bDown == 1 && (++listlistText.begin())->size() != 0){
		DrawTextCDC(pmemBitmap,*(++listlistText.begin()),*(++listlistColor.begin()));
	}
	else{
		DrawTextCDC(pmemBitmap,*(listlistText.begin()),*(listlistColor.begin()));
	}
	return;
}

void CPicControl::DrawOnePic(Bitmap* pmemBitmap,CString strPath,CRect picRect,CRect rcRect){
	//�������ͨ��memGraphics��memBitmap�ϻ��ƶ��ͼԪ
	Graphics memGraphics(pmemBitmap);

	CStringW strWide = CT2CW(strPath);
	Image image(strWide);
	memGraphics.DrawImage(&image,RectF((float)rcRect.left,(float)rcRect.top,(float)rcRect.Width(),(float)rcRect.Height()),
		Gdiplus::REAL(picRect == CRect() ? 0 : picRect.left),
		Gdiplus::REAL(picRect == CRect() ? 0 : picRect.top),
		Gdiplus::REAL(picRect == CRect() ? image.GetWidth() : picRect.Width()),
		Gdiplus::REAL(picRect == CRect() ? image.GetHeight() : picRect.Height()),Gdiplus::UnitPixel);
}

void CPicControl::Draw(HDC hdc,Bitmap* pmemBitmap,int x,int y){
	Graphics gr(hdc);
	gr.DrawImage(pmemBitmap,x,y);
	return;
}

void CPicControl::DrawPicCDC(Bitmap* pmemBitmap,CString strPath,CRect picRect,CRect rcRect,bool ifOnPaint){
	//�������OnPaint�г���·��ȫ���������
	if(ifOnPaint){
		if(strPath == "") return;
		goto begin;
	}
	if(nInit == 0) return;
	else if(nInit == 1){
		if(this->strPath == strPath && this->picRect == picRect && this->rcRect == rcRect) return;
	}
	if(strPath == "") return;
	nInit = 2;

begin:
	//OnPaint�л���λ�û���ƫ��
	if(ifOnPaint == 1){
		this->rcRect = CRect(rcRect.left - rcRectInClient.left,rcRect.top - rcRectInClient.top,
			rcRect.Width() - rcRectInClient.Width(),rcRect.Height() - rcRectInClient.Height());
	}
	else this->rcRect = rcRect;
	this->strPath = strPath;
	this->picRect = picRect;


	DrawOnePic(pmemBitmap,strPath,picRect,rcRect == CRect() ? rcClient : rcRect);
	return;
}

void CPicControl::DrawTextCDC(Bitmap* pmemBitmap,list<CString> listText,list<COLORREF> listColor,bool ifOnPaint){
	//�������OnPaint��ȫ���������
	if(ifOnPaint){
		goto begin;
	}
	if(nInit == 0) return;
	else if(nInit == 1){
		//��¼��һ�β����������ͬ��ֱ�ӷ���
		if(prelistText == listText && prelistColor == listColor) return;
	}
	nInit = 2;

begin:
	//���û������Ҫ������ֱ�ӷ���
	if(listText.size() == 0) return;
	prelistText = listText;
	prelistColor = listColor;

	if(listColor.size() < listText.size()){
		int i = listColor.size();
		while(i++ != listText.size()) listColor.push_back(COLORREF());
	}

	Gdiplus::Graphics TextGraphics(pmemBitmap);
	
	//����ȥë�ߣ���͸����Ĭ�ϱ��������ֱ�Ե���к�ɫ
	TextGraphics.SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
	
	CString strOneLine;
	float xx = 0.0f;
	float yy = 0.0f;
	if(ifOnPaint == 1){
		xx = xx + rcRectInClient.left;
		yy = yy + rcRectInClient.top;
	}
	auto itlistText = listText.begin();
	if(itlistText != listText.end()) strOneLine = *itlistText;
	auto itlistColor = listColor.begin();
	while(itlistText != listText.end()){
		bool bWrap = 0;
		CStringW strWide;
		//ʹ�÷��������
		//����
		if((*itlistText)[0] == '#'){
			bWrap = 1;
			strWide = CT2CW(itlistText->Mid(1,itlistText->GetLength() - 1));
		}
		else strWide = CT2CW(*itlistText);
		//����
		CStringW strFontForm = CT2CW(FontForm);
		FontFamily fontFamily(strFontForm);
		Gdiplus::Font font(&fontFamily,(float)FontSize);
		//��ʽ
		StringFormat stringFormat;
		//stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
		//stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		//������ɫ
		SolidBrush TextBrush(Gdiplus::Color(GetRValue(*itlistColor),GetGValue(*itlistColor),GetBValue(*itlistColor)));
		Gdiplus::PointF origin(xx,yy);

		CRect rcRectTemp;
		this->GetClientRect(&rcRectTemp);
		RectF rectf(xx,yy,(float)rcRectTemp.Width(),(float)rcRectTemp.Height());
		//д����
		if(bWrap == 1) TextGraphics.DrawString(strWide,-1,&font,rectf,&stringFormat,&TextBrush);
		else TextGraphics.DrawString(strWide,-1,&font,origin,&TextBrush);
		//ת��HFONT
		LOGFONTA logfont;
		font.GetLogFontA(&TextGraphics,&logfont);
		CFont cFont;
		cFont.CreateFontIndirect(&logfont);
		//���Ҫ��ȡ����GetDC()->m_hDC����������һ���������ȡ���ȵ�ʱ�����Ч��ֱ��ʹ��GetDC()->m_hDC����
		HDC hDC = TextGraphics.GetHDC();
		//hFont = CreateFont(logfont.lfHeight,logfont.lfWidth,0,0,FW_THIN,true,false,false,
		//	CHINESEBIG5_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,FontForm);
		SelectObject(hDC,cFont);

		CString strText = *itlistText;
		//��ȡһ���ַ����ĳ���
		SIZE size;
		GetTextExtentPoint32(hDC,strOneLine,strlen(strOneLine),&size);
		int nOneLine = size.cx;
		//������һ���ַ������뻺����
		itlistText++;
		if(itlistText != listText.end()) strOneLine = strOneLine + *itlistText;
		GetTextExtentPoint32(hDC,strOneLine,strlen(strOneLine),&size);
		int nOneLineAdd = size.cx;
		if(nOneLineAdd >= rcRectTemp.Width() || (strText.GetLength() >= 1 && strText[strText.GetLength() - 1] == '\n')){
			if(itlistText != listText.end()) strOneLine = *itlistText;
			if(ifOnPaint == 1) xx = (float)rcRectInClient.left;
			else xx = 0;
			yy = yy + size.cy;
		}
		else{
			if(ifOnPaint == 1) xx = (float)nOneLine + rcRectInClient.left;
			else xx = (float)nOneLine;
		}
		//�����ж�Ӧ�ͷŷ�������ObjectBusy���ѻ�ȡ�������ѭ����Ҳ����
		TextGraphics.ReleaseHDC(hDC);
		itlistColor++;
	}
	return;
}

BEGIN_MESSAGE_MAP(CPicControl, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CPicControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE | TME_HOVER;//Ҫ��������Ϣ
	tme.hwndTrack = this->m_hWnd;
	tme.dwHoverTime = 10;// ������˲��������޷�����mouseHover

	//MOUSELEAVE|MOUSEHOVER��Ϣ�ɴ˺�������
	::_TrackMouseEvent(&tme);

	CButton::OnMouseMove(nFlags, point);
}


void CPicControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bDown = 1;
	CButton::OnLButtonDown(nFlags, point);
}


void CPicControl::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//����Ҫ���ڴ�һ�Ż�����û���ⲽGDI+�޷���ͼ��������СӦ����ΪClient��С
	Bitmap memBitmap(rcClient.Width(),rcClient.Height());


	DrawPicCDC(&memBitmap,*(listPath.begin()),*(listPicRect.begin()),*(listRcRect.begin()));
	DrawTextCDC(&memBitmap,*(listlistText.begin()),*(listlistColor.begin()));
	Draw(GetDC()->m_hDC,&memBitmap,0,0);
	if(nInit == 2) nInit = 1;
	CButton::OnMouseLeave();
}


void CPicControl::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//����Ҫ���ڴ�һ�Ż�����û���ⲽGDI+�޷���ͼ��������СӦ����ΪClient��С
	Bitmap memBitmap(rcClient.Width(),rcClient.Height());

	CString strDownPath = *(++listPath.begin());
	CString strMovePath = *(++++listPath.begin());
	//����ǰ���״̬���Ұ���״̬·����Ϊ������ʾ����״̬
	if(bDown == 1 && strDownPath != ""){
		DrawPicCDC(&memBitmap,*(++listPath.begin()),*(++listPicRect.begin()),*(++listRcRect.begin()));

	}
	//����ǵ���״̬�����ƶ�״̬·����Ϊ������ʾ�ƶ�״̬
	else if(bDown == 0 && strMovePath != ""){
		DrawPicCDC(&memBitmap,*(++++listPath.begin()),*(++++listPicRect.begin()),*(++++listRcRect.begin()));

	}
	//����ȫ����ʾ����״̬
	else{
		DrawPicCDC(&memBitmap,*(listPath.begin()),*(listPicRect.begin()),*(listRcRect.begin()));
	}

	//����ǰ���״̬���Ұ���״̬·����Ϊ������ʾ����״̬
	if(bDown == 1 && (++listlistText.begin())->size() != 0){
		DrawTextCDC(&memBitmap,*(++listlistText.begin()),*(++listlistColor.begin()));
	}
	//����ǵ���״̬�����ƶ�״̬·����Ϊ������ʾ�ƶ�״̬
	else if(bDown == 0 && (++++listlistText.begin())->size() != 0){
		DrawTextCDC(&memBitmap,*(++++listlistText.begin()),*(++++listlistColor.begin()));
	}
	//����ȫ����ʾ����״̬
	else{
		DrawTextCDC(&memBitmap,*(listlistText.begin()),*(listlistColor.begin()));
	}
	Draw(GetDC()->m_hDC,&memBitmap,0,0);
	if(nInit == 2) nInit = 1;
	CButton::OnMouseHover(nFlags, point);
}


void CPicControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bDown = 0;
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CPicControl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CButton::OnEraseBkgnd(pDC);
}