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
	Cini(const string& iniPath);

public:
	//ȡ������ϢĬ��1024��󳤶ȣ����key�����ڣ�Ĭ�Ϸ���"-1"��·��������·����strSectionĬ��ΪSection
	string ReadIni(const string& key, const string& strSection = "Section", int MaxLength = 1024)const;

	//·��������·����strSectionĬ��ΪSection��key�������򴴽����������޸ģ��ļ����Բ�����·���������
	void WriteIni(const string& key, const string& text, const string& strSection = "Section")const;

    //��ȡ����Section���������section����
	vector<string> GetSection(int MaxSectionNum, int MaxLength = 1024)const;

    //��ȡ��section�µ�һ��key��
	string GetFirstKey(const string& section = "Section", int MaxLength = 1024)const;

    //ɾ����section�µ�ָ��key
	void DeleteKey(const string& key, const string& section = "Section")const;

    //ɾ��ָ��section
	void DeleteSection(const string& section = "Section")const;
};