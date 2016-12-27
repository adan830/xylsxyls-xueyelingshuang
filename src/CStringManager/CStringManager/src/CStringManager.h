#pragma once
#include <afxwin.h>
#include <vector>
#include "CStringManagerMacro.h"
using namespace std;

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
	//�ָ��ַ���
	vector<CString> split(CString separate_character);
	//vector<CString> vec = split("123,234,345,456,",","); //�õ�5���ַ���
	//vector<CString> vec2 = split("123,,234,,345,,456",",,"); //�õ�4���ַ���

	string Randomstring(int nMin,int nMax,vector<char> vecCharacter);
};