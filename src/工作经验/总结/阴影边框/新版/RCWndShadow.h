/******************************************************************************
 *  ��Ȩ���У�C��2008-2014���Ϻ�������������Ƽ��ɷ����޹�˾                  *
 *  ��������Ȩ����                                                            *
 ******************************************************************************
 *  ���� : �ſ���
 *  �汾 : 1.0
 *****************************************************************************/
/** �޸ļ�¼:
      ����       �汾    �޸���             �޸�����
    --------------------------------------------------------------------------
******************************************************************************/

#ifndef __RCWndShadow_h_
#define __RCWndShadow_h_ 1

#pragma warning(push)
#pragma warning(disable:4786)

#include "base/RCString.h"
#include "base/RCSmartPtr.h"
#include <map>
#include <comdef.h>
#include <gdiplus.h>
#pragma warning(pop) 

//���´�����Ϣ
#define WM_MY_SHADOW_UPDATE WM_USER +10011
BEGIN_NAMESPACE_RC
class RCWndShadow
{
public:
    /** ���캯��
    */
    RCWndShadow(void);

    /** ��������
    */
    virtual ~RCWndShadow(void);

protected:

    // Instance handle, used to register window class and create window 
    static HINSTANCE s_hInstance;

#pragma warning(push)
#pragma warning(disable:4786)
    // Parent HWND and CWndShadow object pares, in order to find CWndShadow in ParentProc()
    static std::map<HWND, RCWndShadow *> s_Shadowmap;
#pragma warning(pop) 

    // �㴰�� window APIs
    typedef BOOL (WINAPI *pfnUpdateLayeredWindow)(HWND hWnd, HDC hdcDst, POINT *pptDst,
        SIZE *psize, HDC hdcSrc, POINT *pptSrc, COLORREF crKey,
        BLENDFUNCTION *pblend, DWORD dwFlags);
    static pfnUpdateLayeredWindow s_UpdateLayeredWindow;

    LONG m_OriParentProc;    // Original WndProc of parent window

    enum ShadowStatus
    {
        SS_ENABLED = 1,    // Shadow is enabled, if not, the following one is always false
        SS_VISABLE = 1 << 1,    // Shadow window is visible
        SS_PARENTVISIBLE = 1<< 2,    // Parent window is visible, if not, the above one is always false
        SS_DISABLEDBYAERO = 1 << 3    // Shadow is enabled, but do not show because areo is enabled
    };
    BYTE m_Status;

    // Set this to true if the shadow should not be update until next WM_PAINT is received
    bool m_bUpdate;

    //��ӰԭͼƬ
    RCScopedPtr<Gdiplus::Bitmap> m_spShadowImage;

    //��Ӱ����
    RECT m_margin;
    
    //����Բ�ǰ뾶
    int m_nRadius;

    //��Ӱ�Ի��򱳾�ͼ
    HBITMAP m_hLayoutBmp;

    /** �ϴδ��ڴ�С
    */
    POINT m_lastWndSize;

    /** ��ǰ���¾�������
    */
    RECT m_newRect;

    /** ��Ӱ���ھ��
    */
    HWND m_hWnd;
public:
    static bool Initialize(HINSTANCE hInstance);

    void Create(HWND hParentWnd);

    bool SetShadowMargin(int nLeft, int nRight, int nTop, int nBottom, int nRadius);
    bool SetShadowBitmap(Gdiplus::Bitmap* shadowImage);

    /** ��ȡ��Ӱ���ھ��
    */
    HWND GetShadowWnd();

    /** �ƶ���Ӱ����
    */
    void MoveShadowWndPos(HWND hWnd, POINT pt);

    void EnableShadow(bool bEnable);
    // Show or hide the shadow, depending on the enabled status stored in m_Status
    void Show(HWND hParent);

    //�Ƿ�֧��ë����Ч��
    static bool IsCompositionEnabled();
protected:
    /** ��Ӱ���ڸ����ڹ��̴�����
    */
    static LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    /** ��Ӱ���ڴ��ڹ��̴�����
    */
    static LRESULT CALLBACK SelfProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    //check fullscreen mode for hide shadow window
    static bool CheckFullScreenMode(HWND parentHwnd, HWND hwnd);
    // Redraw, resize and move the shadow
    // called when window resized or shadow properties changed, but not only moved without resizing
    void Update();

    /** ������Ӱ����
    */
    bool MakeBitmapShadow();

    /** ���ƾŹ���
    */
    void DrawImageSquared(Gdiplus::Graphics* pLayout, Gdiplus::Image* pImage, const RECT& margin, const RECT& layOutWndRect, const RECT& rcImage);

    /* �����м�����
    @param [in] layoutRect һ����ͼƬ��С
    @param [in] destMargin Ŀ����Ӱ����
    @param [in] pImage ͼƬָ��
    @param [in] pLayout Gdiplus����ָ��
    @param [in] rcImage ͼƬ��С
    @param [in] margin ��Ӱ��С
    */
    virtual void PaintCenter(const RECT& layoutRect, const RECT& destMargin, Gdiplus::Image* pImage, Gdiplus::Graphics* pLayout, const RECT& rcImage, const RECT& margin);

    /** ��ʾ��Ӱ����
    */
    void ShowLayoutWindow();
};

END_NAMESPACE_RC
#endif //__RCWndShadow_h_