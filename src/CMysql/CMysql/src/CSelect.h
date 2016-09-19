#pragma once
#include <afxwin.h>
#include <list>
#include "CTableField.h"
using namespace std;

class CSelect{
public:
	//�ȴ���tfȻ����list
	list<CTableField> listTf;
	CTableField tf;

public:
	//sel("User")["ID"];
	CSelect operator()(CString Table);
	CSelect operator[](CString Field);

public:
	CSelect();
	CSelect(const CSelect& sel);
	CSelect operator=(const CSelect& sel);

public:
	CString ToCString();
};