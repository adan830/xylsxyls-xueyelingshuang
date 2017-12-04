#pragma once
#include "ControlShow.h"
#include "ControlSelf.h"
#include "ControlFont.h"
#include "ControlBorder.h"
#include "ControlBackground.h"
#include <QtWidgets/QLineEdit>

class LineEdit :
	public ControlShow < QLineEdit >,
	public ControlSelf < QLineEdit >,
	public ControlFont < QLineEdit >,
	public ControlBorderForNormalHoverDisabled < QLineEdit >,
	public ControlBackgroundForNormalHoverDisabled < QLineEdit >
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	LineEdit(QWidget* parent = nullptr);

	/** ��������
	*/
	virtual ~LineEdit();

public:

private:
	/** ���ó�ʼ��
	*/
	void setDefault();
};