#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "CField.h"
#include "CFieldValue.h"
#include "API.h"
#include <vector>
using namespace std;
#include <stdarg.h>

class CField;
class CFieldValue;
//����ֶ�ֵ���һ����ÿ���ֶ�ֵ�����Լ����ֶ�����

class CMysqlAPI CRecord{
public:
	//������¼�����������ֶ�ֵ
	vector<CFieldValue> vecFieldValue;
	//��CRecord��Ϊ��¼����ʱ���м�����ӷ�
	vector<CString> vecCondition;

public:
	CRecord();
	CRecord(CField      x);
	CRecord(CFieldValue x);

public:
	CRecord operator = (CField      x);
	CRecord operator = (CFieldValue x);

	friend CRecord CMysqlAPI operator + (CRecord     x,CFieldValue y);
	friend CRecord CMysqlAPI operator + (CFieldValue x,CRecord     y);
	friend CRecord CMysqlAPI operator + (CRecord     x,CRecord     y);
	//����û�а취��ȫ���ε������������Ҫ�����������ж�
	friend CRecord CMysqlAPI operator + (CRecord     x,CString     y);
	friend CRecord CMysqlAPI operator + (CFieldValue x,CString     y);
	friend CRecord CMysqlAPI operator + (CFieldValue x,CFieldValue y);

	friend CRecord CMysqlAPI operator + (CRecord     x,CField      y);
	friend CRecord CMysqlAPI operator + (CField      x,CRecord     y);
	friend CRecord CMysqlAPI operator + (CField      x,CField      y);

public:
	//��CTable��һ���Ի�ñ���������ֶ����ԣ�Ȼ��һһ��Ӧ�����Ӧ��ֵ
	CRecord* SetValue(vector<CField> vecField,...);
	//�Ƿ���������¼
	BOOL IsConditionRecord();
	//�Ƿ������ü�¼��ֻ������Ӽ�¼ʱ�Ż��õ�
	BOOL IsSetRecord();

public:
	//����ֶ�������������
	CString OutPutFieldName();
	//����¼ת��Ϊ�ַ���
	CString RecordToCString();
	//ǿתΪ���ü�¼�����ı䱾������һ���½���ǿת������
	CRecord ConditionToSet();
};