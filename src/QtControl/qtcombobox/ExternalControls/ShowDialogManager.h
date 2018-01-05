#pragma once
#include <map>
#include <stdint.h>
#include <QString>
#include "DialogManager.h"

class DialogBase;
class QWidget;
/** ��һʵ��������ͳһ�����ڴ����رգ�����Ķ���ӿڣ��������д���
DialogManager::instance().removeAll();
*/
class ShowDialogManager : public DialogManager
{
	Q_OBJECT
public:
	/** ��һʵ��
	@return ���ص�һʵ��
	*/
	static ShowDialogManager& instance();

	/** ��ʾ��ʾ��
	@param [out] dialogId ����IDֵ
	@param [in] userType �û��Զ���ֵ�������ڹر�ʱ�ᷢ���źţ��ź��к������ֵ
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] done ��ť���º�ķ���ֵ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ����ʱ�Ƿ���ʾ
	*/
	void showTipDialog(int32_t& dialogId,
					   int32_t userType,
					   const QString& title,
					   const QString& tip,
					   int32_t done,
					   const QString& buttonText = QString::fromStdWString(L"֪����"),
					   int32_t timeOut = -1,
					   bool isCountDownVisible = false);

	/** ��ʾѯ�ʿ�
	@param [out] dialogId ����IDֵ
	@param [in] userType �û��Զ���ֵ�������ڹر�ʱ�ᷢ���źţ��ź��к������ֵ
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] acceptDone ȷ�ϰ�ť���º�ķ���ֵ
	@param [in] ignoreDone ȡ����ť���º�ķ���ֵ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isCountDownVisible ����ʱ�Ƿ���ʾ
	*/
	void showAskDialog(int32_t& dialogId,
					   int32_t userType,
					   const QString& title,
					   const QString& tip,
					   int32_t acceptDone,
					   int32_t ignoreDone,
					   const QString& acceptText = QString::fromStdWString(L"ͬ��"),
					   const QString& ignoreText = QString::fromStdWString(L"�ܾ�"),
					   int32_t timeOut = -1,
					   bool isCountDownVisible = false);

	/** ��ʾ��¼��
	@param [out] dialogId ����IDֵ
	@param [in] userType �û��Զ���ֵ�������ڹر�ʱ�ᷢ���źţ��ź��к������ֵ
	@param [in] title ����
	@param [in] tip ��ʾ����
	@param [in] linkUrl �˽�������ӵ�ַ
	@param [in] timeOut ��ʱ�Զ��رգ���λ��
	@param [in] isUrlButtonVisible �˽���ఴť�Ƿ���ʾ
	@param [in] isCountDownVisible ����ʱ�Ƿ���ʾ
	*/
	void showLoginDialog(int32_t& dialogId,
						 int32_t userType,
						 const QString& title,
						 const QString& tip,
						 const QString& linkUrl,
						 int32_t timeOut = -1,
						 bool isUrlButtonVisible = false,
						 bool isCountDownVisible = false);
Q_SIGNALS:
	void dialogDone(int32_t dialogId, int32_t result, int32_t userType);
};