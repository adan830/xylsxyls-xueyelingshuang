#pragma once
#include "IdItemComboBox.h"

class QListWidgetItem;
/** �����֧࣬����addItem��ʱ������html��ʽ���ı�
*/
class HtmlComboBox : public IdItemComboBox
{
	Q_OBJECT
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	HtmlComboBox(QWidget* parent = nullptr);

	/** ��������
	*/
	virtual ~HtmlComboBox();

	/** ���õ��������ƫ����
	@param [in] origin ���������ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setTextOrigin(int32_t origin, bool rePaint = false);

	/** ����������������ɫ
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListTextColor(const QColor& normalColor,
						  const QColor& hoverColor,
						  const QColor& disabledColor,
						  bool rePaint = false);

	/** �����������ı�ƫ����
	@param [in] origin �ı�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListTextOrigin(int32_t origin, bool rePaint = false);

	/** �ڵ㵽�����򴰿ڵ��ĸ���߾�
	@param [in] leftOrigin ���ƫ����
	@param [in] topOrigin �ϲ�ƫ����
	@param [in] rightOrigin �Ҳ�ƫ����
	@param [in] bottomOrigin �²�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListItemAroundOrigin(int32_t leftOrigin,
								 int32_t topOrigin,
								 int32_t rightOrigin,
								 int32_t bottomOrigin,
								 bool rePaint = false);

	/** ����������ڵ�߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListItemBorderWidth(int32_t width, bool rePaint = false);

public:
	QColor m_normalColor;
	QColor m_selectedColor;
	QColor m_disabledColor;
	int32_t m_comboBoxOrigin;
	int32_t m_origin;
	int32_t m_leftOrigin;
	int32_t m_topOrigin;
	int32_t m_rightOrigin;
	int32_t m_bottomOrigin;
	int32_t m_itemBorderWidth;
};