#pragma once
#include <afxwin.h>
#include "CtxtMacro.h"
#include <vector>
using namespace std;

class CtxtAPI Ctxt{
public:
	vector<vector<CString>> vectxt;

public:
	//txt�����Ϊ���֣���һ�֣�ÿ��ֻȡ�̶����ӵĶ�������"1-3,4-6"���ڶ��֣�ÿ����һ����־�ָ���ÿ���������󳤶�Ĭ��һ��
	void LoadTxt(CString strPath,BOOL flag,CString strSplit);
};