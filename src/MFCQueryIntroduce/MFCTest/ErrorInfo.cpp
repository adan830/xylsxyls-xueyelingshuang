#include <SDKDDKVer.h>
#include "ErrorInfo.h"

ErrorInfo errorInfo;

ErrorInfo::ErrorInfo(){
	storage[Success] = "�˶Գɹ�";
	storage[Name] = "���ֵĳ���Ϊ2-5����";
	storage[Birth] = "����Ϊ������Ŀ";
	storage[Sex] = "�Ա�Ϊ������Ŀ";
	storage[Marriage] = "���Ϊ������Ŀ";
	storage[Education] = "ѧ��Ϊ������Ŀ";
}