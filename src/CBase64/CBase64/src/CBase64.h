#pragma once
#include <string>
#include "CBase64Macro.h"
using namespace std;

class CBase64API CBase64{
	//�����Ƿ��������п��ܺ��йؼ��ַ���������԰ѹؼ��ַ�ת�ɷǹؼ��ַ�������\0
public:  
    //���룬�׵�ַ�������ֽ�����������\0�����������
    string Encode(const unsigned char* Data,int DataByte);  
    //���룬�׵�ַ�������ֽ����������ĳ��ȣ�����\0�����ؽ�����ַ�����\0����
    string Decode(const char* Data,int DataByte,int* pOutByte);
};