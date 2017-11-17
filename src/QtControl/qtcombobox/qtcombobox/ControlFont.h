#ifndef CONTROLFONT_H__
#define CONTROLFONT_H__
//#pragma once
#include "ControlBase.h"

template <class QBase>
class ControlFont : virtual public ControlBase < QBase >
{
public:
	/** ��������
	@param [in] fontName ������
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setFontFace(const QString& fontName, bool rePaint = false);

	/** ���������С
	@param [in] fontSize �����С
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setFontSize(int32_t fontSize, bool rePaint = false);
};

#include "ControlFont.inl"

#endif