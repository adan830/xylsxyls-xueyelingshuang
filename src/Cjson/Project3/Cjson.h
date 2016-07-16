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
	void LoadJson(CString strJson);

private:
	void LoadOneModule(CString strName,CString strValue,BOOL flag);
	void OnlyLoadOneJson(CString strJson);
};