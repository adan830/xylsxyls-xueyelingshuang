#pragma once
#include "ComboBox.h"

class HtmlComboBox : public ComboBox
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	HtmlComboBox(QWidget* parent = NULL);

	/** ��������
	*/
	virtual ~HtmlComboBox();

private:
	void paintEvent(QPaintEvent* eve);
};