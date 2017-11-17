#ifndef CONTROLITEM_H__
#define CONTROLITEM_H__
//#pragma once
#include "ControlBase.h"

template <class QBase>
class ControlItem : virtual public ControlBase < QBase >
{
public:
	/** ���ýڵ�߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemBorderWidth(int32_t width, bool rePaint = false);

	/** ���ýڵ�߶�
	@param [in] height �ڵ�߶�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemHeight(int32_t height, bool rePaint = false);

	/** �ڵ㵽���ڵ��ĸ���߾�
	@param [in] leftOrigin ���ƫ����
	@param [in] topOrigin �ϲ�ƫ����
	@param [in] rightOrigin �Ҳ�ƫ����
	@param [in] bottomOrigin �²�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemAroundOrigin(int32_t leftOrigin,
						     int32_t topOrigin,
						     int32_t rightOrigin,
						     int32_t bottomOrigin,
						     bool rePaint = false);
};

#include "ControlItem.inl"

#endif