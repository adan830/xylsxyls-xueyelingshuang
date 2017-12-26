#pragma once
#include "DialogBase.h"

/** ���������ģ�ͣ�ʵ��ͨ�ò���
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
	void init();

	/** ���ùرհ�ť�Ƿ�ɼ�������Ի����йرհ�ť���ɼ���ͬʱ��ȡ��Esc��Alt+F4��ʹ��
	@param [in] visible �Ƿ�ɼ�
	*/
	void setExitVisible(bool visible);

private slots:
	void timeUpdate(int32_t timeOut);

private:
	void paintEvent(QPaintEvent* eve);
	void mousePressEvent(QMouseEvent* eve);
	void mouseMoveEvent(QMouseEvent* eve);
	void mouseReleaseEvent(QMouseEvent* eve);
	void keyPressEvent(QKeyEvent* eve);
	void closeEvent(QCloseEvent* eve);
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);

private:
	void ncActiveChanged(int32_t wParam);
	
protected:
	COriginalButton* m_exit;
	Label* m_title;
	Label* m_separator;
	Label* m_time;

private:
	bool m_bPressed;
	bool m_highLight;
	QPoint m_point;
	bool m_cancelEscAltF4;
};