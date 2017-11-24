#pragma once
#include <QWidget>
#include <QUrl>
#include <QtWebKitWidgets/QWebView>
#include <stdint.h>

class Label;
class QWebView;
class LineEdit;
class CheckBox;
class ComboBox;
class COriginalButton2;
class CPasswordInputBox2;
class GameInfoWidget : public QWidget
{
	Q_OBJECT
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	GameInfoWidget(QWidget* parent = NULL);

	virtual ~GameInfoWidget(){};

	/** ������Ϸ������
	@param [in] gameName ��Ϸ������
	*/
	void setGameName(const QString& gameName);

	/** ��ȡ��Ϸ������
	@return ������Ϸ������
	*/
	QString getGameName();

	/** ������Ϸ������
	@param [in] gamePassword ��Ϸ������
	*/
	void setGamePassword(const QString& gamePassword);

	/** ��ȡ��Ϸ������
	@return ������Ϸ������
	*/
	QString getGamePassword();

	/** ������Ϸ��ģʽ
	@param [in] gameModeList ��Ϸ��ģʽ
	*/
	void setGameModeList(const QStringList& gameModeList);

	/** ���õ�ǰ��Ϸ��ģʽ
	@param [in] gameMode ��Ϸ��ģʽ
	*/
	void setCurGameMode(const QString& gameMode);

	/** ��ȡ��ǰѡ�����Ϸ��ģʽ
	@return ���ص�ǰѡ�����Ϸ��ģʽ
	*/
	QString getCurGameMode();

	/** ��������Lv����
	@param [in] gameLvList ����Lv����
	*/
	void setGameLvList(const QStringList& gameLvList);

	/** ���õ�ǰ����Lv����
	@param [in] gameLv ����Lv����
	*/
	void setCurGameLv(const QString& gameLv);

	/** ��ȡ��ǰѡ�������Lv����
	@return ���ص�ǰѡ�������Lv����
	*/
	QString getCurGameLv();

	/** ����MVP����
	@param [in] gameMVPList MVP����
	*/
	void setGameMVPList(const QStringList& gameMVPList);

	/** ���һ��MVP����
	@param [in] gameMVP MVP����
	*/
	void setCurGameMVP(const QString& gameMVP);

	/** ��ȡ��ǰѡ���MVP����
	@return ���ص�ǰѡ���MVP����
	*/
	QString getCurGameMVP();

	/** ������������
	@param [in] gameNetList ��������
	*/
	void setGameNetList(const QStringList& gameNetList);

	/** ���õ�ǰ��������
	@param [in] gameNet ��������
	*/
	void setCurGameNet(const QString& gameNet);

	/** ��ȡ��ǰѡ�����������
	@return ���ص�ǰѡ�����������
	*/
	QString getCurGameNet();

	/** ���õ���������
	@param [in] gameLeaveList ����������
	*/
	void setGameLeaveList(const QStringList& gameLeaveList);

	/** ��ȡ��ǰ����������
	@param [in] gameLeave ����������
	*/
	void setCurGameLeave(const QString& gameLeave);

	/** ��ȡ��ǰѡ��ĵ���������
	@return ���ص�ǰѡ��ĵ���������
	*/
	QString getCurGameLeave();

	/** �����Ƿ�������λ
	@param [in] judge �Ƿ�������λ
	*/
	void setJudge(bool judge);

	/** ��ȡ��ǰ�Ƿ����˲���λ
	@return ���ص�ǰ�Ƿ����˲���λ
	*/
	bool getJudge();
	
private:
	/** Ĭ�����ݳ�ʼ��
	*/
	void init();

	void initGameSettingButton();
	void initPersonalRecordButton();
	void initMyToolButton();

	void initGameSettingWidget();
	void initPersonalRecordWidget();
	void initMyToolButtonWidget();

	void resizeEvent(QResizeEvent* eve);
	//���пؼ�ͳһ����
	void layout();

private slots:
	void onGameSettingClicked();
	void onPersonalRecordClicked();
	void onMyToolClicked();

private:
	COriginalButton2* m_gameSetting;
	COriginalButton2* m_personalRecord;
	COriginalButton2* m_myTool;

	QWidget* m_gameSettingWidget;
	QWidget* m_personalRecordWidget;
	QWidget* m_myToolWidget;

	LineEdit* m_gameNameEdit;
	CPasswordInputBox2* m_gamePasswordEdit;
	ComboBox* m_gameModeComboBox;
	ComboBox* m_gameLvComboBox;
	ComboBox* m_gameMVPComboBox;
	ComboBox* m_gameNetComboBox;
	ComboBox* m_gameLeaveComboBox;
	CheckBox* m_judgeCheckBox;

	COriginalButton2* m_inviteFriend;
	COriginalButton2* m_startGame;
	COriginalButton2* m_exit;

	QWebView* m_myToolWebView;
	QWebView* m_personalRecordWebView;
	QWebView* m_gameSettingWebView;

	Label* m_gameName;
	Label* m_gamePassword;
	Label* m_gameMode;
	Label* m_gameLv;
	Label* m_gameMVP;
	Label* m_gameNet;
	Label* m_gameLeave;
	COriginalButton2* m_save;

	public:
	//��������߶�
	int32_t m_gameInfoWidgetHeight;

	//��ť��Ӧ��widget�߶�
	int32_t m_widgetHeight;

	//��Ϸ������ҳ��ʼ�߶�
	int32_t m_gameSettingWebviewOrigin;

	//������Ѱ�ť��ʼ�߶�
	int32_t m_inviteFriendOrigin;

	// ��ʼ��Ϸ��ť������ʼλ��
	int32_t m_startGameOrigin_y;

	//�˳���ť������ʼλ��
	int32_t m_exitOrigin_y;
};