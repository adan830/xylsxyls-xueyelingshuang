#pragma once
#include "ComboBox.h"

/** �����࣬�ڵ��ӦID��ţ�����������ݸı�ʱ�����ź�
*/
class IdItemComboBox : virtual public ComboBox
{
	
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	IdItemComboBox(QWidget* parent = NULL);

	/** ��������
	*/
	virtual ~IdItemComboBox();

public:
	/** ��Ӵ���ID�Ľڵ�
	@param [in] id �ڵ�ID
	@param [in] text �ڵ�����
	*/
	void addItem(qint64 id, const QString& text);

	/** ���һ�����ID�Ľڵ�
	@param [in] idList �ڵ�ID�б�
	@param [in] textList �ڵ������б�
	*/
	void addItems(const QList<qint64>& idList, const QStringList& textList);

public slots:
	void currentTextChanged4(const QString& str);

signals:
	/** ������������ַ����ı�ʱ�����ź�
	@param [in] id �ڵ�ID
	@param [in] text ��ǰ��������ı�����
	*/
	void currentItemChanged5(qint64 id, const QString& text);

public:
	std::map<void*, qint64> m_mapIndex;
};