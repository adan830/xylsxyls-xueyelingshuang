#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "mysql.h"
#include "CMysqlManager.h"
#include "CTable.h"
#include "vec.inl"

class CTable;
class CMysqlManager;


class __declspec(dllexport) CDataBase{
	//���ݿ�ܱ�
public:
	MYSQL* mysql;
	CMysqlManager* pMysqlManager;

public:
	
	CString Ip;
	int port;
	CString User;
	CString PassWord;
	CString dbName;

public:
	CDataBase(CMysqlManager* pMysqlManager,CString Ip,int port,CString User,CString PassWord,CString dbName);
	CDataBase(CMysqlManager* pMysqlManager,CString dbName);
	~CDataBase();

public:
	//����
	CTable* CreateTable(CString TableName,BOOL ifExists = 1);
	//ɾ��
	void DropTable(CString TableName,BOOL ifExists = 1);
	//�򿪱�ӿ�
	CTable* OpenTableInterface(CString TableName);
	//�رձ�ӿ�
	void CloseTableInterface(CTable* pTable);
};