#pragma once
#include <afxwin.h>
#include "CBase64Macro.h"

class CBase64API CBase64{
	//�����Ƿ��������п��ܺ��йؼ��ַ���������԰ѹؼ��ַ�ת�ɷǹؼ��ַ�������\0
public:  
    //���룬�׵�ַ�������ֽ�����������\0�����������
    CString Encode(const unsigned char* Data,int DataByte);  
    //���룬�׵�ַ�������ֽ����������ĳ��ȣ�����\0�����ؽ�����ַ�����\0����
    CString Decode(const char* Data,int DataByte,int* pOutByte);
};