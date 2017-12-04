#pragma once
#include "QssString.h"
#include <string>
#include <QColor>

class QShowEvent;
class QWidget;
template <class QBase>
class ControlShow : public QBase
{
public:
	/** �ػ�
	*/
	virtual void repaint();

protected:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	ControlShow(QWidget* parent = nullptr);

	/** ��������
	*/
	virtual ~ControlShow();

protected:
	/** ��ʼ��
	@param [in] className ����
	@param [in] itemName �ڵ���
	*/
	void init(const std::wstring& className, const std::wstring& itemName);

private:
	virtual void showEvent(QShowEvent* eve);

public:
	//style�ַ����������
	QssString m_controlStyle;
	//�����ַ���
	std::wstring m_className;
	//�ڵ����ַ���
	std::wstring m_itemName;
};

#include "ControlShow.cpp"
