#pragma once
#include <stdint.h>
#include <list>
#include <map>

class BigNum
{
public:
	BigNum();
	BigNum(int32_t num);
	BigNum(const char* num);

public:
	bool Check(const char* num);

public:
	BigNum operator = (int32_t num);
	BigNum operator = (const char* num);

public:
	friend BigNum operator + (const BigNum& x, const BigNum& y);
	friend BigNum operator - (const BigNum& x, const BigNum& y);
	friend BigNum operator * (const BigNum& x, const BigNum& y);
	friend BigNum operator / (const BigNum& x, const BigNum& y);
	friend BigNum operator % (const BigNum& x, const BigNum& y);

public:
	friend int32_t operator == (BigNum x, BigNum y);
	friend int32_t operator != (BigNum x, BigNum y);
	friend int32_t operator >  (BigNum x, BigNum y);
	friend int32_t operator >= (BigNum x, BigNum y);
	friend int32_t operator <  (BigNum x, BigNum y);
	friend int32_t operator <= (BigNum x, BigNum y);

public:
	BigNum operator ++ ();//ǰ++
	BigNum operator -- ();//ǰ--
	BigNum operator ++ (int);//��++
	BigNum operator -- (int);//��--

public:
	//��ʮ����ת��Ϊ�ַ���
	std::string toString();

	//��������ת��Ϊ�ַ���
	std::string IntegerToString();

	//С������ת��Ϊ�ַ���
	std::string DecimalsToString();

	//�Ƿ�Ϊ����
	bool IsMinus() const;

	//��������Ϊ����
	void ChangeFlag();

	//���������
	std::string toRadixString(int32_t radix, const std::map<int32_t, std::string>& radixMap);

private:
	void IntToList(int32_t num, std::list<int32_t>& listNum);

	void StringToList(const std::string& num, std::list<int32_t>& listNum, bool isInteger);

public:
	//��������
	std::list<int32_t> m_listIntegerNum;

	//С������
	std::list<int32_t> m_listDecimalsNum;

	//�Ƿ��и��ű�־
	bool m_isMinus = false;

#ifdef _DEBUG
	std::string outString;
#endif
};