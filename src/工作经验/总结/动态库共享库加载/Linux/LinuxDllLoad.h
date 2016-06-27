#pragma once
#include <dlfcn.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <functional>
#include <stdarg.h>
using namespace std;

typedef int MultiBool;
#define CLinuxDllLoad_FunNumber 100
#define CLinuxDllLoad_NameNumber 50
#define V(NewFunName) (void **)(&(NewFunName)) //����ʱ�õĵ����ϰ�
#define V_str(NewFunName) FunName((void **)(&NewFunName),#NewFunName) //���°�

class FunName{
public:
	void **TempFunAddr;
	char strTempFun[CLinuxDllLoad_NameNumber];
	FunName(void **TempFunAddr,char* strTempFun);
};

class CLinuxDllLoad{
private:
	void *handle;
	void *FunArr[CLinuxDllLoad_FunNumber];

public:
	CLinuxDllLoad(string DllPath);
	~CLinuxDllLoad(void);

	int ErrorFunNumber;
	string ErrorFunName;

public:
	//�ϰ棬dll�ڵ����ֺ��Զ������ֿ��Բ�ͬ�������ε������������������V����CLOAD_FunNumber���޿���
	MultiBool Check_Fun(int number,...);//����-1��ʾ����·�����󣬷���1��ʾ���к��������ڣ�����0��ʾ�к���������
	void Load_Fun(int number,...);

public:
	//���°棬dll�ڵ����ֺ��Զ������ֱ�����ͬ�������V_str�����ظ�������CLinuxDllLoad_FunNumber���޿���
	MultiBool LoadFun(int number,...);
	
};