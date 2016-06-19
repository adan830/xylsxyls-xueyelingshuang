#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "API.h"

class API CField{
	//�ֶιܾ�����Ϣ
public:
	CString FieldName;
	CString Type;
	int Length;
	CString strLength;
	BOOL Default;
	int nDefault;
	CString strDefault;
	BOOL ifPrimaryKey;

public:
	CField();
	//���ڲ����ֶ�����ʱֻ�������ּ���
	CField(CString FieldName);
	//int���͵Ĳ������ȣ�д�����ݿ���ĳ�������ģ�ֻ���ַ������ȣ��������Ϊ1����"1234"����ȥ����"1"
	CField(CString FieldName,CString Type,int Length = 255,BOOL ifPrimaryKey = 0);
	//�����ݿ���type�������ֱ�ʾ��
	CField(CString FieldName,int nType,int Length = 255,BOOL ifPrimaryKey = 0);

public:
	//�����ֶ����ԣ�int��type
	void SetAttributes(CString FieldName,int    nType,int Length = 255,BOOL Default = 0,CString strDefault = "",BOOL ifPrimaryKey = 0);
	//�����ֶ�����
	void SetAttributes(CString FieldName,CString Type,int Length = 255,BOOL Default = 0,CString strDefault = "",BOOL ifPrimaryKey = 0);

};

