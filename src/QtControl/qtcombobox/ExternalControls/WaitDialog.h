#pragma once
#include "DialogShow.h"

/** �ȴ�������
*/
class WaitDialog : protected DialogShow
{
	Q_OBJECT
public:
	/** �����ȴ���
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] parent ������ָ��
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@return �رմ���ʱ���ķ���ֵ
	*/
	static int32_t popWaitDialog(const QString& title,
								const QString& tip,
								QDialog* parent = nullptr,
								int32_t timeOut = -1);
private:
	WaitDialog(const QString& title, const QString& tip);

private:
	Label* m_tip;
};