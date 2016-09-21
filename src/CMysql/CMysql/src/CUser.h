#pragma once
#include <afxwin.h>
#include "mysql.h"

class CMysqlManager;
class CDataBase;
class CUser{
	//�û������ݿ�
	//CUser������ʱ�����ʼ�����г�Ա����
public:
	MYSQL *mysql;
	CMysqlManager* pMysqlManager;

public:
	CString IP;
	int port;
	CString User;
	CString PassWord;

public:
	CUser(CMysqlManager *pMysqlManager,CString IP,int port,CString User,CString PassWord);
	void Close();

public:

	//�������ݿ⣬����1��ʾ�ɹ���ifExists = 1��ʾ���۴治���ڶ�������ifExists = 0��ʾ������������򴴽��������򷵻ش���
	//����֮���Զ�ת��������ݿ�
	CDataBase* CreateDataBase(CString NewdbName,bool ifExists = 1);
	//�������ݿ⣬ͬʱ�ͷ�pDataBase�ռ�
	int DropDataBase(CDataBase *pDataBase);
	//����Ҫ���������ݿ�
	CDataBase* OpenDataBaseInterface(CString dbName);
	//�ر����ݿ�
	void CloseDataBaseInterface(CDataBase *pDataBase);
};