#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "mysql.h"
#include "CIp.h"
#include "CUser.h"
#include "CDataBase.h"
#include "CTable.h"
#include "CMysqlManager.h"
#include "API.h"
#include <vector>
using namespace std;

typedef int MultiBool;

class CMysqlManager;
class CIp;
class CUser;
class CDataBase;
class CTable;

class API CMysql{
	//����BOOLΪ����ֵ�ĺ�����1��ʾ�ɹ���0��ʾʧ��
	//MysqlSucceedΪ�ؼ��ж�ֵ��һ�����ִ������Ϊ0��֮�����г�Ա��䲻ִ��
	//��ɾ����֮����������ת����һ�ű��ٽ��в���������ᱨ��
	//BOOL ifExists = 1����ʾĬ�ϱض����������٣�����ֶ���ֵ0��������Ƿ���ڵ��жϣ����������������Ӧ����ֵ
	//CIp��CUser��CDataBase�����ж������������Կ��û��������ݿ⣬����ÿ��������һ�����ӣ�����CIp��������ר�����ڿ��û�

public:
	//����������õ���ͬһ�����������ݿ���һ����һ���ߣ�������Ҫ�ֿ�����

	//��Ҫ�������ݿ��ָ��
	MYSQL *mysql;
	//CMysql�Ĺ����ߣ������ڴ����ͺ�������
	CMysqlManager *pMysqlManager;
	//��¼�������ڵ�Ip
	CString Ip;
	//��¼���ڵ�port
	int port;
	//��¼���ڵ�User
	CString User;
	//��¼���ڵ�����
	CString PassWord;
	//��¼���ڵ����ݿ���
	CString dbName;

public:
	CMysql(CString IP = "127.0.0.1",CString User = "root",CString PassWord = "root",CString dbName = "test",int port = 3306);
	~CMysql();

public:
	//��Ip�Ľӿڣ�����ʼ��CIp�����ڹ���User
	CIp* OpenIpInterface();
	CIp* OpenIpInterface(CString Ip,int port = 3306);
	//��User�Ľӿڣ����ڹ������ݿ�
	CUser* OpenUserInterface();
	CUser* OpenUserInterface(CString User,CString PassWord);
	//�����ݿ�ӿڣ����ڹ����
	CDataBase* OpenDataBaseInterface();
	CDataBase* OpenDataBaseInterface(CString dbName);
	//����ӿڣ����ڹ����ֶκͼ�¼
	CTable* OpenTableInterface(CString TableName);

public:
	
	
	//ת����һ��IP�����ݿ�
	//void SelectOtherIPDataBase(CString IP,CString User,CString PassWord,CString dbName,int port = 3306);
	
	//ѡ�����в���
	//void SelectTable(CString TableName);
	

};