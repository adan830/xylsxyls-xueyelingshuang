#pragma once
#include <SDKDDKVer.h>
#include <afx.h>

class CValue{
	//1���ַ�����2��������3��С����-1��������ʽ���߳���
public:
	BOOL Type;
	CString strValue;
	int nValue;
	double dValue;
	
public:
	CValue();
	CValue(CString strValue);
	CValue(int nValue);
	CValue(double dValue);

	CValue(const CValue& value);
	CValue operator = (const CValue& value);
	bool operator== (const CValue& value);
	bool operator!= (const CValue& value);
};