#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "CValue.h"
#include "CRecord.h"

class CRecord;
class CAttri{
public:
	BOOL Type;
	CString Name;
	int nlength;
	CValue vDefault;
	bool bPrimaryKey;
	bool bNotNull;
	int nAutoIncrement;
	bool bZeroFill;
	CString strComment;
	CRecord* pRecord;
public:
	CAttri();
	CAttri(const CAttri& attri);
	CAttri operator = (const CAttri& attri);

public:
	//Ϊ��CRecord���߼�д����
	CRecord& operator=(const CValue& value);
};