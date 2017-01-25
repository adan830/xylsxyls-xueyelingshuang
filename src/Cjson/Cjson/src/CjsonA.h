#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
using namespace std;

#include "CjsonMacro.h"
#include "CFieldType.h"

class CstrValue;
class CszValue;
class Cjson;
class CFieldType;

typedef int BOOL;

class CjsonAPI CjsonA{
public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	unordered_map<string, Cjson> mapdata;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	

public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	//��new�����Ŀռ��ã�����һֱΪ��
	vector<CFieldType> vecField;
	//һ����Ҫ�����в�ȫ�����£���Ϊ������û��ı䵱ǰ�����Ե������ȫ�����²����ҵ�����ǰ����һ��
	vector<Cjson*> vecCjson;

public:
	//��һ���ǲ���ʶ����ַ������ڶ�����˵��
	map<string, string> mapError;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	

public:
	CjsonA();
	~CjsonA();

	CjsonA(const CjsonA& json);
	CjsonA operator = (const CjsonA& json);

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
private:
	BOOL GetOneModule(string* strJson, BOOL* flag, string* strName, string *strValue);
	void GetOneJson(string *strJson, string* strOneJson);
	void LoadOneModule(string strName, string strValue, BOOL flag);
	void OnlyLoadOneJson(string strJson);
	string AddTypeValue(string strResult, int *nInsert, BOOL ifFirst, string strField, Cjson TypeValue, string NewLineSign, string FormatSign, int FormatLength);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
};