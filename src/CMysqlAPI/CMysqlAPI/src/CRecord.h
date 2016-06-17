#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "CField.h"
#include "CFieldValue.h"
#include <vector>
using namespace std;
#include <stdarg.h>

class CField;
class CFieldValue;
//����ֶ�ֵ���һ����ÿ���ֶ�ֵ�����Լ����ֶ�����

class __declspec(dllexport) CRecord{
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

	friend CRecord operator + (CRecord     x,CFieldValue y);
	friend CRecord operator + (CFieldValue x,CRecord     y);
	friend CRecord operator + (CRecord     x,CRecord     y);
	//����û�а취��ȫ���ε������������Ҫ�����������ж�
	friend CRecord operator + (CRecord     x,CString     y);
	friend CRecord operator + (CFieldValue x,CString     y);
	friend CRecord operator + (CFieldValue x,CFieldValue y);

	friend CRecord operator + (CRecord     x,CField      y);
	friend CRecord operator + (CField      x,CRecord     y);
	friend CRecord operator + (CField      x,CField      y);

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