#pragma once
#include "../CW3LModalFrame.h"
#include <list>
#include <stdint.h>

class TreeWidget;
class COriginalButton;
class QTreeWidgetItem;

/** �����б��
*/
class FriendDialog : public CW3LModalFrame
{
	Q_OBJECT
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
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	FriendDialog(QWidget* parent = nullptr);

	/** ���һ����
	@param [in] groupList ����Ϣ
	*/
	void addGroupList(const Group& groupList);

	/** �����û���Ϣ��������û��������򲻻��иĶ�
	@param [in] groupId ��ID
	@param [in] userInfo �û���Ϣ
	*/
	void updateUserInfo(int32_t groupId, const FriendDialog::User& userInfo);

	/** ����û���Ϣ���������𲻴����򲻻��иĶ�
	@param [in] groupId ��ID
	@param [in] userInfo �û���Ϣ
	*/
	void addUserInfo(int32_t groupId, const FriendDialog::User& userInfo);

	/** �Ƴ��û���������ɾ����
	@param [in] groupId ��ID
	@param [in] userId �û�ID
	*/
	void removeUser(int32_t groupId, int32_t userId);

	/** �Ƴ���
	@param [in] groupId ��ID
	*/
	void removeGroup(int32_t groupId);

private:
	bool eventFilter(QObject* obj, QEvent* eve);
	void paintEvent(QPaintEvent* eve);
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	void ncActiveChanged(int32_t wParam);
	void setResponseHighlightDialog(QWidget* parent);

private slots:
	void onIndiClicked();
	void onInviteClicked();
	void onItemExpanded(QTreeWidgetItem* item);
	void onItemCollapsed(QTreeWidgetItem* item);

Q_SIGNALS:
	void inviteClicked(int32_t groupId, int32_t userId);

private:
	TreeWidget* m_friendTree;

	QWidget* m_lastHoverWidget;
	bool m_highLight;

private:
	COriginalButton* m_exit;
	COriginalButton* m_bottomExit;

	std::map<int32_t, QWidget*> m_groupData;
	std::map<int32_t, std::map<int32_t, QWidget*>> m_userData;
};