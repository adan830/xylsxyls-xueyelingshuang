#pragma once
#include <afxwin.h>
#include <map>
using namespace std;
#include "CValue.h"

class CRecord{
public:
	//��ʹ��table�ж����ֶ�����ģʽ����Ϊ�޷�������ֶ�
	map<CString,CValue> mapValue;

	CString strCurrentField;
public:
	CRecord();
	CRecord(const CRecord& record);
	CRecord operator=(const CRecord& record);

public:
	//���ﲻ�������ã���Ϊ����������������˾ֲ�����
	CValue operator[](CString Field);

public:
	CString ToCString();

};