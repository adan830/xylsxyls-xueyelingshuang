/******************************************************************************
*  ��Ȩ���У�C��2008-2015���Ϻ�������������Ƽ����޹�˾                      *
*  ��������Ȩ����                                                            *
******************************************************************************
*  ���� : �ſ���
*  �汾 : 1.0
*****************************************************************************/
/** �޸ļ�¼:
����       �汾    �޸���             �޸�����
--------------------------------------------------------------------------
******************************************************************************/

#ifndef __RCPdfEdit_h_
#define __RCPdfEdit_h_ 1

#include "base/RCDefs.h"
#include "wtl/RCWTLDefs.h"
#include "pdfapp/def/RCPdfWndIdDef.h"

BEGIN_NAMESPACE_RC
/** pdf��ʹ�õ�edit�༭�� ��ʵ����ԭ�򣬸ı䱳��ɫ��������ɫ��
*/
class RCPdfEdit:
    public CWindowImpl<RCPdfEdit, CEdit>
{
public:
    /** ���캯��
    */
    RCPdfEdit();

    /** ��������
    */
    ~RCPdfEdit();

    DECLARE_WND_SUPERCLASS(_T("RCPdfEdit"), WC_EDIT)
    BEGIN_MSG_MAP(RCEdit)
        MSG_WM_CHAR(OnChar)
        MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
        MSG_OCM_CTLCOLOREDIT(OnCtlColorEdit)
        MSG_OCM_CTLCOLORSTATIC(OnCtlColorEdit)
        MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
        MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
        MSG_WM_SIZE(OnSize)
    END_MSG_MAP()

public:

    /** ����͸����Edit��
    */
    HBRUSH OnCtlColorEdit(CDCHandle dc, CEdit edit);

    /** ��Ӧ����
    */
    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    /** ������Ϣ
    */
    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
    
    void OnSize(UINT nType, CSize size);
public:
    /* ��ʼ������
    */
    void Init();

    /** ����������ɫ
    @param [in] clr ��ɫ
    */
    void SetTextColor(COLORREF clr);

    /* ����������
    @param [in] wParam ��Ϣ��Ӧ����wParam
    @param [in] lParam ��Ϣ��Ӧ����lParam
    */
    void VScroll(WPARAM wParam, LPARAM lParam);

    /* �ı䴰�ڴ�С
    */
    void ChangeSize();

    /** �ı��������Ϣ
    @param [in] si ��������Ϣ�ṹ��
    @param [in] message ��������Ϣ��
    */
    void ChangeScrollInfo(SCROLLINFO& si, uint32_t message);

    /* ��ȡ���ڴ�С
    @return ���ش��ھ��δ�С
    */
    CRect GetClientCRectDPI();

    /* ��ȡ�ı���ǰ���߶�
    @return �����ı���ǰ���߶�
    */
    int32_t GetMaxLines();

private:
    /* ����������ϴ�����λ��
    */
    int32_t m_xOldPos;

    /* ����������ϴ�����λ��
    */
    int32_t m_yOldPos;

    /* ��������ǰ����λ��
    */
    int32_t m_pos;

    /** ����ˢ��
    */
    HBRUSH m_hBkBrush;

    /** ������ɫ
    */
    COLORREF m_bkgColor;

    /** ������ɫ
    */
    COLORREF m_textClr;

    /* ��������Ļ�����
    */
    HDC hCalcDC;

    /* �ָ�
    */
    int32_t textHeight;
};

END_NAMESPACE_RC

#endif