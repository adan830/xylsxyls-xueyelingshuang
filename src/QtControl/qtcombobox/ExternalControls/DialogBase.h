#pragma once
#include <QDialog>
#include <stdint.h>

class Label;
class COriginalButton;
class QSplitter;
class LineEdit;
class CPasswordInputBox;
/** ��������࣬ʵ�ֻ����ӿ�
*/
class DialogBase : public QDialog
{
	Q_OBJECT
public:
	/** ���캯��
	*/
	DialogBase();

	/** չʾ����
	@param [in] timeOut �Զ��ر�ʱ�䣬��λ�룬����������ʾ�����Զ��ر�
	@return �رմ���ʱ���ķ���ֵ
	*/
	int32_t exec(int32_t timeOut = -1);

	/** ������ǩ���ֲ�����
	@param [in] text �ı�����
	@param [in] rect ��ǩ��Ը���������λ��
	@param [in] textColor ������ɫ
	@return ���ر�ǩָ��
	*/
	Label* addLabel(const QString& text, const QRect& rect, const QColor& textColor);

	/** ������ʾ���ֲ����ã����У�
	@param [in] text �ı�����
	@param [in] rect ��ǩ��Ը���������λ��
	@param [in] textColor ������ɫ
	@return ���ر�ǩָ��
	*/
	Label* addTip(const QString& text, const QRect& rect, const QColor& textColor);

	/** ������ť�����ã���ť������رմ���
	@param [in] text ��ť���ı�����
	@param [in] rect ��ť��Ը���������λ��
	@param [in] result �رմ��ں�ķ���ֵ
	@return ���ذ�ťָ��
	*/
	COriginalButton* addButton(const QString& text, const QRect& rect, int32_t result);

	/** ��ӷָ���
	@param [in] point ��ʼ��
	@param [in] width ���
	@param [in] isHorizon �Ƿ�ˮƽ
	@return ���طָ���ָ��
	*/
	Label* addSeparator(const QPoint& point, int32_t width, bool isHorizon);

	/** ��ӵ����ı���
	@param [in] rect ��ǩ��Ը���������λ��
	@param [in] defaultText Ĭ����ʾ����
	@return �����ı���ָ��
	*/
	LineEdit* addLineEdit(const QRect& rect, const QString& defaultText = "");

	/** ��������
	@param [in] rect ��ǩ��Ը���������λ��
	@param [in] defaultText Ĭ����ʾ����
	@return �����ı���ָ��
	*/
	CPasswordInputBox* addPasswordInputBox(const QRect& rect, const QString& defaultText = "");

	/** ���õ���ⲿʱ����Ӧ������˸�ĸ�����
	@param [in] parent ������ָ��
	*/
	void setResponseHighlightDialog(QDialog* parent);

Q_SIGNALS:
	void timeRest(int32_t seconds);

private slots:
	void endDialog();

private:
	void showEvent(QShowEvent* eve);
	void timerEvent(QTimerEvent* eve);

private:
	int32_t m_timeRest;
	int32_t m_timeId;
	std::map<void*, int32_t> m_mapResult;
};