#pragma once
#include <QtWidgets/QLabel>
#include "ControlShow.h"
#include "ControlFont.h"
#include "ControlBorder.h"
#include "ControlBackground.h"

class Label : 
	public ControlShow < QLabel >,
	public ControlFont < QLabel >,
	public ControlBorderForNormalHoverDisabled < QLabel >,
	public ControlBackgroundForNormalHoverDisabled < QLabel >
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	Label(QWidget* parent = nullptr);

	/** ��������
	*/
	virtual ~Label();

public:
	
};