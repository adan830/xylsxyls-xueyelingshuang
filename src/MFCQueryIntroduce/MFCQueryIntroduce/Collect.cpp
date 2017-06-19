#include <SDKDDKVer.h>
#include "stdafx.h"
#include "Collect.h"
#include <afx.h>
#include "ConfigInfo.h"
#include "ErrorInfo.h"

void Collect::GetSearchInfo(Search* search,HWND hwnd){
	//?������Ϣ�ý����person����
    ::SendMessage(hwnd, GetConfig(FillSearchInt, int), NULL, (LPARAM)search);
}

void Collect::ShowPerson(Person* person, HWND hwnd){
    //?������Ϣ��person��Ϣ�͵�����
    ::SendMessage(hwnd, GetConfig(ShowPersonInt, int), NULL, (LPARAM)person);
}

int Collect::CheckName(Person* person){
    if (person->name.length() <= 2 || person->name.length() > 10) return NameError;
	else return 0;
}

int Collect::CheckBirth(Person* person){
    if (person->birth.toString().find("-00") != -1 || person->birth.toString().find("0000") != -1) return BirthError;
	else return 0;
}

int Collect::CheckSex(Person* person){
	if (person->sex == "") return SexError;
	else return 0;
}

int Collect::CheckMarriage(Person* person){
    if (person->marriage == "") return MarriageError;
	else return 0;
}

int Collect::CheckEducation(Person* person){
    if (person->education == "") return EducationError;
	else return 0;
}