#pragma once
#include "stdafx.h"

typedef int MultiBool;
#define V(NewFunName) (void **)(&(NewFunName)) //����ʱ�õĵ����ϰ�
#define CLOAD_FunNumber 1000

#define V_str(NewFunName) FunName((void **)(&NewFunName),#NewFunName) //���°�

typedef struct FunName{
	void **TempFunAddr;
	CString strTempFun ;
	struct FunName(void **TempFunAddr,const char szTempFun[]);
}FunName;

class CLOAD
{
private:
	HINSTANCE FPI_DllHinstance;
	void *FunArr[CLOAD_FunNumber];

public:
	CLOAD(CString DllPath);
	~CLOAD(void);

	int ErrorFunNumber;
	CString ErrorFunName;

public:
	//�ϰ棬dll�ڵ����ֺ��Զ������ֿ��Բ�ͬ�������ε������������������V����CLOAD_FunNumber���޿���
	MultiBool Check_Fun(int number,...);//����-1��ʾ����·�����󣬷���1��ʾ���к��������ڣ�����0��ʾ�к���������
	void Load_Fun(int number,...);

public:
	//���°棬dll�ڵ����ֺ��Զ������ֱ�����ͬ�������V_str�����ظ�������CLOAD_FunNumber���޿���
	MultiBool LoadFun(int number,...);
};