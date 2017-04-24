#pragma once
#include "CtxtMacro.h"
#include <vector>
using namespace std;

class CtxtAPI Ctxt{
public:

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	vector<vector<string>> vectxt;
	FILE *pFile;
	string strPath;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
	Ctxt(string strPath);
	~Ctxt();

public:
	//?�ڲ�ʹ��ifstream��getline���ļ�ĩβ�Ķ�����в��ᱻ���أ�txt�����Ϊ���֣���һ�֣�ÿ��ֻȡ�̶����ӵĶ�������"1-3,4-6"���������1��1-3����ȡ123�񣬵ڶ��֣�ÿ����һ����־�ָ���ÿ���������󳤶�Ĭ��һ��
	void LoadTxt(int flag,string strSplit);
	//?���ڴ��еı��浽�ļ���
	void Save();
	//?����д��ʽ��һ���ļ�
	bool OpenFile_w();
	//?��׷�ӷ�ʽ��һ���ļ�
	bool OpenFile_a();
	//?׷��д��һ��
	void AddWriteLine(string format,...);
	//?�ر��ļ�
	void CloseFile();
	//?׷��д��һ�в����ļ�
	void AddLine(string format,...);
};