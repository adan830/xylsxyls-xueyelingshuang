#pragma once
#include <afxwin.h>
#include "CDumpMacro.h"
#pragma comment(lib,"Dbghelp.lib")

class CDumpAPI CDump{
public:
	//ִ�����֮�����֮������ٳ���ͻ��ڵ�ǰ�����²���dump�ļ������鴫����·��
	void DeclareDumpFile(CString DumpFilePath = "CrashDumpFile.dmp");
};