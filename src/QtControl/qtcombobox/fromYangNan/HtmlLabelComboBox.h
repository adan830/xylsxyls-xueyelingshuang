#pragma once
#include "ComboBox.h"
#include <QColor>

class Label;
class QListWidgetItem;
class HtmlLabelComboBox : public ComboBox
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	HtmlLabelComboBox(QWidget* parent = nullptr);

	/** ��������
	*/
	virtual ~HtmlLabelComboBox();

public:
	/** ����һ��html��ʽ�ı�
	@param [in] text �ı�
	*/
	void addItem(const QString& text);

	/** ��������html��ʽ�ı�
	@param [in] textList �ı��б�
	*/
	void addItems(const QStringList& textList);

	/** ��������������
	@param [in] fontName ������
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListFontFace(const QString& fontName, bool rePaint = false);

	/** ���������������С
	@param [in] fontSize �����С
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListFontSize(int32_t fontSize, bool rePaint = false);

	/** ����������������ɫ
	@param [in] normalColor ��̬��ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListTextColor(const QColor& normalColor,
						  const QColor& disabledColor,
						  bool rePaint = false);

	/** ��������ƫ����
	@param [in] origin ����ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setTextOrigin(int32_t origin, bool rePaint = false);

private:
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

public:
	int32_t m_textOrigin;

private:
	std::map<QListWidgetItem*, Label*> m_mapLabel;
};