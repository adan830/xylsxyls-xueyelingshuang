#pragma once
#include <afxwin.h>
#include "CtxtMacro.h"
#include <vector>
using namespace std;

class CtxtAPI Ctxt{
public:
	vector<vector<CString>> vectxt;
	FILE *pFile;
	CString strPath;

public:
	Ctxt(CString strPath);

public:
	//�ڲ�ʹ��ifstreamֱ�ӵ��ü��ɣ�txt�����Ϊ���֣���һ�֣�ÿ��ֻȡ�̶����ӵĶ�������"1-3,4-6"���������1��1-3����ȡ123�񣬵ڶ��֣�ÿ����һ����־�ָ���ÿ���������󳤶�Ĭ��һ��
	void LoadTxt(BOOL flag,CString strSplit);
	//��׷�ӷ�ʽ��һ���ļ�
	bool OpenFile_a();
	//׷��д��һ��
	void AddWriteLine(int MaxLength,CString format,...);
	//�ر��ļ�
	void CloseFile();
};