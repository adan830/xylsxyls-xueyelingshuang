#pragma once
#include <stdint.h>
#include "CBigNumberMacro.h"

//�������㣬��֧�ָ��������ָ��������Ϊ0���������һ�ɷ���-1
class CBigNumber;
//�����������ڴ��������н���ʹ�����ͬ�����ʱ��Ҫ�����λ��
class CRadixTool;
#define BigNumberLength 10000

//���ϵͳ�Դ���sprintf_s�Ⱥ�����ʹ�ú��Ѷ��������Ϊ-2������ʹ���Ϊ�Զ������֣������������������С����strlen���㣬�����sizeof����Ļ����ڶ��δ��ε�ʱ��ᴫ��ָ�룬������4�������
//_strrev();����Ҫʹ�ã�sprintf_s��Ҫʹ��
void UnnecessaryToXA(char *arr, int size, int number);
#define UnnecessaryToX(ArrayName,number) UnnecessaryToXA(ArrayName,strlen(ArrayName) + 1,number)
//UnnecessaryToX(temp,0);//��д��

//brr����arr������ȫ������Ϊ0
#define strcpy_x(arr,brr,number) strcpy_s(arr,strlen(brr) + 1,brr);UnnecessaryToX(arr,number)

int Power(int BaseNumber, int power);

typedef int32_t MultiBool;

//������^���ű���������������ȼ�
//ֻ����ȷ��a��b������-1������²�������a - b == -1���ж��Ƿ�Ϊ����
//MutilBoolֵΪ1ʱ��ʾ�жϳ�����Ϊ0ʱ��ʾ�������
//����-1 == -1��ֵΪ1������Ϊ-1�������ֵΪ0������ֻҪ��-1������ж϶�Ϊ-1
//����������������£�a - b��a / 0��a % 0��õ�-1
class CBigNumberAPI CBigNumber
{
public:
	char number[BigNumberLength];

public:
	CBigNumber();
	CBigNumber(int           InitNumber);
	CBigNumber(char*      strInitNumber);

public:
	CBigNumber operator = (int           InitNumber);
	CBigNumber operator = (char*      strInitNumber);

public:
	friend CBigNumber operator + (CBigNumber x, CBigNumber y);
	friend CBigNumber operator - (CBigNumber x, CBigNumber y);
	friend CBigNumber operator * (CBigNumber x, CBigNumber y);
	friend CBigNumber operator ^ (CBigNumber x, CBigNumber y);
	friend CBigNumber operator / (CBigNumber x, CBigNumber y);
	friend CBigNumber operator % (CBigNumber x, CBigNumber y);

	//��չ
public:
	friend CBigNumber operator + (int        x, CBigNumber y);
	friend CBigNumber operator - (int        x, CBigNumber y);
	friend CBigNumber operator * (int        x, CBigNumber y);
	friend CBigNumber operator ^ (int        x, CBigNumber y);
	friend CBigNumber operator / (int        x, CBigNumber y);
	friend CBigNumber operator % (int        x, CBigNumber y);

	friend CBigNumber operator + (CBigNumber x, int        y);
	friend CBigNumber operator - (CBigNumber x, int        y);
	friend CBigNumber operator * (CBigNumber x, int        y);
	friend CBigNumber operator ^ (CBigNumber x, int        y);
	friend CBigNumber operator / (CBigNumber x, int        y);
	friend CBigNumber operator % (CBigNumber x, int        y);

	friend CBigNumber operator + (char*      x, CBigNumber y);
	friend CBigNumber operator - (char*      x, CBigNumber y);
	friend CBigNumber operator * (char*      x, CBigNumber y);
	friend CBigNumber operator ^ (char*      x, CBigNumber y);
	friend CBigNumber operator / (char*      x, CBigNumber y);
	friend CBigNumber operator % (char*      x, CBigNumber y);

	friend CBigNumber operator + (CBigNumber x, char*      y);
	friend CBigNumber operator - (CBigNumber x, char*      y);
	friend CBigNumber operator * (CBigNumber x, char*      y);
	friend CBigNumber operator ^ (CBigNumber x, char*      y);
	friend CBigNumber operator / (CBigNumber x, char*      y);
	friend CBigNumber operator % (CBigNumber x, char*      y);

public:
	friend MultiBool operator == (CBigNumber x, CBigNumber y);
	friend MultiBool operator != (CBigNumber x, CBigNumber y);
	friend MultiBool operator >  (CBigNumber x, CBigNumber y);
	friend MultiBool operator >= (CBigNumber x, CBigNumber y);
	friend MultiBool operator <  (CBigNumber x, CBigNumber y);
	friend MultiBool operator <= (CBigNumber x, CBigNumber y);

	friend MultiBool operator == (CBigNumber x, int        y);
	friend MultiBool operator != (CBigNumber x, int        y);
	friend MultiBool operator >  (CBigNumber x, int        y);
	friend MultiBool operator >= (CBigNumber x, int        y);
	friend MultiBool operator <  (CBigNumber x, int        y);
	friend MultiBool operator <= (CBigNumber x, int        y);

	friend MultiBool operator == (int        x, CBigNumber y);
	friend MultiBool operator != (int        x, CBigNumber y);
	friend MultiBool operator >  (int        x, CBigNumber y);
	friend MultiBool operator >= (int        x, CBigNumber y);
	friend MultiBool operator <  (int        x, CBigNumber y);
	friend MultiBool operator <= (int        x, CBigNumber y);

	friend MultiBool operator == (CBigNumber x, char*      y);
	friend MultiBool operator != (CBigNumber x, char*      y);
	friend MultiBool operator >  (CBigNumber x, char*      y);
	friend MultiBool operator >= (CBigNumber x, char*      y);
	friend MultiBool operator <  (CBigNumber x, char*      y);
	friend MultiBool operator <= (CBigNumber x, char*      y);

	friend MultiBool operator == (char*      x, CBigNumber y);
	friend MultiBool operator != (char*      x, CBigNumber y);
	friend MultiBool operator >  (char*      x, CBigNumber y);
	friend MultiBool operator >= (char*      x, CBigNumber y);
	friend MultiBool operator <  (char*      x, CBigNumber y);
	friend MultiBool operator <= (char*      x, CBigNumber y);

public:
	CBigNumber operator ++ ();//ǰ++
	CBigNumber operator -- ();//ǰ--
	CBigNumber operator ++ (int);//��++
	CBigNumber operator -- (int);//��--

private:
	//��x�ڵ����λȡ��ѹ��y.number[0]�ڣ���ɾ��x�����λ��y.number��ԭ�����������
	void HighNumberInto(CBigNumber* x, CBigNumber* y);
public:
	int InvertOut(char* OutString = nullptr);
	int Sequence(char* OutString = nullptr);
};