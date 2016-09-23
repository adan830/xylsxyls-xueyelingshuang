#pragma once
#include <afxwin.h>

class CMysqlManager;
class CIP;
class CUser;
class CDataBase;
class CTable;
class CMysql{
	//��ɾ����֮����������ת����һ�ű��ٽ��в���������ᱨ��
	//bool ifExists = 1����ʾĬ�ϱض����������٣�����ֶ���ֵ0��������Ƿ���ڵ��жϣ����������������Ӧ����ֵ
	//CIP��CUser��CDataBase�����ж������������Կ��û��������ݿ⣬����ÿ��������һ�����ӣ�����CIP��������ר�����ڿ��û�
	//int����ֵ����������ݿ���ķ���ֵ��������󷵻ش���ֵ
public:
	//����������õ���ͬһ�����������ݿ���һ����һ���ߣ�������Ҫ�ֿ�����
	//CMysql�Ĺ����ߣ������ڴ����ͺ�������
	CMysqlManager *pMysqlManager;
	//��¼�������ڵ�IP
	CString IP;
	//��¼���ڵ�port
	int port;
	//��¼���ڵ�User
	CString User;
	//��¼���ڵ�����
	CString PassWord;
	//��¼���ڵ����ݿ���
	CString dbName;

public:
	CMysql(CString IP = "127.0.0.1",int port = 3306,CString User = "root",CString PassWord = "root",CString dbName = "test");
	~CMysql();

public:
	//��IP�Ľӿڣ�����ʼ��CIP�����ڹ���User
	CIP* OpenIPInterface();
	CIP* OpenIPInterface(CString IP,int port = 3306);
	//��User�Ľӿڣ����ڹ������ݿ�
	CUser* OpenUserInterface();
	CUser* OpenUserInterface(CString User,CString PassWord);
	//�����ݿ�ӿڣ����ڹ����
	CDataBase* OpenDataBaseInterface();
	CDataBase* OpenDataBaseInterface(CString dbName,bool AutoCommit = 1);
	//�򿪱�ӿڣ��򿪵�ʱ���Ѹñ��������Ϣȫ���ŵ��ڴ��У��������ȫ��ȡ��������ʹ�����ݿ�ӿ�
	CTable* OpenTableInterface(CString TableName,bool AutoCommit = 1);

public:
	//ת����һ��IP�����ݿ�
	//void SelectOtherIPDataBase(CString IP,CString User,CString PassWord,CString dbName,int port = 3306);
	
	//ѡ�����в���
	//void SelectTable(CString TableName);
};

