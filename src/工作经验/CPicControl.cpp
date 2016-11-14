#include "stdafx.h"
#include "CPicControl.h"

void CPicControl::init(CRect rcRect,UINT nID,CWnd* pParentWnd,list<CString> listPath,list<CRect> listPicRect,list<CRect> listRcRect,list<list<CString>> listlistText,list<list<COLORREF>> listlistColor){
	Create("",/////��ť����ʾ���ı�  
		WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,///���û���ƶ�WS_VISIBLE��Ҫ����ShowWindow������ʾ����  WS_CHILD|
		rcRect,/////���Ͻǵ�����(0��0),����Ϊ100��100  
		pParentWnd,//������  
		nID);
	
	this->bDown = 0;
	this->ninit = 0;
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
	
	DrawPicCDC(*(this->listPath.begin()),*(this->listPicRect.begin()),*(this->listRcRect.begin()));
	DrawTextCDC(*(this->listlistText.begin()),*(this->listlistColor.begin()));
	if(ninit == 2) ninit = 1;
	return;
}

int i = 0;

void CPicControl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ninit = 1;
	CString strDownPath = *(++listPath.begin());
	//����ǰ���״̬���Ұ���״̬·����Ϊ����ô��ʾ����״̬�����������ʾ����״̬
	if(bDown == 1 && strDownPath != ""){
		DrawPicCDC(*(++listPath.begin()),*(++listPicRect.begin()),*(++listRcRect.begin()));
	}
	else if(*(listPath.begin()) != ""){
		DrawPicCDC(*(listPath.begin()),*(listPicRect.begin()),*(listRcRect.begin()));
	}

	//�����������Ҫ��ʾ
	if(bDown == 1 && (++listlistText.begin())->size() != 0){
		DrawTextCDC(*(++listlistText.begin()),*(++listlistColor.begin()));
	}
	else{
		DrawTextCDC(*(listlistText.begin()),*(listlistColor.begin()));
	}
	ninit = 1;
	// TODO:  ������Ĵ����Ի���ָ����
}

void CPicControl::DrawPicCDC(CString strPath,CRect picRect,CRect rcRect){
	//return;
	if(ninit == 0) return;
	else if(ninit == 1){
		if(this->strPath == strPath && this->picRect == picRect && this->rcRect == rcRect) return;
	}
	if(strPath == "") return;
	ninit = 2;
	this->strPath = strPath;
	this->picRect = picRect;
	this->rcRect = rcRect;

	CStringW strWide = CT2CW(strPath);

	HBITMAP hBitmap;
	hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(),strPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	CBitmap cBitmap;
	cBitmap.Attach(hBitmap);
	BITMAP bitmap;
	cBitmap.GetBitmap(&bitmap);
	int nWidth = bitmap.bmWidth;
	int nHeight = bitmap.bmHeight;

	CRect rcRectTemp;
	if(rcRect == CRect(0,0,0,0)) this->GetClientRect(&rcRectTemp);
	else rcRectTemp = rcRect;
	CRect picRectTemp;
	if(picRect == CRect(0,0,0,0)){
		picRectTemp.right = nWidth;
		picRectTemp.bottom = nHeight;
	}
	else picRectTemp = picRect;

	CDC ImageCDC;
	ImageCDC.CreateCompatibleDC(NULL);
	ImageCDC.SelectObject(&cBitmap);

	GetDC()->StretchBlt(rcRectTemp.left,rcRectTemp.top,rcRectTemp.Width(),rcRectTemp.Height(),&ImageCDC,
		picRectTemp.left,picRectTemp.top,picRectTemp.Width(),picRectTemp.Height(),SRCCOPY);

	DeleteObject(hBitmap);
	cBitmap.DeleteObject();
	//ɾ��λͼ
	DeleteObject(&bitmap);
	/*
	if(strPath == "") return;
	//������ʱ�豸������
	CDC* pDC = this->GetDC();
	CDC ImageCDC;
	ImageCDC.CreateCompatibleDC(pDC);

	//����ͼƬ��bitmap��ȡ���
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), strPath, IMAGE_BITMAP, 0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	CBitmap cBitmap;
	cBitmap.Attach(hBitmap);
	BITMAP bitmap;
	cBitmap.GetBitmap(&bitmap);
	int nWidth = bitmap.bmWidth;
	int nHeight = bitmap.bmHeight;

	//��ʱ�豸������ѡ��CBitmap
	CBitmap* pOld = ImageCDC.SelectObject(&cBitmap);

	CRect rcRectTemp;
	if(rcRect == CRect(0,0,0,0)) this->GetClientRect(&rcRectTemp);
	else rcRectTemp = rcRect;
	CRect picRectTemp;
	if(picRect == CRect(0,0,0,0)){
		picRectTemp.right = nWidth;
		picRectTemp.bottom = nHeight;
	}
	else picRectTemp = picRect;

	//ǰ����������꣬������ͼƬ����
	pDC->StretchBlt(rcRectTemp.left,rcRectTemp.top,rcRectTemp.Width(),rcRectTemp.Height(),&ImageCDC,picRectTemp.left,picRectTemp.top,picRectTemp.Width(),picRectTemp.Height(),SRCCOPY);

	DeleteObject(hBitmap);
	cBitmap.DeleteObject();
	//�ָ���ʱDC��λͼ
	ImageCDC.SelectObject(pOld);
	//ɾ��λͼ
	DeleteObject(&bitmap);
	//ɾ����̨DC
	ImageCDC.DeleteDC();
	*/
}




