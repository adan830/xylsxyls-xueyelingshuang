#ifndef CONTROLSELF_H__
#define CONTROLSELF_H__
//#pragma once
#include "ControlBase.h"

template <class QBase>
class ControlSelf : virtual public ControlBase < QBase >
{
public:
	/** ���������ΪԲ�ǣ�����Բ�ǰ뾶��ֻ�м���߿�Ż���Բ��
	@param [in] radius Բ�ǰ뾶
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderRadius(int32_t radius, bool rePaint = false);

	/** ���ñ߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderWidth(int32_t width, bool rePaint = false);
};

#include "ControlSelf.inl"

#endif