#pragma once
#include <QtWidgets/QLabel>
#include "ControlBase.h"

class Label : public ControlBase < QLabel >
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	Label(QWidget* parent = NULL);

	/** ���ñ���ͼƬ��û�а���Ч����
	@param [in] backgroundImg ����ͼƬ·�������·���б���ʹ����б��
	@param [in] backgroundImgStateCount ͼƬ�����и����
	@param [in] backgroundImgNormal ��̬ͼƬ
	@param [in] backgroundImgHover ��ͣͼƬ
	@param [in] backgroundImgDisabled ����ͼƬ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBackgroundImage(const QString& backgroundImg,
			   			    int32_t backgroundImgStateCount = 4,
						    int32_t backgroundImgNormal = 1,
						    int32_t backgroundImgHover = 2,
						    int32_t backgroundImgDisabled = 4,
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

	/** ����������ɫ��û�а���Ч����
	@param [in] textNormalColor ��̬��ɫ
	@param [in] textHoverColor ��ͣ��ɫ
	@param [in] textDisabledColor ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setTextColor(const QColor& textNormalColor,
	 	 		 	  const QColor& textHoverColor,
					  const QColor& textDisabledColor,
					  bool rePaint = false);

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

	/** �����ı�ƫ����
	@param [in] origin �ı�ƫ����
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setTextOrigin(int32_t origin, bool rePaint = false);

	/** �����ı���������ʾʡ�Ժ�
	@param [in] str �ַ���
	*/
	void setText(const QString& str);

	/** ��ȡ�ı�
	@return �����ı�
	*/
	QString text();

	/** �ػ�
	*/
	void repaint();

private:
	std::wstring m_str;
	int32_t m_leftOrigin;
	std::wstring m_fontName;
	int32_t m_fontSize;
};