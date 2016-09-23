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
	//��ѯ�˴�����ֶ������ᵼ�¼�¼����ֶ�����
	CRecord& operator[](CString Field);
	//����¼��ֵ�ֶ�ֵ�������������
	CRecord operator=(const CValue& value);

public:
	//һ������������������ԣ������ֶ���������
	CAttri* operator->();
	CValue toValue();

public:
	CString ToCString();

};