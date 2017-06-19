#include <SDKDDKVer.h>
#include "stdafx.h"
#include "ConfigInfo.h"
#include "CGetPath/CGetPathAPI.h"

ConfigInfo configInfo;

ConfigInfo::ConfigInfo(){
	storage[FillSearchInt] = 10000;
    storage[ShowPersonInt] = 10001;
	storage[Split] = "~!@#$%^&*()";
	storage[txtPath] = CGetPath::GetCurrentExePath() + "save.data";
    storage[notMarriage] = "δ��";
	storage[notMarriage1] = "δ��";
    storage[hasMarriage] = "�ѻ�";
	storage[hasMarriage1] = "�̻�δ��";
	storage[hasMarriage2] = "�ѻ�����";
	storage[noHouse] = "�޷�";
	storage[noHouse1] = "�޷�";
	storage[hasHouse] = "�з�";
	storage[hasHouse1] = "�з��д���";
	storage[hasHouse2] = "�з��޴���";
	storage[junior] = "��ר������";
	storage[junior1] = "��ר";
	storage[junior2] = "��ר";
	storage[college] = "���Ƽ�����";
	storage[college1] = "�Կ���ѧ";
	storage[college2] = "����";
	storage[college3] = "����";
	storage[college4] = "һ��";
	storage[college5] = "���ƺ�����ѧ";
	storage[college6] = "����˫ѧλ";
	storage[graduate] = "˶ʿ������";
	storage[graduate1] = "ѧ˶";
	storage[graduate2] = "ר˶";
	storage[graduate3] = "˶ʿ˫ѧλ";
	storage[graduate4] = "˶ʿ������ѧ";
	storage[philosophy] = "��ʿ";
	storage[philosophy1] = "��ʿ";
	storage[philosophy2] = "��ʿ������ѧ";
	storage[noMatter] = "����ν";
	storage[maxPeople] = 10000;
}