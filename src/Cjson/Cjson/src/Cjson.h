#pragma once
#include <afxwin.h>
#include "CstrValue.h"
#include "CszValue.h"
#include "CjsonA.h"
#include "CjsonMacro.h"

class CstrValue;
class CszValue;
class CjsonA;

class CjsonAPI Cjson{
public:
	CString type;
	void *pClass;

	//�����������������CTypeValue�ǲ���ʹ������
	CjsonA *pJsonA;

public:
	//���jsonָ�룬����Ѱ��vecField��vecCjson������Ҫ��һ��͸��ֵ�������²�CTypeValue�Ƿ���Ҫ��������
	//pJsonһ·͸��������pJsonA�Ƿ���Ҫ���죬���Ƿ��������ֱ���ڽ��뺯��ʱͨ��pJson�õ������pJson������pJsonһ��������Ϊinsert��delete��ԭ���¶�ʧ
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
	Cjson operator = (const Cjson& x);
	Cjson& operator[] (CString field);
	Cjson& operator[] (int num);

	//���������ָ�����ڵ��ڵĴ�ֵ
	Cjson* TypeEqual(CString strTemp);

	Cjson operator = (int nNum);
	Cjson operator = (double dNum);
	Cjson operator = (CString str);

public:
	CstrValue& toValue();
	CszValue& tosz();
	CjsonA& toJson();

public:
	vector<HWND> vecHwnd;
	void ClearHwnd();
	void SaveHwnd(HWND hwnd);
	HWND GetHwnd(int num);

	void FreeCJson();
	~Cjson();
};