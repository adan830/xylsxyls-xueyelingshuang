#pragma once
#include <map>
#include <stdint.h>
#include <QString>
#include <QObject>

enum
{
	/** ȷ�ϰ�ť
	*/
	ACCEPT_BUTTON = 1,

	/** ȡ����ť
	*/
	IGNORE_BUTTON = 2
};

class DialogBase;
class QWindow;
/** ��һʵ��������ͳһ�����ڴ����رգ�����Ķ���ӿڣ��������д���
DialogManager::instance().removeAll();
*/
class DialogManager : public QObject
{
	Q_OBJECT
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
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popAskDialog(int32_t& dialogId,
						 const QString& title,
						 const QString& tip,
						 const QString& acceptText,
						 int32_t acceptDone,
						 const QString& ignoreText,
						 int32_t ignoreDone,
						 QWindow* parent = nullptr,
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
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popTipDialog(int32_t& dialogId,
						 const QString& title,
						 const QString& tip,
						 const QString& buttonText,
						 int32_t done,
						 QWindow* parent = nullptr,
						 int32_t timeOut = -1,
						 bool isCountDownVisible = false);

	/** ���������
	@param [out] dialogId ����IDֵ
	@param [in] title ����
	@param [in] editTip ��ʾ����
	@param [in] buttonText ��ť����
	@param [in] done ��ť���º�ķ���ֵ
	@param [in,out] editText �����Ĭ������
	@param [in] maxLength ������󳤶ȣ�-1��ʾ������
	@param [in] parent ������ָ��
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popInputDialog(int32_t& dialogId,
						   const QString& title,
						   const QString& editTip,
						   const QString& buttonText,
						   int32_t done,
						   QString& editText,
						   int32_t maxLength = -1,
						   QWindow* parent = nullptr,
						   int32_t timeOut = -1,
						   bool isCountDownVisible = false);

	/** �����ȴ���
	@param [out] dialogId ����IDֵ
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] parent ������ָ��
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popWaitDialog(int32_t& dialogId,
						  const QString& title,
						  const QString& tip,
						  QWindow* parent = nullptr,
						  int32_t timeOut = -1,
						  bool isCountDownVisible = false);

	/** ����ѯ�ʿ�
	@param [out] dialogId ����IDֵ
	@param [in] tip ��ʾ����
	@param [in] title ����
	@param [in] parent ������ָ��
	@param [in] acceptText ���ܰ�ť����
	@param [in] ignoreText �ܾ���ť����
	@param [in] acceptDone ���ܰ�ť���º�ķ���ֵ
	@param [in] ignoreDone �ܾ���ť���º�ķ���ֵ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popAskDialog(int32_t& dialogId,
						 const QString& tip,
						 const QString& title = QString::fromStdWString(L"11��սƽ̨"),
						 QWindow* parent = nullptr,
						 const QString& acceptText = QString::fromStdWString(L"ȷ��"),
						 const QString& ignoreText = QString::fromStdWString(L"ȡ��"),
						 int32_t acceptDone = ACCEPT_BUTTON,
						 int32_t ignoreDone = IGNORE_BUTTON,
						 int32_t timeOut = -1,
						 bool isCountDownVisible = false);

	/** ����ѯ�ʿ�
	@param [out] dialogId ����IDֵ
	@param [in] tip ��ʾ����
	@param [in] parent ������ָ��
	@param [in] title ����
	@param [in] acceptText ���ܰ�ť����
	@param [in] ignoreText �ܾ���ť����
	@param [in] acceptDone ���ܰ�ť���º�ķ���ֵ
	@param [in] ignoreDone �ܾ���ť���º�ķ���ֵ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popAskDialog(int32_t& dialogId,
						 const QString& tip,
						 QWindow* parent,
						 const QString& title = QString::fromStdWString(L"11��սƽ̨"),
						 const QString& acceptText = QString::fromStdWString(L"ȷ��"),
						 const QString& ignoreText = QString::fromStdWString(L"ȡ��"),
						 int32_t acceptDone = ACCEPT_BUTTON,
						 int32_t ignoreDone = IGNORE_BUTTON,
						 int32_t timeOut = -1,
						 bool isCountDownVisible = false);

	/** ������ʾ��
	@param [out] dialogId ����IDֵ
	@param [in] tip ��ʾ����
	@param [in] title ����
	@param [in] parent ������ָ��
	@param [in] buttonText ��ť����
	@param [in] done ��ť���º�ķ���ֵ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popTipDialog(int32_t& dialogId,
						 const QString& tip,
						 const QString& title = QString::fromStdWString(L"11��սƽ̨"),
						 QWindow* parent = nullptr,
						 const QString& buttonText = QString::fromStdWString(L"ȷ��"),
						 int32_t done = ACCEPT_BUTTON,
						 int32_t timeOut = -1,
						 bool isCountDownVisible = false);

	/** ������ʾ��
	@param [out] dialogId ����IDֵ
	@param [in] tip ��ʾ����
	@param [in] parent ������ָ��
	@param [in] title ����
	@param [in] buttonText ��ť����
	@param [in] done ��ť���º�ķ���ֵ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popTipDialog(int32_t& dialogId,
						 const QString& tip,
						 QWindow* parent,
						 const QString& title = QString::fromStdWString(L"11��սƽ̨"),
						 const QString& buttonText = QString::fromStdWString(L"ȷ��"),
						 int32_t done = ACCEPT_BUTTON,
						 int32_t timeOut = -1,
						 bool isCountDownVisible = false);

	/** ���������
	@param [out] dialogId ����IDֵ
	@param [in,out] editText �����Ĭ������
	@param [in] editTip ��ʾ����
	@param [in] isPassword �Ƿ������Ϊ�����
	@param [in] title ����
	@param [in] parent ������ָ��
	@param [in] maxLength ������󳤶ȣ�-1��ʾ������
	@param [in] buttonText ��ť����
	@param [in] done ��ť���º�ķ���ֵ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ��ʱ�Զ��ر���ʾ�Ƿ�ɼ�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t popInputDialog(int32_t& dialogId,
						   QString& editText,
						   const QString& editTip,
						   bool isPassword = false,
						   const QString& title = QString::fromStdWString(L"11��սƽ̨"),
						   QWindow* parent = nullptr,
						   int32_t maxLength = -1,
						   const QString& buttonText = QString::fromStdWString(L"ȷ��"),
						   int32_t done = ACCEPT_BUTTON,
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

	/** ��ǰ��������
	@return ���ص�������
	*/
	int32_t dialogCount();

	/** ���ݴ���ָ�������д����л�ȡ����ID
	@param [in] base ����ָ��
	@return ���ش���ID
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

	/** ��ȡ�´���ID
	@return �����´���ID
	*/
	int32_t getId();

private:
	std::map<int32_t, DialogBase*> m_mapDialog;
	int32_t m_id;
};