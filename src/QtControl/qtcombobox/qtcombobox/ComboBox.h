#ifndef COMBOBOX_H__
#define COMBOBOX_H__

#include <QtWidgets/QComboBox>
#include <stdint.h>
#include "ControlFont.h"
#include "ControlSelf.h"
#include "ControlBorder.h"

class ListWidget;
class ComboBox : 
	public ControlFont < QComboBox >,
	public ControlSelf < QComboBox >,
	public ControlBorderForNormalHoverPressedDisabled < QComboBox >
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	ComboBox(QWidget* parent = NULL);

public:
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

	/** ����������ͷ�ĳߴ�
	@param [in] width ������ͷ���
	@param [in] height ������ͷ�߶�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownSize(int32_t width, int32_t height, bool rePaint = false);

	/** ����������ͷ�ı߿���
	@param [in] width ������ͷ���
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownBorderWidth(int32_t width, bool rePaint = false);

	/** ����������ͷ��ͼƬ
	@param [in] dropDownImgPath ����ͼƬ·�������·���б���ʹ����б��
	@param [in] dropDownImgStateCount ����ƽ�ּ���
	@param [in] dropDownImgNormal ��ѡ�г�̬ͼƬ�������1��ʾ��ͼƬ����ָ�4�ݻ�8�ݣ�ѡ������ĵ�һ��
	@param [in] dropDownImgHover ��ѡ����ͣͼƬ
	@param [in] dropDownImgDisabled ��ѡ�н���ͼƬ
	@param [in] dropDownImgCkNormal ѡ�г�̬ͼƬ
	@param [in] dropDownImgCkDisabled ѡ�н���ͼƬ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownImage(const QString& dropDownImgPath,
						  int32_t dropDownImgStateCount = 8,
						  int32_t dropDownImgNormal = 1,
						  int32_t dropDownImgHover = 2,
						  int32_t dropDownImgDisabled = 4,
						  int32_t dropDownImgExpandNormal = 5,
						  int32_t dropDownImgExpandDisabled = 8,
						  bool rePaint = false);

	/** ����������ͷ�������Ͻǵı߾�
	@param [in] topOrigin �ϲ�ƫ����
	@param [in] rightOrigin �Ҳ�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setDropDownTopRightOrigin(int32_t topOrigin, int32_t rightOrigin, bool rePaint = false);

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

	/** ���ñ�����ɫ
	@param [in] color ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListBackgroundColor(const QColor& color, bool rePaint = false);

	/** ���ñ߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListBorderWidth(int32_t width, bool rePaint = false);

	/** ���ñ߿���ɫ
	@param [in] color ��̬
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListBorderColor(const QColor& color, bool rePaint = false);

	/** ���ýڵ㱳����ɫ��list�ؼ�û�а������ԣ�
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListItemBorderColor(const QColor& normalColor,
								const QColor& hoverColor,
								const QColor& disabledColor,
								bool rePaint = false);

	/** ���ýڵ�߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListItemBorderWidth(int32_t width, bool rePaint = false);

	/** ���ýڵ㱳��ͼƬ���ͱ߿���ɫ���ô�
	@param [in] borderImgPath ����ͼƬ·�������·���б���ʹ����б��
	@param [in] borderImgStateCount ����ƽ�ּ���
	@param [in] borderImgNormal ��ѡ�г�̬ͼƬ�������1��ʾ��ͼƬ����ָ�4�ݻ�8�ݣ�ѡ������ĵ�һ��
	@param [in] borderImgHover ��ѡ����ͣͼƬ
	@param [in] borderImgDisabled ��ѡ�н���ͼƬ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListItemBorderImage(const QString& borderImgPath,
								int32_t borderImgStateCount = 4,
								int32_t borderImgNormal = 1,
								int32_t borderImgHover = 2,
								int32_t borderImgDisabled = 4,
								bool rePaint = false);

	/** ���ýڵ�߶�
	@param [in] height �ڵ�߶�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListItemHeight(int32_t height, bool rePaint = false);

	/** ����������ɫ
	@param [in] normalColor ��̬��ɫ
	@param [in] hoverColor ��ͣ��ɫ
	@param [in] disabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListTextColor(const QColor& normalColor,
						  const QColor& hoverColor,
						  const QColor& disabledColor,
						  bool rePaint = false);

	/** ��������
	@param [in] fontName ������
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListFontFace(const QString& fontName, bool rePaint = false);

	/** ���������С
	@param [in] fontSize �����С
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListFontSize(int32_t fontSize, bool rePaint = false);

	/** �����ı�ƫ����
	@param [in] origin �ı�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setListTextOrigin(int32_t origin, bool rePaint = false);

	/** �ڵ㵽���ڵ��ĸ���߾�
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

	/** �ػ�
	*/
	virtual void repaint();

private:
	virtual void showEvent(QShowEvent* eve);
	virtual void mouseReleaseEvent(QMouseEvent* eve);
	virtual void showPopup();
	virtual void hidePopup();

private:
	ListWidget* m_listWidget;
	int32_t m_dropDownImgNormal;
	int32_t m_dropDownImgDisabled;
	int32_t m_dropDownImgExpandNormal;
	int32_t m_dropDownImgExpandDisabled;
	int32_t m_dropDownImgStateCount;
	std::map<int32_t, std::map<int32_t, int32_t>> m_imageStateMap;
	std::wstring m_imagePath;
};

#endif