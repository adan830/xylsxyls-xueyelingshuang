#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "mysql.h"
#include "CMysqlManager.h"
#include "CUser.h"
#include "CDataBase.h"
#include "vec.inl"

class CUser;
class CDataBase;
class CMysqlManager;

class __declspec(dllexport) CIp{
	//Ip���û�
	//��CIp��������ʱ�������Ip��port�ͱ��뱻��ʼ�����ڲ���������Ҳ���뱻��ʼ��
public:
	//CIp�е����ݿ�������
	MYSQL *mysql;
	//ʹ��CMysql�еĹ����߽��й���
	CMysqlManager *pMysqlManager;
public:
	CString Ip;
	int port;

public:
	CIp(CMysqlManager *pMysqlManager,CString Ip,int port);
	~CIp();

public:
	//ת����һ���û������ݿ�
	CDataBase* OpenUserDataBaseInterface(CString User,CString PassWord,CString dbName);
	void CloseDataBaseInterface(CDataBase* pCDataBase);
};