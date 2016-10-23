#pragma once
#include <afxwin.h>

class CCondition{
public:
	CString strSQL;
	//ѡ����ʾ������0��ʼ�����м�ļ����0��1�ļ����ʾ��һ�У�ѡ��ǰ4��Ӧ����0��4
	int nLineBegin;
	int nLineEnd;
	CString strOrderField;
	CString strAscDesc;

	CCondition();
	CCondition& operator&&(CCondition con);
	CCondition& operator||(CCondition con);
	CCondition& operator!();
	CCondition& operator()(int nLineBegin,int nLineEnd);
	CCondition& operator[](CString strOrderField);
	const CCondition& operator++(int);
	const CCondition& operator--(int);

	CString toCString();
	void Clear();
};