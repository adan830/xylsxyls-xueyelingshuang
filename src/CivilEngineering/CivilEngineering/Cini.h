#pragma once
#include <afxwin.h>
#include "CiniMacro.h"

class CiniAPI Cini{
public:
	CString iniPath;

public:
	Cini(CString iniPath);

public:
	//ȡ������ϢĬ��1024��󳤶ȣ����key�����ڣ�Ĭ�Ϸ���"-1"��·��������·����strSectionĬ��ΪSection
	CString ReadIni(CString key,int MaxLength = 1024,CString strSection = "Section");

	//·��������·����strSectionĬ��ΪSection��key�������򴴽����������޸ģ��ļ����Բ�����·���������
	void WriteIni(CString key,CString text,CString strSection = "Section");
};