#pragma once
#include <QtWidgets/QListWidget>
#include <stdint.h>

class ListWidget : public QListWidget
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	ListWidget(QWidget* parent = NULL);

public:
	/** ���ñ�����ɫ
	@param [in] color ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBackgroundColor(const QColor& color, bool rePaint = false);

	/** ���ñ߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderWidth(int32_t width, bool rePaint = false);

	/** ���ñ߿���ɫ
	@param [in] color ��̬
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderColor(const QColor& color, bool rePaint = false);

	/** ���ýڵ㱳����ɫ��list�ؼ�û�а������ԣ�
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemBorderColor(const QColor& normalColor,
							const QColor& hoverColor,
							const QColor& disabledColor,
							bool rePaint = false);

	/** ���ýڵ�߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemBorderWidth(int32_t width, bool rePaint = false);

	/** ���ýڵ㱳��ͼƬ���ͱ߿���ɫ���ô�
	@param [in] borderImgPath ����ͼƬ·�������·���б���ʹ����б��
	@param [in] borderImgStateCount ����ƽ�ּ���
	@param [in] borderImgNormal ��ѡ�г�̬ͼƬ�������1��ʾ��ͼƬ����ָ�4�ݻ�8�ݣ�ѡ������ĵ�һ��
	@param [in] borderImgHover ��ѡ����ͣͼƬ
	@param [in] borderImgDisabled ��ѡ�н���ͼƬ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemBorderImage(const QString& borderImgPath,
							int32_t borderImgStateCount = 4,
							int32_t borderImgNormal = 1,
							int32_t borderImgHover = 2,
							int32_t borderImgDisabled = 4,
							bool rePaint = false);

	/** ���ýڵ�߶�
	@param [in] height �ڵ�߶�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemHeight(int32_t height, bool rePaint = false);

	/** ����������ɫ
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setTextColor(const QColor& normalColor,
					  const QColor& hoverColor,
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

	/** �ڵ㵽���ڵ������߾�
	@param [in] origin ���ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemLeftOrigin(int32_t origin, bool rePaint = false);

	/** �ڵ㵽���ڵ��ϲ���߾�
	@param [in] origin �ϲ�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemTopOrigin(int32_t origin, bool rePaint = false);

	/** �ڵ㵽���ڵ��Ҳ���߾�
	@param [in] origin �Ҳ�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemRightOrigin(int32_t origin, bool rePaint = false);

	/** �ڵ㵽���ڵ��²���߾�
	@param [in] origin �²�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setItemBottomOrigin(int32_t origin, bool rePaint = false);

	/** �ػ�
	*/
	void repaint();

private:
	void updateStyle();
	void showEvent(QShowEvent* eve);

private:
	bool m_hasSetBackgroundColor;
	QColor m_backgroundColor;

	bool m_hasSetBorderWidth;
	int32_t m_borderWidth;

	bool m_hasSetBorderColor;
	QColor m_borderColor;

	bool m_hasSetItemBorderColor;
	std::map<int32_t, QColor> m_itemBorderColorMap;

	bool m_hasSetItemBorderWidth;
	int32_t m_itemBorderWidth;

	bool m_hasSetItemBorderImg;
	bool m_loadItemBorderImgSuccess;
	int32_t m_itemBorderImgStateCount;
	std::wstring m_itemBorderImgPath;
	std::vector<int32_t> m_vecItemBorderImgHeight;
	std::map<int32_t, int32_t> m_itemBorderImgMap;

	bool m_hasSetItemHeight;
	int32_t m_itemHeight;

	bool m_hasSetTextColor;
	std::map<int32_t, QColor> m_itemTextColorMap;

	bool m_hasSetFontName;
	std::wstring m_fontName;

	bool m_hasSetFontSize;
	int32_t m_fontSize;

	bool m_hasSetTextOrigin;
	int32_t m_textOrigin;

	bool m_hasSetItemLeftOrigin;
	int32_t m_itemLeftOrgin;

	bool m_hasSetItemTopOrigin;
	int32_t m_itemTopOrgin;

	bool m_hasSetItemRightOrigin;
	int32_t m_itemRightOrgin;

	bool m_hasSetItemBottomOrigin;
	int32_t m_itemBottomOrgin;
};