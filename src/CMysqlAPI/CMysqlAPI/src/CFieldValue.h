#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include <windows.h>
#include "CField.h"

class CField;
class __declspec(dllexport) CFieldValue{
public:
	CString strValue;
	int nValue;

	//�ֶ�ֵ���ֶ����ԵĹ�ϵ��=��>��<��>=��<=��!=
	CString CompareFlag;

	//�ֶ�ֵ������
	CField Field;
	
public:
	CFieldValue(                                                     );
	CFieldValue(CString strValue,CField     Field                    );
	CFieldValue(int       nValue,CField     Field                    );
	CFieldValue(CField     Field,CString strValue                    );
	CFieldValue(CField     Field,int       nValue                    );
	CFieldValue(CField     Field,CString CompareFlag,CString strValue);
	CFieldValue(CField     Field,CString CompareFlag,int       nValue);

public:
	//�����������ݺ�������ָ�������Բ�ƥ�䣬���������е�Ϊ׼��������0����ȫƥ�䷵��1
	BOOL SetValue(CField     Field,CString    strValue               );
	BOOL SetValue(CField     Field,int          nValue               );
	BOOL SetValue(CString strValue,CString CompareFlag,CField *pField);
	BOOL SetValue(int       nValue,CString CompareFlag,CField *pField);
};