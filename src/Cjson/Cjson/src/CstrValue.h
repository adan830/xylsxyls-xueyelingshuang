#pragma once
#include <afxwin.h>
#include "CjsonMacro.h"

class CjsonAPI CstrValue{
	//1���ַ�����2��������3��С����-1��������ʽ���߳���
public:
	BOOL type;
	CString strValue;
	int nValue;
	double dValue;

public:
	CstrValue();
	CstrValue(BOOL type,CString strValue,int nValue,double dValue);
	CstrValue(CString strValue);
	CstrValue(const CstrValue& x);
	CstrValue operator= (const CstrValue& x);

public:
	operator int();
	operator CString();
	operator double();

public:
	~CstrValue();
};