void MyDrawText(Gdiplus::Graphics *pGDI, WCHAR* szText, Gdiplus::PointF& pt,Gdiplus::Font* pFont,SolidBrush* pTextColor, BOOL IsGround, SolidBrush* pGroundColor, RectF &rc)
{
	if(szText[0] == 0) return;

	INT len = (INT)wcslen(szText);   

	pGDI->MeasureString(szText, len, pFont, pt, &rc);
	//while(res != 0)
	//{
	//	res = pGDI->MeasureString(szText, len, pFont, pt, &rc);
	//}
	if(IsGround)
	{           
		pGDI->FillRectangle(pGroundColor, rc);//gdi��ͼʧ�����»�
		
	}
	int x = pGDI->DrawString(szText, len, pFont, pt, pTextColor);
}

void CPicControl::DrawTextCDC(list<CString> listText,list<COLORREF> listColor){
	//return;
	/*
	Gdiplus::Graphics pGDIBmp(GetDC()->m_hDC);

	Gdiplus::RectF rc;                // ��������
	rc.X = 0;
	rc.Y = 0;
	rc.Width = 100;
	rc.Height = 100;
	WCHAR szLineText[256];    // ��ӡ��
	wsprintfW(szLineText, L"�ı�1111111111111111");
	Gdiplus::PointF ptStar(0,0); // ��ʼ��
	//pGDIBmp->DrawString(L"");

	LOGFONTW lfont;  
	memset( &lfont, 0, sizeof(lfont) );  

	lfont.lfHeight = -15, //   nHeight   ע��ʹ�ø�ֵ����ʾcharacter height,  ��ֵ��ʾ cell height  
		lfont.lfWidth  = 0,  //   nWidth  
		//0,     //   nEscapement  
		//0,     //   nOrientation  
		lfont.lfWeight      = FW_NORMAL,  //nWeight  
		lfont.lfItalic      = FALSE,      //bItalic  
		lfont.lfUnderline   = FALSE,   //   bUnderline  
		lfont.lfStrikeOut   = 0,         //   cStrikeOut  
		lfont.lfCharSet     = DEFAULT_CHARSET,   //   nCharSet  
		lfont.lfOutPrecision    = OUT_DEFAULT_PRECIS,//   nOutPrecision  
		lfont.lfClipPrecision   = CLIP_DEFAULT_PRECIS,  //   nClipPrecision  
		lfont.lfQuality         = CLEARTYPE_QUALITY,      //   nQuality  
		lfont.lfPitchAndFamily  = DEFAULT_PITCH | FF_SWISS,//   nPitchAndFamily  
		wcscpy_s( lfont.lfFaceName, (L"΢���ź�") );  //   lpszFacename  

	//HDC hHDC = ::GetDC(NULL);  
	Gdiplus::Font hf( GetDC()->m_hDC, &lfont );  
	//::ReleaseDC( NULL, hHDC );

	SolidBrush textBrush(Gdiplus::Color(255,0,0));
	SolidBrush bkBrush(Gdiplus::Color(100,0,0));
	*/
	//System.DrawString(L"123456",&hf,&bkBrush,ptStar);
	//MyDrawText(&pGDIBmp/*gdi����*/,szLineText/*�ı�*/,
	//	ptStar/*��ʼ��*/, &hf/*����*/, &textBrush/*������ɫ*/,
	//	1/*�Ƿ񱳾�*/, &bkBrush/*������ɫ*/, rc/*������ı���������*/);
	
	if(ninit == 0) return;
	else if(ninit == 1){
		//��¼��һ�β����������ͬ��ֱ�ӷ���
		if(prelistText == listText && prelistColor == listColor) return;
	}
	ninit = 2;
	prelistText = listText;
	prelistColor = listColor;

	if(listColor.size() < listText.size()){
		int i = listColor.size();
		while(i++ != listText.size()) listColor.push_back(COLORREF());
	}

	Gdiplus::Graphics bmpGraphics(GetDC()->m_hDC);
	//bmpGraphics.Clear(Color::White);
	//��Ϊ��������ʾ����������Ϊ��λ�ȶ���һ��������
	CString strOneLine;
	float xx = 0.0f;
	float yy = 0.0f;

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
		Gdiplus::Font font(&fontFamily,FontSize);
		
		//��ʽ
		StringFormat stringFormat;
		//stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
		//stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		//������ɫ
		SolidBrush TextBrush(Gdiplus::Color(GetRValue(*itlistColor),GetGValue(*itlistColor),GetBValue(*itlistColor)));
		Gdiplus::PointF origin(xx,yy);

		CRect rcRectTemp;
		this->GetClientRect(&rcRectTemp);
		RectF rectf(0.0f,0.0f,(float)rcRectTemp.Width(),(float)rcRectTemp.Height());
		//д����
		if(bWrap == 1) bmpGraphics.DrawString(strWide,-1,&font,rectf,&stringFormat,&TextBrush);
		else bmpGraphics.DrawString(strWide,-1,&font,origin,&TextBrush);
		
		//ת��HFONT
		LOGFONTA logfont;
		font.GetLogFontA(&bmpGraphics,&logfont);

		CFont cFont;
		cFont.CreateFontIndirect(&logfont);
		

		//��������һ���������ȡ���ȵ�ʱ�����Ч��ֱ��ʹ��GetDC()->m_hDC����
		HDC hDC = GetDC()->m_hDC;
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
			xx = 0;
			yy = yy + size.cy;
		}
		else{
			xx = (float)nOneLine;
			//y = y + size.cy;
		}
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
	
	DrawPicCDC(*(listPath.begin()),*(listPicRect.begin()),*(listRcRect.begin()));
	DrawTextCDC(*(listlistText.begin()),*(listlistColor.begin()));
	if(ninit == 2) ninit = 1;
	CButton::OnMouseLeave();
}


