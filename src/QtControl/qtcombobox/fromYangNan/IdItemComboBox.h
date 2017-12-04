#pragma once
#include "ComboBox.h"

/** 定做类，节点对应ID编号，当点击框内容改变时发射信号
*/
class IdItemComboBox : public ComboBox
{
	Q_OBJECT
public:
	/** 构造函数
	@param [in] parent 父窗口指针
	*/
	IdItemComboBox(QWidget* parent = nullptr);

	/** 析构函数
	*/
	virtual ~IdItemComboBox();

public:
	/** 添加带有ID的节点
	@param [in] id 节点ID（ID不唯一，可以添加两个相同ID的节点）
	@param [in] text 节点内容
	*/
	void addItem(qint64 id, const QString& text);

	/** 添加一组带有ID的节点（会检测两个list的size是否一样，不一样不添加，和原生addItems相似不具备覆盖效果）
	@param [in] idList 节点ID列表
	@param [in] textList 节点文字列表
	*/
	void addItems(const QList<qint64>& idList, const QStringList& textList);

Q_SIGNALS:
	/** 当选择了另一个id的下拉节点时发送信号（点击框设为可编辑，手动输入文字时不发送信号）
	@param [in] id 节点ID
	@param [in] text 当前点击框内文本内容
	*/
	void currentItemChanged(qint64 id, const QString& text);

private slots:
	void curIndexChanged(const QString& str);
};