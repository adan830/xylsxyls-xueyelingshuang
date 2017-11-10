#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <stdint.h>
#include <string>
#include "ListWidget.h"

class ComboBox : public QComboBox
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	ComboBox(QWidget* parent = NULL);

public:
	/** ���������ΪԲ�ǣ�����Բ�ǰ뾶��ֻ�м���߿�Ż���Բ��
	@param [in] radius Բ�ǰ뾶
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderRadius(int32_t radius, bool rePaint = false);

	/** ���õ���򱳾���ɫ
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] pressedColor ������ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBackgroundColor(const QColor& normalColor,
							const QColor& hoverColor,
							const QColor& pressedColor,
							const QColor& disabledColor,
							bool rePaint = false);

	/** ���ñ߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderWidth(int32_t width, bool rePaint = false);

	/** ���õ����߿���ɫ
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] pressedColor ������ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderColor(const QColor& normalColor,
						const QColor& hoverColor,
						const QColor& pressedColor,
						const QColor& disabledColor,
						bool rePaint = false);

	/** ���õ����߿�ͼƬ���ͱ߿���ɫ���ô�
	@param [in] borderImgPath ����ͼƬ·�������·���б���ʹ����б��
	@param [in] borderImgStateCount ����ƽ�ּ���
	@param [in] borderImgNormal ��ѡ�г�̬ͼƬ�������1��ʾ��ͼƬ����ָ�4�ݻ�8�ݣ�ѡ������ĵ�һ��
	@param [in] borderImgHover ��ѡ����ͣͼƬ
	@param [in] borderImgPressed ��ѡ�а���ͼƬ
	@param [in] borderImgDisabled ��ѡ�н���ͼƬ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderImage(const QString& borderImgPath,
						int32_t borderImgStateCount = 4,
						int32_t borderImgNormal = 1,
						int32_t borderImgHover = 2,
						int32_t borderImgPressed = 3,
						int32_t borderImgDisabled = 4,
						bool rePaint = false);

	/** ����������ͷ�Ŀ��
	@param [in] width ������ͷ���
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownWidth(int32_t width, bool rePaint = false);

	/** ����������ͷ�ĸ߶�
	@param [in] height ������ͷ�߶�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownHeight(int32_t height, bool rePaint = false);

	/** ����������ͷ�ı߿���
	@param [in] width ������ͷ���
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownBorderWidth(int32_t width, bool rePaint = false);

	/** ����������ͷ��ͼƬ
	@param [in] dropDownImgPath ����ͼƬ·�������·���б���ʹ����б��
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownImage(const QString& dropDownImgPath, bool rePaint = false);

	/** ����������ɫ
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] pressedColor ������ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setTextColor(const QColor& normalColor,
					  const QColor& hoverColor,
					  const QColor& pressedColor,
					  const QColor& disabledColor,
					  bool rePaint = false);

	/** ��������
	@param [in] fontName ������
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setFontFace(const QString& fontName, bool rePaint = false);

	/** ���������С
	@param [in] fontSize �����С
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setFontSize(int32_t fontSize, bool rePaint = false);

	/** �����ı�ƫ����
	@param [in] origin �ı�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setTextOrigin(int32_t origin, bool rePaint = false);

	/** ������������������ƫ����
	@param [in] origin ����ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListOrigin(int32_t origin, bool rePaint = false);

	/** ����һ��
	@param [in] text �ı�
	*/
	void addItem(const QString& text);

	/** �ػ�
	*/
	void repaint();

private:
	void updateStyle();
	void showEvent(QShowEvent* eve);

public:
	ListWidget* m_listWidget;

private:
	bool m_hasSetBorderRadius;
	int32_t m_borderRadius;

	bool m_hasSetBackgroundColor;
	std::map<int32_t, QColor> m_backgroundColorMap;

	bool m_hasSetBorderWidth;
	int32_t m_borderWidth;

	bool m_hasSetBorderColor;
	std::map<int32_t, QColor> m_borderColorMap;

	bool m_hasSetBorderImg;
	bool m_loadBorderImgSuccess;
	int32_t m_borderImgStateCount;
	std::wstring m_borderImgPath;
	std::vector<int32_t> m_vecBorderImgHeight;
	std::map<int32_t, int32_t> m_borderImgMap;

	bool m_hasSetDropDownWidth;
	int32_t m_dropDownWidth;

	bool m_hasSetDropDownHeight;
	int32_t m_dropDownHeight;

	bool m_hasSetDropDownBorderWidth;
	int32_t m_dropDownBorderWidth;

	bool m_hasSetDropDownImg;
	std::wstring m_dropDownImgPath;

	bool m_hasSetTextColor;
	std::map<int32_t, QColor> m_itemTextColorMap;

	bool m_hasSetFontName;
	std::wstring m_fontName;

	bool m_hasSetFontSize;
	int32_t m_fontSize;

	bool m_hasSetTextOrigin;
	int32_t m_textOrigin;

	bool m_hasSetListOrigin;
	int32_t m_listOrigin;
};

#endif