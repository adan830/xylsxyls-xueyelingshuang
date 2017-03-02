#pragma once
#include <vector>
#include "CRandomMacro.h"
using namespace std;

class CRandomAPI CRandom{
public:
	enum{
		smallLetter = 0x00000001,
		bigLetter = 0x00000010,
		numberNoZero = 0x00000100,
		zero = 0x00001000,
		firstNoZero = 0x00010000
	};
public:
	CRandom();
	//?�����������������һ����
	int RandomInt(const vector<int>& vecInt);
	//?�����·�Χ�в���һ�������������ͷβ��������������-1����Χ����21��
	int RandomInt(int min, int max);
	//?���������в���һ�����С��
	double RandomDouble(const vector<double>& vecDouble);
	//?����һ���������������С�������λ�����һ����С��λ������ͷβ�����������򷵻�-1
	double RandomDouble(double min, double max, int decimal);
	//?���ѡ��һ���ַ���
	string RandomString(const vector<string>& vecString);
	//?�������ַ��������һ����Ĭ�������ַ����к�0
	string RandomString(int nMin, int nMax, bool ifHasZero = true);
	//?����һ������ַ�������С���ȣ���󳤶ȣ��ַ����п��ܳ��ֵ��ַ������������Ϊ�κ��ַ�
	string RandomString(int nMin, int nMax, const vector<char>& vecCharacter);
	//?����һ���ַ�������|�������ϲ����ܳ��ֵ��ַ�����enum
	string RandomString(int nMin, int nMax, int enumFlag);

private:
	string toBit(unsigned int number);
	unsigned int toUnsignedInt(const string& bit);
	int GetBigBit(const string& bit1, const string& bit2);
	int GetSmallBit(const string& bit1, const string& bit2);
	string RandomBitString(int nBit);
	unsigned int Rand();
};