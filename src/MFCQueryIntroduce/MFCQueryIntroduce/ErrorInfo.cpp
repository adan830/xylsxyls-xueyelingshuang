#include <SDKDDKVer.h>
#include "stdafx.h"
#include "ErrorInfo.h"

ErrorInfo errorInfo;

ErrorInfo::ErrorInfo(){
	storage[Success] = "�˶Գɹ�";
	storage[NameError] = "���ֵĳ���Ϊ2-5����";
	storage[BirthError] = "����Ϊ������Ŀ";
	storage[SexError] = "�Ա�Ϊ������Ŀ";
	storage[MarriageError] = "���Ϊ������Ŀ";
	storage[EducationError] = "ѧ��Ϊ������Ŀ";
}