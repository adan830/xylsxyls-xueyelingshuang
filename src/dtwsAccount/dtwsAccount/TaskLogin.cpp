#include "TaskLogin.h"
#include "Ctxt/CtxtAPI.h"
#include "ConfigInfo.h"
#include "CMouse/CMouseAPI.h"
#include "CKeyboard/CKeyboardAPI.h"
#include "CScreenEx.h"

TaskLogin::TaskLogin(){
	Ctxt txt(configInfo[ConfigInfo::accountPath].toValue<string>());
	txt.LoadTxt(2, "~!@#$%^&*()");
	//?��ȡ�ڼ����˺�
	int n = atoi(txt.vectxt.at(0).at(0).c_str());
	//?��һ���˺ţ��ڶ������룬����������
	account = txt.vectxt.at(n).at(ConfigInfo::accountNum);
	password = txt.vectxt.at(n).at(ConfigInfo::passwordNum);
	bigServerName = txt.vectxt.at(n).at(ConfigInfo::bigServerNameNum);
	smallServerName = txt.vectxt.at(n).at(ConfigInfo::smallServerNameNum);
}

int TaskLogin::Run(){
	//?����ƶ�����¼�Ի��򲢵���
	CMouse::MoveAbsolute(configInfo[ConfigInfo::loginPoint].toValue<Point>());
	CMouse::LeftClick();
	//?�����˺�\t����\n
	CKeyboard::InputString(account + "\t" + password + "\n");

	//?�ȴ�����ʼ�������Ļ���Ƿ��з�������������
	int x, y;
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::serverNameRect].toValue<Rect>(), configInfo[ConfigInfo::serverNamePicPath].toValue<string>(), x, y, 1000, 10, "TaskLogin::Run serverNamePicPath error");
	//?���ݽ�ɫ��������ѡ�����
	vector<string> picPath;
	picPath.push_back(configInfo[ConfigInfo::picPath].toValue<string>() + bigServerName + configInfo[ConfigInfo::selected].toValue<string>() + configInfo[ConfigInfo::bmp].toValue<string>());
	picPath.push_back(configInfo[ConfigInfo::picPath].toValue<string>() + bigServerName + configInfo[ConfigInfo::notSelected].toValue<string>() + configInfo[ConfigInfo::bmp].toValue<string>());
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::bigServerAreaRect].toValue<Rect>(), picPath, x, y, 1000, 10, "TaskLogin::Run bigServerAreaRect error");
	CMouse::MoveAbsolute(Point(x, y));
	CMouse::LeftClick();
	//?ѡ��С��
	picPath.clear();
	picPath.push_back(configInfo[ConfigInfo::picPath].toValue<string>() + smallServerName + configInfo[ConfigInfo::selected].toValue<string>() + configInfo[ConfigInfo::bmp].toValue<string>());
	picPath.push_back(configInfo[ConfigInfo::picPath].toValue<string>() + smallServerName + configInfo[ConfigInfo::notSelected].toValue<string>() + configInfo[ConfigInfo::bmp].toValue<string>());
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::smallServerAreaRect].toValue<Rect>(), picPath, x, y, 1000, 10, "TaskLogin::Run smallServerAreaRect error");
	CMouse::MoveAbsolute(Point(x, y));
	CMouse::LeftClick();
	//?�����¼ȷ��
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::loginConfirmRect].toValue<Rect>(), configInfo[ConfigInfo::loginConfirmPicPath].toValue<string>(), x, y, 1000, 10, "TaskLogin::Run loginConfirmRect error");
	CMouse::MoveAbsolute(Point(x, y));
	CMouse::LeftClick();
	return CTask::RUNSUCCESS;
}

void TaskLogin::SuspendRun(){

}