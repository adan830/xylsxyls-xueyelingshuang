#pragma once
#include <afxwin.h>

class CstrValue{
	//1���ַ�����2��������3��С����-1��������ʽ���߳���
public:
	BOOL type;
	CString strValue;
	int nValue;
	double dValue;

public:
	CstrValue();
	CstrValue(CString strValue);
	CstrValue(const CstrValue& x);
	CstrValue operator = (const CstrValue& x);
	~CstrValue();
};