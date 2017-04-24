#include "TaskCreateAccount.h"
#include "CScreenEx.h"
#include "Ctxt/CtxtAPI.h"
#include "ConfigInfo.h"
#include "CMouse/CMouseAPI.h"
#include "CKeyboard/CKeyboardAPI.h"

int TaskCreateAccount::initRun(){
	//?���txt�ĵ��е�ǰ�˺����Ƿ񴴽�
	Ctxt txt(configInfo[ConfigInfo::accountPath].toValue<string>());
	txt.LoadTxt(2, "~!@#$%^&*()");
	int n = atoi(txt.vectxt.at(0).at(0).c_str());
	job = txt.vectxt.at(n).at(ConfigInfo::jobNum);
	name = txt.vectxt.at(n).at(ConfigInfo::NameNum);
	//?����Ѿ��ɹ������˸��˺������������
	if (txt.vectxt.at(n).at(ConfigInfo::ifCreatedNum) == configInfo[ConfigInfo::hasCreated].toValue<string>()) return !CTask::INITSUCCESS;
	return CTask::INITSUCCESS;
}

int TaskCreateAccount::Run(){
	//?�ȴ�����ʼ�������Ļ���Ƿ��з�������������
	int x, y;
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::createCharacterRect].toValue<Rect>(), configInfo[ConfigInfo::createCharacterPicPath].toValue<string>(), x, y, 1000, 10, "TaskCreateAccount::Run createCharacterRect error");
	CMouse::MoveAbsolute(Point(x, y));
	CMouse::LeftClick();
	//?�Ȱ�����ƿ�
	CMouse::MoveAbsolute(configInfo[ConfigInfo::createBeginMove].toValue<Point>());
	//?��������ְҵ
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::jobRect].toValue<Rect>(), configInfo[ConfigInfo::picPath].toValue<string>() + job + configInfo[ConfigInfo::bmp].toValue<string>(), x, y, 1000, 10, "TaskCreateAccount::Run jobRect error");
	CMouse::MoveAbsolute(Point(x, y));
	CMouse::LeftClick();
	//?���������һ��
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::createNextRect].toValue<Rect>(), configInfo[ConfigInfo::createNextPicPath].toValue<string>(), x, y, 1000, 10, "TaskCreateAccount::Run createNextRect error");
	//?�����޷�ͨ����ɫ���ң��ײ���������⣬ֻ��ͨ��Sleep�ȴ�
	Sleep(configInfo[ConfigInfo::createNextSleep].toValue<int>());
	CMouse::MoveAbsolute(Point(x, y));
	CMouse::LeftClick();
	//?����ƿ�
	CMouse::MoveAbsolute(configInfo[ConfigInfo::moveCreateConfirm].toValue<Point>());
	//?�ȴ�����ȷ������
	CScreenEx::ChokeFindPic(configInfo[ConfigInfo::rect8].toValue<Rect>(), configInfo[ConfigInfo::createConfirmPicPath].toValue<string>(), x, y, 1000, 10, "TaskCreateAccount::Run createConfirmPicPath error");
	//?��������������
	CMouse::MoveAbsolute(configInfo[ConfigInfo::namePoint].toValue<Point>());
	CMouse::LeftClick();
	CKeyboard::InputString(name);
	CMouse::MoveAbsolute(Point(x, y));
	CMouse::LeftClick();
	return CTask::RUNSUCCESS;
}

void TaskCreateAccount::SuspendRun(){

}

void TaskCreateAccount::ExceptionRun(int exception){
	//?����Ҫ����ʱ����Ҫ�����⴦��
}