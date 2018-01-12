#pragma once
#include "../CW3LModalFrame.h"
#include <list>
#include <stdint.h>

class TreeWidget;
class COriginalButton;

/** �����б��
*/
class FriendDialog : public CW3LModalFrame
{
public:
	struct User
	{
		int32_t m_userId;
		QString m_userPicPath;
		QString m_userName;
		int32_t m_userState;
	};

	struct Group
	{
		int32_t m_groupId;
		QString m_groupName;
		std::list<User> m_userList;
	};
	
public:
	FriendDialog();

	/** ���һ����
	@param [in] groupList ����Ϣ
	*/
	void addGroupList(const Group& groupList);

private:
	bool eventFilter(QObject* obj, QEvent* eve);

private:
	TreeWidget* m_friendTree;

	QWidget* m_lastHoverWidget;

private:
	COriginalButton* m_exit;
	COriginalButton* m_bottomExit;

	std::map<int32_t, QWidget*> m_groupData;
	std::map<int32_t, std::map<int32_t, QWidget*>> m_userData;
};