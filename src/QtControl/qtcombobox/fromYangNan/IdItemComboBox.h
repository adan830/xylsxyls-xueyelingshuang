#pragma once
#include "ComboBox.h"

/** �����࣬�ڵ��ӦID��ţ�����������ݸı�ʱ�����ź�
*/
class IdItemComboBox : public ComboBox
{
	Q_OBJECT
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	IdItemComboBox(QWidget* parent = nullptr);

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
	void curIndexChanged(const QString& str);

signals:
	/** ������������ַ����ı�ʱ�����ź�
	@param [in] id �ڵ�ID
	@param [in] text ��ǰ��������ı�����
	*/
	void currentItemChanged5(qint64 id, const QString& text);

public:
	std::map<void*, qint64> m_mapIndex;
};