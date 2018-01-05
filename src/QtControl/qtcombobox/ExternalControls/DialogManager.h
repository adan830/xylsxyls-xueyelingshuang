#pragma once
#include <map>
#include <stdint.h>
#include <QString>
#include <QObject>

class DialogBase;
class QWidget;
/** ��һʵ��������ͳһ�����ڴ����رգ�����Ķ���ӿڣ��������д���
DialogManager::instance().removeAll();
*/
class DialogManager : public QObject
{
	friend class DialogBase;
	friend class DialogShow;
public:
	/** ��һʵ��
	@return ���ص�һʵ��
	*/
	static DialogManager& instance();

	/** ����ѯ�ʿ�
	@param [out] dialogId ����IDֵ
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] acceptText ���ܰ�ť����
	@param [in] acceptDone ���ܰ�ť���º�ķ���ֵ
	@param [in] ignoreText �ܾ���ť����
	@param [in] ignoreDone �ܾ���ť���º�ķ���ֵ
	@param [in] parent ������ָ��
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popAskDialog(int32_t& dialogId,
						 const QString& title,
						 const QString& tip,
						 const QString& acceptText,
						 int32_t acceptDone,
						 const QString& ignoreText,
						 int32_t ignoreDone,
						 QWidget* parent = nullptr,
						 int32_t timeOut = -1,
						 bool isCountDownVisible = false);

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
	int32_t popTipDialog(int32_t& dialogId,
						 const QString& title,
						 const QString& tip,
						 const QString& buttonText,
						 int32_t done,
						 QWidget* parent = nullptr,
						 int32_t timeOut = -1,
						 bool isCountDownVisible = false);

	/** ���������
	@param [out] dialogId ����IDֵ
	@param [in] title ����
	@param [in] editTip ��ʾ����
	@param [in] buttonText ��ť����
	@param [in] done ��ť���º�ķ���ֵ
	@param [in,out] editText �����Ĭ������
	@param [in] parent ������ָ��
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popInputDialog(int32_t& dialogId,
						   const QString& title,
						   const QString& editTip,
						   const QString& buttonText,
						   int32_t done,
						   QString& editText,
						   QWidget* parent = nullptr,
						   int32_t timeOut = -1,
						   bool isCountDownVisible = false);

	/** �����ȴ���
	@param [out] dialogId ����IDֵ
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] parent ������ָ��
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popWaitDialog(int32_t& dialogId,
						  const QString& title,
						  const QString& tip,
						  QWidget* parent = nullptr,
						  int32_t timeOut = -1,
						  bool isCountDownVisible = false);

	/** ����ID�����ٴ���
	@param [in] dialogId ����ID��
	*/
	void destroyDialog(int32_t dialogId);

	/** �������һ�������Ĵ���
	*/
	void destroyLastDialog();

	/** �������д���
	*/
	void destroyAll();

	/** ���ݴ���ָ�������д����л�ȡ����ID
	*/
	int32_t DialogId(DialogBase* base);

protected:
	DialogManager();

private:
	/** �洢����ָ��
	@param [in] dialog ����ָ��
	@return ���ش��ڶ�ӦID��
	*/
	int32_t setDialog(DialogBase* dialog);

	/** ����ID�����ٴ���
	@param [in] dialogId ����ID��
	*/
	void removeDialog(int32_t dialogId);

	/** ����ID�����ٴ���
	@param [in] dialogId ����ID��
	*/
	void removeDialog(DialogBase* base);

	int32_t getId();

private:
	std::map<int32_t, DialogBase*> m_mapDialog;
	int32_t m_id;
};