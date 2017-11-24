#pragma once
#include "ControlSelf.h"
#include "ControlFont.h"
#include "ControlBorder.h"
#include <QtWidgets/QLineEdit>

class LineEdit :
	public ControlSelf < QLineEdit >,
	public ControlFont < QLineEdit >,
	public ControlBorderForNormalHoverDisabled < QLineEdit >
{
public:
	virtual ~LineEdit(){};
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	LineEdit(QWidget* parent = NULL);

private:
	/** ���ó�ʼ��
	*/
	void init();
};