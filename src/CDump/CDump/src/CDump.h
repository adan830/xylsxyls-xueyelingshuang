#pragma once
#include "CDumpMacro.h"
#pragma comment(lib,"Dbghelp.lib")
#include <string>
using namespace std;

class CDumpAPI CDump{
public:
	//ִ�����֮�����֮������ٳ���ͻ��ڵ�ǰ�����²���dump�ļ������鴫����·��
	void DeclareDumpFile(string DumpFilePath = "CrashDumpFile.dmp");
};