#pragma once
#include "CiniMacro.h"
#include <string>
using namespace std;

class CiniAPI Cini{
public:

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string iniPath;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
public:
	Cini(string iniPath);

public:
	//ȡ������ϢĬ��1024��󳤶ȣ����key�����ڣ�Ĭ�Ϸ���"-1"��·��������·����strSectionĬ��ΪSection
	string ReadIni(string key,int MaxLength = 1024,string strSection = "Section");

	//·��������·����strSectionĬ��ΪSection��key�������򴴽����������޸ģ��ļ����Բ�����·���������
	void WriteIni(string key,string text,string strSection = "Section");
};