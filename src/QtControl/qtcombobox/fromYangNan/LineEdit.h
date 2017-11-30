#pragma once
#include "ControlSelf.h"
#include "ControlFont.h"
#include "ControlBorder.h"
#include "ControlBackground.h"
#include <QtWidgets/QLineEdit>

class LineEdit :
	public ControlSelf < QLineEdit >,
	public ControlFont < QLineEdit >,
	public ControlBorderForNormalHoverDisabled < QLineEdit >,
	public ControlBackgroundForNormalHoverDisabled < QLineEdit >
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	LineEdit(QWidget* parent = NULL);

	/** ��������
	*/
	virtual ~LineEdit();

public:

private:
	/** ���ó�ʼ��
	*/
	void init();
};