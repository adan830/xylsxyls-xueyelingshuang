#include <SDKDDKVer.h>
#include "ErrorInfo.h"

ErrorInfo errorInfo;

ErrorInfo::ErrorInfo(){
	storage[Success] = string("�˶Գɹ�");
	storage[Name] = string("���ֵĳ���Ϊ2-5����");
	storage[Birth] = string("����Ϊ������Ŀ");
	storage[Sex] = string("�Ա�Ϊ������Ŀ");
	storage[Marriage] = string("���Ϊ������Ŀ");
	storage[Education] = string("ѧ��Ϊ������Ŀ");
}