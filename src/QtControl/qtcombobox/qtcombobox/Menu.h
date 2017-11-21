#pragma once
#include <QMenu>
#include "ControlFont.h"
#include "ControlItem.h"
#include "ControlSelf.h"
#include "ControlBorder.h"
#include <vector>

class QMouseEvent;
class CustomStyle;
class Menu : 
	public ControlFont < QMenu >,
	public ControlItem < QMenu >,
	public ControlSelf < QMenu >,
	public ControlBorderForNormal < QMenu >,
	public ControlItemBorderForNormalSelectedDisabled < QMenu >
{
public:
	/** 构造函数
	@param [in] parent 父窗口指针
	*/
	Menu(QWidget* parent = NULL);

	/** 构造函数
	@param [in] title 菜单标题
	@param [in] icon 菜单图标
	@param [in] size 菜单图标大小
	@param [in] parent 父窗口指针
	*/
	Menu(const QString& title, const QString& icon = QString(), const QSize& size = QSize(), QWidget* parent = NULL);

public:
	/** 设置背景颜色
	@param [in] color 背景颜色
	@param [in] rePaint 是否立即重画
	*/
	void setBackgroundColor(const QColor& color, bool rePaint = false);

	/** 设置文本偏移量
	@param [in] origin 文本偏移量
	@param [in] rePaint 是否立即重画
	*/
	void setItemTextOrigin(int32_t origin, bool rePaint = false);

	/** 添加节点
	@param [in] text 文本
	@param [in] uncheckIcon 未选择时的图片
	@param [in] uncheckIconSize 未选择时的图片大小
	@param [in] checkIcon 选择时的图片
	@param [in] checkIconSize 选择时的图片大小
	@return 返回添加的节点指针
	*/
	QAction* addAction(const QString& text,
					   const QString& uncheckIcon = QString(),
					   const QSize& uncheckIconSize = QSize(0, 0),
					   const QString& checkIcon = QString(),
					   const QSize& checkIconSize = QSize(0, 0));

	/** 添加菜单
	@param [in] menu 菜单指针
	*/
	void addMenu(Menu* menu);

	/** 设置分割线粗度
	@param [in] height 分割线高度
	@param [in] rePaint 是否立即重画
	*/
	void setSeparatorHeight(int32_t height, bool rePaint = false);

	/** 设置分割线颜色
	@param [in] color 分割线颜色
	@param [in] rePaint 是否立即重画
	*/
	void setSeparatorColor(const QColor& color, bool rePaint = false);

	/** 设置图标偏移量
	@param [in] leftOrigin 图标偏移量
	@param [in] rePaint 是否立即重画
	*/
	void setItemIconOrigin(int32_t leftOrigin, bool rePaint = false);

	/** 弹出菜单
	@param [in] point 弹出位置
	@return 在选择了一个菜单后返回该菜单指针，如果点击其他区域则返回空
	*/
	QAction* exec(const QPoint& point);

private:
	/** 改变图标
	@param [in] action 选中的菜单项
	@param [in] icon 当前图标
	@return 返回改变后的图标
	*/
	QIcon ChangeIcon(QAction* action, const QIcon& icon);
	

private:
	std::map<QAction*, QIcon> m_mapIconData;
	CustomStyle* m_pCustomStyle;
	std::vector<Menu*> m_vecMenu;
};