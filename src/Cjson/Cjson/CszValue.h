#pragma once
#include <vector>
#include <map>
using namespace std;
#include <afxwin.h>

class Cjson;
class CszValue{
public:
	vector<Cjson> vecszValue; //ֻ������֣�CstrValue��CjsonA

public:
	map<CString,CString> mapszError;

public:
	CszValue();
	CszValue(CString strValue);
	~CszValue();

public:
	int size();
};