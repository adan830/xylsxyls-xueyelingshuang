#pragma once
#include <afxwin.h>
#include <map>
using namespace std;
#include "CValue.h"

class CTable;
class CRecord{
public:
	//��ʹ��table�ж����ֶ�����ģʽ����Ϊ�޷�������ֶ�
	map<CString,CValue> mapValue;

	CString strCurrentField;
	CTable* pTable;
public:
	CRecord(CTable* pTable);
	CRecord(const CRecord& record);
	CRecord operator=(const CRecord& record);

public:
	//ֻ��ʹ�÷��ر���ķ�ʽ���������CValue�������CValue����CTable�ľ�̬����
	//CRecord& operator[](CString Field);
	CRecord& operator[](CString Field);
	//����¼��ֵ�ֶ�ֵ
	CRecord operator=(const CValue& value);
	
	
	
public:
	CAttri* operator->();

public:
	CValue toValue();

public:
	CString ToCString();

};