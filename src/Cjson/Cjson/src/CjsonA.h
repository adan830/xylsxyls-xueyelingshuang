#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
using namespace std;
#include <afxwin.h>
#include "CjsonMacro.h"
#include "CFieldType.h"

class CstrValue;
class CszValue;
class Cjson;
class CFieldType;

class CjsonAPI CjsonA{
public:
	unordered_map<string,Cjson> mapdata;

public:
	//��new�����Ŀռ��ã�����һֱΪ��
	vector<CFieldType> vecField;
	//һ����Ҫ�����в�ȫ�����£���Ϊ������û��ı䵱ǰ�����Ե������ȫ�����²����ҵ�����ǰ����һ��
	vector<Cjson*> vecCjson;

public:
	//��һ���ǲ���ʶ����ַ������ڶ�����˵��
	map<CString,CString> mapError;

public:
	CjsonA();
	~CjsonA();

	CjsonA(const CjsonA& json);
	CjsonA operator = (const CjsonA& json);

public:
	map<CString,CString> LoadJson(CString strJson);
	vector<CString> GetField();
	int size();
	//FormatLengthָ���������\t����
	CString toCString(CString NewLineSign = "\r\n",CString FormatSign = "\t",int FormatLength = 1);
private:
	BOOL GetOneModule(CString* strJson,BOOL* flag,CString* strName,CString *strValue);
	void GetOneJson(CString *strJson,CString* strOneJson);
	void LoadOneModule(CString strName,CString strValue,BOOL flag);
	void OnlyLoadOneJson(CString strJson);
	CString AddTypeValue(CString strResult,int *nInsert,BOOL ifFirst,CString strField,Cjson TypeValue,CString NewLineSign,CString FormatSign,int FormatLength);
};