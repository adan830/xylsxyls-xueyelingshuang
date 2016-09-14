#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "CValue.h"
#include "CCondition.h"

class CTableField{
public:
	CString Table;
	CString Field;
public:
	//tf("User")["ID"];
	CTableField operator()(CString Table);
	CTableField operator[](CString Field);
public:
	CTableField();
	CTableField(const CTableField& tf);
	CTableField operator=(const CTableField& tf);

public:
	CCondition operator==(const CValue& value);
	CCondition operator!=(const CValue& value);
	CCondition operator<(const CValue& value);
	CCondition operator>(const CValue& value);
	CCondition operator<=(const CValue& value);
	CCondition operator>=(const CValue& value);
	//����
	CCondition operator&&(const CTableField& tf);
	//�����ϣ���ߵ����������ڵ����ұߵ�������
	CCondition operator>=(const CTableField& tf);
	//�����ϣ���ߵ�������С�ڵ����ұߵ�������
	CCondition operator<=(const CTableField& tf);
	//ȫ��
	CCondition operator||(const CTableField& tf);
};