#ifndef CONTROLBASE_H__
#define CONTROLBASE_H__
//#pragma once
#include "QssString.h"
#include <string>
#include <QColor>

class QShowEvent;
class QWidget;
template <class QBase>
class ControlBase : public QBase
{
public:
	/** �ػ�
	*/
	virtual void repaint();

protected:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	ControlBase(QWidget* parent = NULL);

	virtual ~ControlBase(){};

	/** ��ʼ��
	@param [in] className ����
	@param [in] itemName �ڵ���
	*/
	void init(const std::wstring& className, const std::wstring& itemName);

	/** ��������
	@param [in] fontName ������
	@param [in] isItem �����Ƿ�Ϊ�ڵ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setFontFace(const std::wstring& fontName, bool isItem, bool rePaint);

	/** �������ζ�Ӧֵ
	@param [in] keyWord �ؼ���
	@param [in] valuePx ����ֵ����������px
	@param [in] isItem �����Ƿ�Ϊ�ڵ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setPxValue(const std::wstring& keyWord, int32_t valuePx, bool isItem, bool rePaint);

	/** ����������Ӧֵ��solid
	@param [in] keyWord �ؼ���
	@param [in] valuePx ����ֵ����������px
	@param [in] isItem �����Ƿ�Ϊ�ڵ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setPxSolidValue(const std::wstring& keyWord, int32_t valuePxSolid, bool isItem, bool rePaint);

	/** ���ö�Ӧֵ
	@param [in] keyWord �ؼ���
	@param [in] value ֵ
	@param [in] isItem �����Ƿ�Ϊ�ڵ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setKeyValue(const std::wstring& keyWord, const std::wstring& value, bool isItem, bool rePaint);

	/** ������ɫ
	@param [in] colorStateMap ��ɫ����
	@param [in] keyWord �ؼ���
	@param [in] isItem �����Ƿ�Ϊ�ڵ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setColorStateMap(const std::map<int32_t, std::map<int32_t, QColor>>& colorStateMap,
						  const std::wstring& keyWord,
						  bool isItem,
						  bool rePaint);

	/** ����ͼƬ
	@param [in] imageStateMap ͼƬ����
	@param [in] imagePath ·��
	@param [in] stateCount ״̬����
	@param [in] keyWord �ؼ���
	@param [in] isItem �����Ƿ�Ϊ�ڵ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setImageStateMap(const std::map<int32_t, std::map<int32_t, int32_t>>& imageStateMap,
						  const std::wstring& imagePath,
						  int32_t stateCount,
						  const std::wstring& keyWord,
						  bool isItem,
						  bool rePaint);

	/** ����ͼƬ
	@param [in] imageStateMap ͼƬ����
	@param [in] imagePath ·��
	@param [in] stateCount ״̬����
	@param [in] keyWord �ؼ���
	@param [in] itemName �ڵ���
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setImageStateMap(const std::map<int32_t, std::map<int32_t, int32_t>>& imageStateMap,
						  const std::wstring& imagePath,
						  int32_t stateCount,
						  const std::wstring& keyWord,
						  const std::wstring& itemName,
						  bool rePaint);

protected:
	virtual void updateStyle();
	virtual void showEvent(QShowEvent* eve);

protected:
	QssString m_controlStyle;
	std::wstring m_className;
	std::wstring m_itemName;
};

#include "ControlBase.inl"

#endif