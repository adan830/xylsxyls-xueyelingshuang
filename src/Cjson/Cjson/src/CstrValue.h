#pragma once

#include "CjsonMacro.h"
typedef int BOOL;
#include <string>
using namespace std;

class CjsonAPI CstrValue{
	//1���ַ�����2��������3��С����-1��������ʽ���߳���
public:
	BOOL type;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string strValue;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
	int nValue;
	double dValue;

public:
	CstrValue();
	CstrValue(BOOL type,string strValue,int nValue,double dValue);
	CstrValue(string strValue);
	CstrValue(const CstrValue& x);
	CstrValue operator= (const CstrValue& x);

public:
	operator int();
	operator string();
	operator double();

public:
	~CstrValue();
};