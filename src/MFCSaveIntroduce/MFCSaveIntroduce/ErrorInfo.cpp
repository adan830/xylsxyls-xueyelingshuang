#include <SDKDDKVer.h>
#include "ErrorInfo.h"

ErrorInfo errorInfo;

ErrorInfo::ErrorInfo(){
	storage[Success] = string("�˶Գɹ�");
	storage[NameError] = string("���ֵĳ���Ϊ2-5����");
	storage[BirthError] = string("����Ϊ������Ŀ");
	storage[SexError] = string("�Ա�Ϊ������Ŀ");
	storage[MarriageError] = string("���Ϊ������Ŀ");
	storage[EducationError] = string("ѧ��Ϊ������Ŀ");
}