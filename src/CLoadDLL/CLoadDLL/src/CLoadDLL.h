#pragma once
#include "CLoadDLLMacro.h"
#include <Windows.h>
#include <string>
using namespace std;

typedef int MultiBool;
#define V(NewFunName) (void **)(&(NewFunName)) //����ʱ�õĵ����ϰ�
#define CLOAD_FunNumber 200

#define V_str(NewFunName) FunName((void **)(&NewFunName),#NewFunName) //���°�

class CLoadDLLAPI FunName{
public:
	void** TempFunAddr;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string strTempFun;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	FunName(void **TempFunAddr,const char szTempFun[]);
};

class CLoadDLLAPI CLoadDLL
{
private:
	HINSTANCE FPI_DllHinstance;
	void *FunArr[CLOAD_FunNumber];

public:
	CLoadDLL(string DllPath);
	~CLoadDLL(void);

	int ErrorFunNumber;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string ErrorFunName;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
public:
	//�ϰ棬dll�ڵ����ֺ��Զ������ֿ��Բ�ͬ�������ε������������������V����CLOAD_FunNumber���޿���
	MultiBool Check_Fun(int number,...); //����-1��ʾ����·�����󣬷���1��ʾ���к��������ڣ�����0��ʾ�к���������
	void Load_Fun(int number,...);

public:
	//���°棬dll�ڵ����ֺ��Զ������ֱ�����ͬ�������V_str�����ظ�������CLOAD_FunNumber���޿���
	MultiBool LoadFun(int number,...);
};