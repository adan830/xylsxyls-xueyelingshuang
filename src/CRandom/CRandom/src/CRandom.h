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
	static int Int(const vector<int>& vecInt);
	//?�����·�Χ�в���һ�������������ͷβ��������������-1����Χ����21��
	static int Int(int min, int max);
	//?���������в���һ�����С��
	static double Double(const vector<double>& vecDouble);
	//?����һ���������������С�������λ�����һ����С��λ������ͷβ�����������򷵻�-1
	static double Double(double min, double max, int decimal);
	//?���ѡ��һ���ַ���
	static string String(const vector<string>& vecString);
	//?�������ַ��������һ����Ĭ�������ַ����к�0
	static string String(int nMin, int nMax, bool ifHasZero = true);
	//?����һ������ַ�������С���ȣ���󳤶ȣ��ַ����п��ܳ��ֵ��ַ������������Ϊ�κ��ַ�
	static string String(int nMin, int nMax, const vector<char>& vecCharacter);
	//?����һ���ַ�������|�������ϲ����ܳ��ֵ��ַ�����enum
	static string String(int nMin, int nMax, int enumFlag);

private:
	static string toBit(unsigned int number);
	static unsigned int toUnsignedInt(const string& bit);
	static int GetBigBit(const string& bit1, const string& bit2);
	static int GetSmallBit(const string& bit1, const string& bit2);
	static string RandomBitString(int nBit);
	static unsigned int Rand();
};