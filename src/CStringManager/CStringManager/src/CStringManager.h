#pragma once
#include <vector>
#include "CStringManagerMacro.h"
using namespace std;
#include <string>
#include <Windows.h>

class CStringManagerAPI CStringManager{
public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string strInside;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
	CStringManager(string str);
	CStringManager operator = (string str);

public:
	//��0��ʼ���������ݵ�ǰѡ�񷵻���һ����ŵ�λ�ã���������������಻���ڻ�ѡ���λ�ò�������֮һ�򷵻�-1
	//���������ƥ���ʱ��������࿪ʼ���ض�Ӧ���Ҳ�
	int FindOther(char cLeft,char cRight,int nSelect);
	//�ָ��ַ���
	vector<string> split(string separate_character);
	//vector<CString> vec = split("123,234,345,456,",","); //�õ�5���ַ���
	//vector<CString> vec2 = split("123,,234,,345,,456",",,"); //�õ�4���ַ���

	//����һ������ַ�������С���ȣ���󳤶ȣ��ַ����п��ܳ��ֵ��ַ������������Ϊ�κ��ַ�
	string RandomString(int nMin,int nMax,vector<char> vecCharacter = vector<char>());

	//�滻�ַ�����ѭ���滻�����ַ�������֤����в�����ԭ�����ַ���
	string ReplaceAll(const string& old_value,const string& new_value);
	//�滻�ַ����������滻�ַ���������CString�е�Replace
	string ReplaceEvery(const string& old_value,const string& new_value);

	//��ʽ���ַ���
	void Format(LPCTSTR szFormat,...);
	//ȡ��ߵ�N���ַ��γ�һ���µ��ַ���
	void Left();
};