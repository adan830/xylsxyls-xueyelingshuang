#pragma once
#include <vector>
using namespace std;
#include <afxwin.h>

class CTypeValue;
class CszValue{
public:
	vector<CTypeValue> vecszValue; //ֻ������֣�CstrValue��Cjson

public:
	CszValue();
	CszValue(CString strValue);
	~CszValue();

public:
	int size();
};