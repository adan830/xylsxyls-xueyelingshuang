#pragma once
#include <afxwin.h>
#include <string>
using namespace std;

class CAttri;
class CTable;
class CValue{
	//1���ַ�����2��������3��С����-1��������ʽ���߳���
public:
	BOOL Type;
	CString strValue;
	int nValue;
	double dValue;
	//ת�����е�map�ֶ�
	static CTable* pTable;
	
public:
	CValue();
	CValue(CString strValue);
	CValue(char* szValue);
	CValue(string strValue);
	CValue(int nValue);
	CValue(double dValue);

	CValue(const CValue& value);
	CValue operator = (const CValue& value);
	bool operator== (const CValue& value);
	bool operator!= (const CValue& value);

public:
	CAttri* operator->();
};