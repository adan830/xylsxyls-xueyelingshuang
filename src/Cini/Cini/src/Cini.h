#pragma once
#include "CiniMacro.h"
#include <string>
#include <vector>
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
    string ReadIni(string key, string strSection = "Section", int MaxLength = 1024);

	//·��������·����strSectionĬ��ΪSection��key�������򴴽����������޸ģ��ļ����Բ�����·���������
	void WriteIni(string key,string text,string strSection = "Section");

    //��ȡ����Section���������section����
    vector<string> GetSection(int MaxSectionNum, int MaxLength = 1024);

    //��ȡ��section�µ�һ��key��
    string GetFirstKey(string section = "Section", int MaxLength = 1024);

    //ɾ����section�µ�ָ��key
    void DeleteKey(string key, string section = "Section");

    //ɾ��ָ��section
    void DeleteSection(string section = "Section");
};