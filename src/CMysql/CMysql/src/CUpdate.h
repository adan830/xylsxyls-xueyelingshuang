#pragma once
#include <afxwin.h>
#include <map>
using namespace std;
#include "CValue.h"

class CUpdate{
public:
public:
	//һ����¼���ֶ�����Ӧ�ֶ�ֵ
	map<CString,CValue> mapValue;
	CString strCurrentField;

public:
	CUpdate();
	CUpdate(const CUpdate& upd);
	CUpdate operator=(const CUpdate& upd);
public:
	CUpdate operator=(const CValue& value);
	CUpdate& operator[](CString Field);
	
public:
	CString ToCString();
};