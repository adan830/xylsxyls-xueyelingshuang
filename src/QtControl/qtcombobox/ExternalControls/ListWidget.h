#pragma once
#include <QtWidgets/QListWidget>
#include <stdint.h>
#include "ControlFont.h"
#include "ControlItem.h"
#include "ControlSelf.h"
#include "ControlShow.h"
#include "ControlBorder.h"
#include "ControlBackground.h"

class ListWidget :
	public ControlShow < QListWidget >,
	public ControlFont < QListWidget >,
	public ControlItem < QListWidget >,
	public ControlSelf < QListWidget >,
	public ControlBorderForNormal < QListWidget >,
	public ControlBackgroundForNormal < QListWidget >,
	public ControlItemBorderForNormalHoverDisabled < QListWidget >,
	public ControlItemBackgroundForNormalHoverDisabled < QListWidget >
{
	Q_OBJECT
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	ListWidget(QWidget* parent = nullptr);

	/** ��������
	*/
	virtual ~ListWidget();

public:
	/** �������߶�
	@param [in] maxHeight ���߶�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setMaxHeight(int32_t maxHeight, bool rePaint = false);
};