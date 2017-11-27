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

	/** ���ñ�����ɫ��û�а���Ч����
	@param [in] backgroundNormalColor ��̬��ɫ
	@param [in] backgroundHoverColor ��ͣ��ɫ
	@param [in] backgroundDisabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBackgroundColor(const QColor& backgroundNormalColor,
	 	 		 		    const QColor& backgroundHoverColor,
						    const QColor& backgroundDisabledColor,
							bool rePaint = false);

private:
	/** ���ó�ʼ��
	*/
	void init();
};