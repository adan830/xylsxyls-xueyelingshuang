#pragma once
#include <QWidget>
#include <QUrl>
#include <QtWebKitWidgets/QWebView>
#include <stdint.h>
#include "fromYangNan/ComboBox.h"

class QEvent;
class QObject;
class Label;
class QWebView;
class LineEdit;
class CheckBox;
class COriginalButton;
class CPasswordInputBox;
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

	/** ������Ϸ�������Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setGameNameEnable(bool enable);

	/** ������Ϸ������
	@param [in] gamePassword ��Ϸ������
	*/
	void setGamePassword(const QString& gamePassword);

	/** ��ȡ��Ϸ������
	@return ������Ϸ������
	*/
	QString getGamePassword();

	/** ������Ϸ�������Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setGamePasswordEnable(bool enable);

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

	/** ������Ϸ��ģʽ�Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setGameModeEnable(bool enable);

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

	/** ��������Lv�����Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setGameLvEnable(bool enable);

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

	/** ����MVP�����Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setGameMVPEnable(bool enable);

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

	/** �������������Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setGameNetEnable(bool enable);

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

	/** ���õ����������Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setGameLeaveEnable(bool enable);

	/** �����Ƿ�������λ
	@param [in] judge �Ƿ�������λ
	*/
	void setJudge(bool judge);

	/** ��ȡ��ǰ�Ƿ����˲���λ
	@return ���ص�ǰ�Ƿ����˲���λ
	*/
	bool getJudge();

	/** ���ò���λ�Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setJudgeEnable(bool enable);

	/** ���ñ����Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setSaveEnable(bool enable);

	/** ������������Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setInviteFriendEnable(bool enable);

	/** ���ÿ�ʼ��Ϸ�Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setStartGameEnable(bool enable);

	/** �����˳��Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setExitEnable(bool enable);

	/** ������Ϸ���ý�����ҳ����
	@param [in] web ��ַ
	*/
	void setGameSettingWebView(const QString& web);

	/** ���ø���ս��������ҳ����
	@param [in] web ��ַ
	*/
	void setPersonalRecordWebView(const QString& web);

	/** �����ҵĵ��߽�����ҳ����
	@param [in] web ��ַ
	*/
	void setMyToolWebView(const QString& web);
	
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

	//����ַ����������ʾ������������ʽ
	void setComboBoxAttri(ComboBox* pBox, const std::wstring& pattern = L"", QRegExpValidator* rep = nullptr);

	bool mouseInWithoutDropDown(ComboBox* pBox);

	void setComboBoxEditAttri(ComboBox* pBox, std::wstring& curText);

	void setComboBoxUnEditAttri(ComboBox* pBox, const std::wstring& flag, std::wstring& curText);

	void resizeEvent(QResizeEvent* eve);
	//���пؼ�ͳһ����
	void layout();

	bool eventFilter(QObject* target, QEvent* eve);

private slots:
	void onGameSettingClicked();
	void onPersonalRecordClicked();
	void onMyToolClicked();
	void onGameSettingLinkClicked(const QUrl& url);
	void onPersonalRecordLinkClicked(const QUrl& url);
	void onMyToolLinkClicked(const QUrl& url);

Q_SIGNALS:
	void onSaveClicked();
	void onInviteFriendClicked();
	void onStartGameClicked();
	void onExitClicked();
	void onGameNameChanged(const QString &);
	void onGamePasswordChanged(const QString &);
	void onGameModeChanged(const QString&);
	void onGameLvChanged(const QString &);
	void onGameMVPChanged(const QString &);
	void onGameNetChanged(const QString &);
	void onGameLeaveChanged(const QString &);
	void onJudgeChanged(int);
	void onGameSettingLinkClicked(const QString&);
	void onPersonalRecordLinkClicked(const QString&);
	void onMyToolLinkClicked(const QString&);
	
private:
	COriginalButton* m_gameSetting;
	COriginalButton* m_personalRecord;
	COriginalButton* m_myTool;

	QWidget* m_gameSettingWidget;
	QWidget* m_personalRecordWidget;
	QWidget* m_myToolWidget;

	LineEdit* m_gameNameEdit;
	CPasswordInputBox* m_gamePasswordEdit;
	ComboBox* m_gameModeComboBox;
	ComboBox* m_gameLvComboBox;
	ComboBox* m_gameMVPComboBox;
	ComboBox* m_gameNetComboBox;
	ComboBox* m_gameLeaveComboBox;
	CheckBox* m_judgeCheckBox;

	COriginalButton* m_inviteFriend;
	COriginalButton* m_startGame;
	COriginalButton* m_exit;

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
	COriginalButton* m_save;

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

	QRegExpValidator m_lvRep;
	QRegExpValidator m_MVPRep;
	QRegExpValidator m_netRep;
	QRegExpValidator m_leaveRep;

	std::wstring m_gameLvCurText;
	std::wstring m_gameMVPCurText;
	std::wstring m_gameNetCurText;
	std::wstring m_gameLeaveCurText;

	QString m_war3ResourcePath;
};