void CPicControl::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString strDownPath = *(++listPath.begin());
	CString strMovePath = *(++++listPath.begin());
	//����ǰ���״̬���Ұ���״̬·����Ϊ������ʾ����״̬
	if(bDown == 1 && strDownPath != ""){
		DrawPicCDC(*(++listPath.begin()),*(++listPicRect.begin()),*(++listRcRect.begin()));
		
	}
	//����ǵ���״̬�����ƶ�״̬·����Ϊ������ʾ�ƶ�״̬
	else if(bDown == 0 && strMovePath != ""){
		DrawPicCDC(*(++++listPath.begin()),*(++++listPicRect.begin()),*(++++listRcRect.begin()));
		
	}
	//����ȫ����ʾ����״̬
	else{
		DrawPicCDC(*(listPath.begin()),*(listPicRect.begin()),*(listRcRect.begin()));
	}

	//����ǰ���״̬���Ұ���״̬·����Ϊ������ʾ����״̬
	if(bDown == 1 && (++listlistText.begin())->size() != 0){
		DrawTextCDC(*(++listlistText.begin()),*(++listlistColor.begin()));
	}
	//����ǵ���״̬�����ƶ�״̬·����Ϊ������ʾ�ƶ�״̬
	else if(bDown == 0 && (++++listlistText.begin())->size() != 0){
		DrawTextCDC(*(++++listlistText.begin()),*(++++listlistColor.begin()));
	}
	//����ȫ����ʾ����״̬
	else{
		DrawTextCDC(*(listlistText.begin()),*(listlistColor.begin()));
	}
	if(ninit == 2) ninit = 1;
	CButton::OnMouseHover(nFlags, point);
}


void CPicControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bDown = 0;
	CWnd::OnLButtonUp(nFlags, point);
}
