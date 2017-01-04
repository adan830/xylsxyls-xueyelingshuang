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
	//static void Format(string &str,LPCTSTR szFormat,...);
	//ȡ��ߵ�N���ַ��γ�һ���µ��ַ���
	//void Left();

	static std::string Mid(const std::string & str, size_t offset, size_t count);

	static std::string Left(const std::string & str, size_t count);

	static std::string Right(const std::string & str, size_t count);

	static size_t Find(const std::string & str, const std::string & right, size_t offset = 0);

	static size_t Find(const std::string & str, char ch, size_t offset = 0);

	static size_t ReserveFind(const std::string & str, const std::string & right, size_t offset = 0);

	static size_t ReserveFind(const std::string & str, char ch, size_t offset = 0);

	static size_t GetLength(const std::string & str);

	static size_t Delete(std::string & str, size_t offset, size_t count);

	static size_t Insert(std::string & str, size_t offset, const std::string & right);

	static size_t Insert(std::string & str, size_t offset, char ch);

	static size_t Replace(std::string & str, const std::string & oldstr, const std::string & newstr);

	static size_t Replace(std::string & str, char ch1, char ch2);

	static void Format(std::string & str, const char * fmt, ...);
};