#pragma once
#include "CstrValue.h"
#include "CszValue.h"
#include "CjsonA.h"
#include "CjsonMacro.h"

class CstrValue;
class CszValue;
class CjsonA;

class CjsonAPI Cjson{
public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string type;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
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
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	map<string, string> LoadJson(string strJson);
	vector<string> GetField();
	int size();
	//FormatLengthָ���������\t����
	string tostring(string NewLineSign = "\r\n", string FormatSign = "\t", int FormatLength = 1);
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
	Cjson();
	Cjson(const CstrValue& Class);
	Cjson(const CszValue& Class);
	Cjson(const CjsonA& Class);

	Cjson(const Cjson& x);
	Cjson operator = (const Cjson& x);
	Cjson& operator[] (string field);
	Cjson& operator[] (int num);

	//���������ָ�����ڵ��ڵĴ�ֵ
	Cjson* TypeEqual(string strTemp);

	Cjson operator = (int nNum);
	Cjson operator = (double dNum);
	Cjson operator = (string str);

public:
	CstrValue& toValue();
	CszValue& tosz();
	CjsonA& toJson();

public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	//vector<HWND> vecHwnd;
	//void ClearHwnd();
	//void SaveHwnd(HWND hwnd);
	//HWND GetHwnd(int num);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	

	void FreeCJson();
	~Cjson();
};