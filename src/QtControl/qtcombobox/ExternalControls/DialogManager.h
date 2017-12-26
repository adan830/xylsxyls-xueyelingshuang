#pragma once
#include <map>
#include <stdint.h>

class DialogBase;
/** ��һʵ��������ͳһ�����ڴ����رգ�����Ķ���ӿڣ��������д���
DialogManager::instance().removeAll();
*/
class DialogManager
{
public:
	/** ��һʵ��
	@return ���ص�һʵ��
	*/
	static DialogManager& instance();

	/** �洢����ָ��
	@param [in] dialog ����ָ��
	@return ���ش��ڶ�ӦID��
	*/
	int32_t setDialog(DialogBase* dialog);

	/** ����ID�����ٴ���
	@param [in] dialogId ����ID��
	*/
	void removeDialog(int32_t dialogId);

	/** �������д���
	*/
	void removeAll();

private:
	DialogManager();

	int32_t getId();

private:
	std::map<int32_t, DialogBase*> m_mapDialog;
	int32_t m_id;
};