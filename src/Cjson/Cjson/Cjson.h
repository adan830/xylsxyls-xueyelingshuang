#pragma once
#include <map>
#include <vector>
using namespace std;
#include <afxwin.h>

class CstrValue;
class CszValue;
class CTypeValue;
class CFieldType;
class Cjson{
public:
	map<CString,CTypeValue> mapdata;

public:
	//��new�����Ŀռ��ã�����һֱΪ��
	vector<CFieldType> vecField;
	vector<CTypeValue*> vecTypeValue;

public:
	//��һ���ǲ���ʶ����ַ������ڶ�����˵��
	map<CString,CString> mapError;

public:
	Cjson();
	~Cjson();

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
	CString AddTypeValue(CString strResult,int *nInsert,BOOL ifFirst,CString strField,CTypeValue TypeValue,CString NewLineSign,CString FormatSign,int FormatLength);
};