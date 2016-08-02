#pragma once
#include <afxwin.h>
#include "CstrValue.h"
#include "CszValue.h"
#include "CjsonA.h"

class CstrValue;
class CszValue;
class CjsonA;

class Cjson{
public:
	CString type;
	void *pClass;

	CjsonA *pJsonA;

public:
	//���jsonָ�룬����Ѱ��vecField��veCjson
	CjsonA *pJson;

	//��Ŵ���ֵ
	CstrValue strValueError;
	CszValue szValueError;
	CjsonA jsonError;

public:
	map<CString,CString> LoadJson(CString strJson);
	vector<CString> GetField();
	int size();
	//FormatLengthָ���������\t����
	CString toCString(CString NewLineSign = "\r\n",CString FormatSign = "\t",int FormatLength = 1);

public:
	Cjson();
	Cjson(const CstrValue& Class);
	Cjson(const CszValue& Class);
	Cjson(const CjsonA& Class);

	Cjson(const Cjson& x);
	Cjson& operator = (const Cjson& x);
	Cjson& operator[] (CString field);
	Cjson& operator[] (int num);

	void TypeEqual(CString strTemp);

	Cjson& operator = (int nNum);
	Cjson& operator = (double dNum);
	Cjson& operator = (CString str);

public:
	CstrValue& toValue();
	CszValue& tosz();
	CjsonA& toJson();
	~Cjson();
};