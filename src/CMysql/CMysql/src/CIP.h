#pragma once
#include <afxwin.h>
#include "mysql.h"

class CDataBase;
class CMysqlManager;
class CIP{
	//IP���û�
	//��CIP��������ʱ�������IP��port�ͱ��뱻��ʼ�����ڲ���������Ҳ���뱻��ʼ��
public:
	//CIP�е����ݿ�������
	MYSQL *mysql;
	//ʹ��CMysql�еĹ����߽��й���
	CMysqlManager *pMysqlManager;
public:
	CString IP;
	int port;

public:
	CIP(CMysqlManager *pMysqlManager,CString IP,int port);

public:
	//ת����һ���û������ݿ�
	CDataBase* OpenUserDataBaseInterface(CString User,CString PassWord,CString dbName);
	void CloseDataBaseInterface(CDataBase* pCDataBase);
};