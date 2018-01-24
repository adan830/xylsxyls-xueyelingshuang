#pragma once
#include "DialogBase.h"
#include <QPropertyAnimation>

/** ���ڻ���ģ�ͣ�ʵ��ͨ�ò���
*/
class DialogShow : public DialogBase
{
	Q_OBJECT
public:
	/** ���캯��
	*/
	DialogShow();

	/** ����Ĭ�Ͽؼ������йرհ�ť�����⣬�ָ��ߣ����С��������ɫ�������߿�
	*/
	void initForExec();

	/** ����Ĭ�Ͽؼ������б�����
	@param [in] dialogWidth ���
	@param [in] dialogHeight �߶�
	@param [in] typeName ������
	*/
	void initForShow(int32_t dialogWidth, int32_t dialogHeight, const std::string& typeName);

	/** ���ùرհ�ť�Ƿ�ɼ�������Ի����йرհ�ť���ɼ���ͬʱ��ȡ��Esc��Alt+F4��ʹ��
	@param [in] visible �Ƿ�ɼ�
	*/
	void setExitVisible(bool visible);

Q_SIGNALS:
	/** ��֪ͨ�򴰿ڹر�ʱ�����źţ��ڹرն���ִ��֮ǰ�����ź�
	@param [in] dialogId ����ID
	@param [in] result ���ڹر�ʱ�����ķ���ֵ
	@param [in] userType �û��Զ���ֵ
	*/
	void dialogDone(int32_t dialogId, int32_t result, int32_t userType);

protected:
	void paintEvent(QPaintEvent* eve);
	void mousePressEvent(QMouseEvent* eve);
	void mouseMoveEvent(QMouseEvent* eve);
	void mouseReleaseEvent(QMouseEvent* eve);
	void keyPressEvent(QKeyEvent* eve);
	void closeEvent(QCloseEvent* eve);
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	void showEvent(QShowEvent* eve);

	void done(int result);
	void end();

private slots:
	void timeUpdate(int32_t timeOut);

private:
	void ncActiveChanged(int32_t wParam);
	
protected:
	COriginalButton* m_exit;
	Label* m_title;
	Label* m_separator;
	Label* m_time;
	Label* m_titleBar;
	Label* m_icon;
	int32_t m_userType;

private:
	bool m_bPressed;
	bool m_highLight;
	QPoint m_point;
	bool m_cancelEscAltF4;
	bool m_isExec;
	QPropertyAnimation m_animation;
	int32_t m_result;
	QRect m_beginRect;
	QRect m_endRect;
};