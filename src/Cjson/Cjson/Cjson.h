#pragma once
#include <vector>
using namespace std;
#include <afxwin.h>
#include <map>
#include "CstrValue.h"
#include "CszValue.h"
#include "CTypeValue.h"

class CszValue;
class CTypeValue;
class Cjson{
public:
	//json����3����ʽ���ֶν��ֶ�ֵ���ֶν�����ֵ���ֶν�json
	vector<CString> vecstr ;
	vector<CString> vecsz  ;
	vector<CString> vecjson;
	//ͨ��map�洢ʵ�ʵ�ֵ
	map<CString,CstrValue> mapstr ; //�洢�ֶν��ֶ�ֵ
	map<CString,CszValue > mapsz  ; //�洢�ֶν�����ֵ
	map<CString,Cjson    > mapjson; //�洢�ֶν�json

	map<CString,CTypeValue> mapdata;

public:
	Cjson();
	~Cjson();

public:
	void LoadJson(CString strJson);
	vector<CString> GetField();
	int size();
	//FormatLengthָ���������\t����
	CString toCString(CString NewLineSign = "\r\n",CString FormatSign = "\t",int FormatLength = 1);
private:
	void LoadOneModule(CString strName,CString strValue,BOOL flag);
	void OnlyLoadOneJson(CString strJson);
	CString AddTypeValue(CString strResult,int *nInsert,BOOL ifFirst,CString strField,CTypeValue TypeValue,CString NewLineSign,CString FormatSign,int FormatLength);
};