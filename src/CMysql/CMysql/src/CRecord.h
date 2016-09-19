#pragma once
#include <afxwin.h>
#include <map>
using namespace std;
#include "CValue.h"
#include "CAttri.h"

class CAttri;
class CRecord{
public:
	//ʹ��table�е��ֶ���
	map<CString,CValue> mapValue;

	CString strCurrentField;
public:
	CRecord();
	CRecord(const CRecord& record);
	CRecord operator=(const CRecord& record);

public:
	CValue operator[](CString Field);

public:
	CString ToCString();
};