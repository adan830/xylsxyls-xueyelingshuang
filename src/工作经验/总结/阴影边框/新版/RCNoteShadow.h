/*****************************************************************************
*  ��Ȩ���У�C��2008-2017���Ϻ�������������Ƽ����޹�˾                      *
*  ��������Ȩ����                                                            *
******************************************************************************
*  ���� : ���                                                               *
*  �汾 : 1.0                                                                *
*****************************************************************************/

#ifndef __RCNoteShadow_h_
#define __RCNoteShadow_h_ 1

#include "ui/common/RCWndShadow.h"

BEGIN_NAMESPACE_RC

/* ע�͵�����Ӱ
*/
class RCNoteShadow :
    public RCWndShadow
{
    /* �����м�����
    @param [in] layoutRect һ����ͼƬ��С
    @param [in] destMargin Ŀ����Ӱ����
    @param [in] pImage ͼƬָ��
    @param [in] pLayout Gdiplus����ָ��
    @param [in] rcImage ͼƬ��С
    @param [in] margin ��Ӱ��С
    */
    virtual void PaintCenter(const RECT& layoutRect, const RECT& destMargin, Gdiplus::Image* pImage, Gdiplus::Graphics* pLayout, const RECT& rcImage, const RECT& margin);
};

END_NAMESPACE_RC

#endif //__RCNoteShadow_h_