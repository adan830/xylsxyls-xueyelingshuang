#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "mysql.h"
#include "CMysqlManager.h"
#include "CDataBase.h"
#include "API.h"
#include "vec.inl"

class CMysqlManager;
class CDataBase;

class CMysqlAPI CUser{
	//�û������ݿ�
	//CUser������ʱ�����ʼ�����г�Ա����
public:
	MYSQL *mysql;
	CMysqlManager* pMysqlManager;

public:
	CString Ip;
	int port;
	CString User;
	CString PassWord;

public:
	CUser(CMysqlManager *pMysqlManager,CString Ip,int port,CString User,CString PassWord);
	~CUser();

public:

	//�������ݿ⣬����1��ʾ�ɹ���ifExists = 1��ʾ���۴治���ڶ�������ifExists = 0��ʾ������������򴴽��������򷵻ش���
	//����֮���Զ�ת��������ݿ�
	CDataBase* CreateDataBase(CString NewdbName,BOOL ifExists = 1);
	//�������ݿ⣬ͬʱ�ͷ�pDataBase�ռ�
	void DropDataBase(CDataBase *pDataBase);
	//����Ҫ���������ݿ�
	CDataBase* OpenDataBaseInterface(CString dbName);
	//�ر����ݿ�
	void CloseDataBaseInterface(CDataBase *pDataBase);
};