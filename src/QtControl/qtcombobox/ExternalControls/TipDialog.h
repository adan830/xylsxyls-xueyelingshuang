#pragma once
#include "DialogShow.h"

/** ��ʾ������
*/
class TipDialog : protected DialogShow
{
	Q_OBJECT
public:
	/** ������ʾ��
	@param [out] dialogId ����IDֵ
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] buttonText ��ť����
	@param [in] done ��ť���º�ķ���ֵ
	@param [in] parent ������ָ��
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@return �رմ���ʱ���ķ���ֵ
	*/
	static int32_t popTipDialog(int32_t& dialogId,
								const QString& title,
								const QString& tip,
								const QString& buttonText,
								int32_t done,
								QDialog* parent = nullptr,
								int32_t timeOut = -1);
private:
	TipDialog(const QString& title,
			  const QString& tip,
			  const QString& buttonText,
			  int32_t done);

private:
	Label* m_tip;
	COriginalButton* m_accept;
};