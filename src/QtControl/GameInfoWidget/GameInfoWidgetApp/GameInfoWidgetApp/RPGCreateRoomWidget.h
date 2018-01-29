#pragma once
#include <QWidget>
#include <QUrl>
#include <stdint.h>
#include "ExternalControls/ComboBox.h"
#include "../CW3LModalFrame.h"

class QEvent;
class QObject;
class Label;
class CWebViewEx;
class LineEdit;
class CheckBox;
class COriginalButton;
class CPasswordInputBox;
class RPGCreateRoomWidget : public CW3LModalFrame
{
	Q_OBJECT
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	RPGCreateRoomWidget(QWidget* parent = NULL);

	/** ��������
	*/
	virtual ~RPGCreateRoomWidget();

	/** ���õ�ͼ�汾
	@param [in] mapVersion ��ͼ�汾
	*/
	void setMapVersion(const QString& mapVersion);

	/** ��ȡ��ͼ�汾
	@return ���ص�ͼ�汾
	*/
	QString getMapVersion();

	/** ���õ�ͼ�汾�Ƿ����
	@param [in] enable �Ƿ����
	*/
	void setMapVersionEnable(bool enable);

	/** ������Ϸ����
	@param [in] gameName ��Ϸ����
	*/
	void setGameName(const QString& gameName);

	/** ��ȡ��Ϸ����
	@return ���ص�ͼ�汾
	*/
	QString getGameName();

	/** ������Ϸ�����Ƿ����
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

	/** ����ҳ�������пؼ�
	*/
	void resetSettings();

	/** �����Ϸ���ý���
	*/
	void clickGameSetting();

private:
	/** Ĭ�����ݳ�ʼ��
	*/
	void init();

	/** �����Ƿ�Ϊ������������ʾ��ʼ��Ϸ����������ʾ׼����Ϸ
	@param [in] isLeader �Ƿ�Ϊ����
	*/
	void setLeader(bool isLeader);

	void initGameSettingButton();

	void initGameSettingWidget();

	//����ַ����������ʾ������������ʽ
	void setComboBoxAttri(ComboBox* pBox,
						  const std::wstring& pattern = L"",
						  QRegExp* ex = nullptr,
						  QRegExpValidator* rep = nullptr);

	void resizeEvent(QResizeEvent* eve);

	void paintEvent(QPaintEvent* eve);
	//���пؼ�ͳһ����
	void layout();

private slots:
	void onExitClicked();
	void onJudgeChanged(int state);
	
Q_SIGNALS:
	void exitClicked();
	void createRoomClicked();
	void gameNameChanged(const QString &);
	void gamePasswordChanged(const QString &);
	void gameModeChanged(const QString&);
	void judgeChanged(bool);
	
private:
	Label* m_gameSetting;

	QWidget* m_gameSettingWidget;

	LineEdit* m_gameNameEdit;
	LineEdit* m_mapVersionEdit;
	CPasswordInputBox* m_gamePasswordEdit;
	ComboBox* m_gameModeComboBox;
	CheckBox* m_judgeCheckBox;
	Label* m_judgeCheckName;

	COriginalButton* m_exit;

	Label* m_mapVersion;
	Label* m_gameName;
	Label* m_gamePassword;
	Label* m_gameMode;
	COriginalButton* m_createRoom;

	//��������߶�
	int32_t m_rpgCreateRoomWidgetHeight;

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

	QString m_war3ResourcePath;
	bool m_isLeader;
};
