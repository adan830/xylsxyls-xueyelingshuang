#pragma once
#include <afxwin.h>
#include "mysql.h"
#include "CMysqlManager.h"
#include "CTable.h"

class CTable;
class CMysqlManager;


class CDataBase{
	//���ݿ�ܱ�
public:
	MYSQL* mysql;
	CMysqlManager* pMysqlManager;

public:
	CString IP;
	int port;
	CString User;
	CString PassWord;
	CString dbName;

public:
	//������ݿ�����ʧ������Զ��ͷţ��������������ָ���ͷţ���bSucceed��ʶ������new��������Ȼ��ֵ����Ҫ���ⲿ��0
	CDataBase(bool* bSucceed,CMysqlManager* pMysqlManager,CString IP,int port,CString User,CString PassWord,CString dbName);

public:
	//����
	CTable* CreateTable(CString TableName,CString FieldName,BOOL type,int length,bool ifExists = 1,bool AutoCommit = 1);
	//ɾ��
	int DropTable(CString TableName,bool ifExists = 1);
	//�򿪱�ӿ�
	CTable* OpenTableInterface(CString TableName,bool AutoCommit = 1);
	//�رձ�ӿ�
	void CloseTableInterface(CTable* pTable);
};