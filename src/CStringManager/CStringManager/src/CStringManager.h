#pragma once
#include <afxwin.h>
#include "CStringManagerMacro.h"

class CStringManagerAPI CStringManager{
public:
	CString str;

public:
	CStringManager(CString str);
	CStringManager operator = (CString str);

public:
	//��0��ʼ���������ݵ�ǰѡ�񷵻���һ����ŵ�λ�ã���������������಻���ڻ�ѡ���λ�ò�������֮һ�򷵻�-1
	//���������ƥ���ʱ��������࿪ʼ���ض�Ӧ���Ҳ�
	int FindOther(char cLeft,char cRight,int nSelect);
};