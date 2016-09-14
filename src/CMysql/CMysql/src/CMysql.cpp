#include "CMysql.h"

CMysql::CMysql(CString IP,CString User,CString PassWord,CString dbName,int port){
	//��ʼ��������
	pMysqlManager = new CMysqlManager;

	//��ʼ�����ݿ�
	mysql = mysql_init(NULL);
	//Ĭ�����ӵ�����mysql��test���ݿ⣬����֮���Ĭ�Ͽ�ʼ��������ݿ�
	MYSQL *IsSucceed = mysql_real_connect(mysql,IP,User,PassWord,dbName,port,NULL,0);
	//�������ʧ�����ͷţ����ǲ��ͷŹ����ߣ�������ֻ����CMysql���ͷ�ʱ�Ż��ͷ�
	if(IsSucceed == NULL){
		//�ͷſռ�
		mysql_close(mysql);
		mysql = 0;
		//���г�Ա������ִ��������Ϊ0
		pMysqlManager->MysqlSucceed = 0;
	}
	
	//�ѳ�ʼ���Ĳ����������еļ�¼������
	this->Ip = IP;
	this->port = port;
	this->User = User;
	this->PassWord = PassWord;
	this->dbName = dbName;
}

CMysql::~CMysql(){
	delete pMysqlManager;
	pMysqlManager = 0;
	//�ͷſռ䣬�жϲ�����0����Ϊ�п��ܿ�ʼ��û������ֱ�ӱ���Ϊ0��
	if(mysql != 0){
		mysql_close(mysql);
		mysql = 0;
	}
}

//ֻ�ǽ�Ip��port�ļ�¼�����¿�����
CIp* CMysql::OpenIpInterface(){
	return OpenIpInterface(Ip,port);
}

CIp* CMysql::OpenIpInterface(CString Ip,int port){
	//�ڴ���ʱ�ڴ����г�Ա����������ʼ��
	return new CIp(pMysqlManager,Ip,port);
}

CUser* CMysql::OpenUserInterface(){
	return OpenUserInterface(User,PassWord);
}

CUser* CMysql::OpenUserInterface(CString User,CString PassWord){
	//�ڴ���ʱ�ڴ����г�Ա����������ʼ��
	return new CUser(pMysqlManager,Ip,port,User,PassWord);
}

CDataBase* CMysql::OpenDataBaseInterface(){
	return OpenDataBaseInterface(dbName);
}

CDataBase* CMysql::OpenDataBaseInterface(CString dbName){
	//�ڴ���ʱ�ڴ����г�Ա����������ʼ��
	CDataBase* pDataBase = new CDataBase(pMysqlManager,dbName);

	//���¿���CDataBase��������߽�������
	MYSQL *IsSucceed = mysql_real_connect(pDataBase->mysql,Ip,User,PassWord,dbName,port,NULL,0);
	//�������ʧ�����ͷţ����ǲ��ͷŹ����ߣ�������ֻ����CMysql���ͷ�ʱ�Ż��ͷ�
	if(IsSucceed == NULL){
		delete pDataBase;
		pDataBase = 0;
		//���г�Ա������ִ��������Ϊ0
		pMysqlManager->MysqlSucceed = 0;
	}
	return pDataBase;
}

CTable* CMysql::OpenTableInterface(CString TableName,BOOL AutoCommit){
	//�ڴ���ʱ�ڴ����г�Ա����������ʼ��
	CTable* pTable = new CTable(pMysqlManager,TableName);

	//���¿���CDataBase��������߽�������
	MYSQL *IsSucceed = mysql_real_connect(pTable->mysql,Ip,User,PassWord,dbName,port,NULL,0);
	//�������ʧ�����ͷţ����ǲ��ͷŹ����ߣ�������ֻ����CMysql���ͷ�ʱ�Ż��ͷ�
	if(IsSucceed == NULL){
		delete pTable;
		pTable = 0;
		//���г�Ա������ִ��������Ϊ0
		pMysqlManager->MysqlSucceed = 0;
	}
	return pTable;
}

/*
void CMysql::SelectOtherIPDataBase(CString IP,CString User,CString PassWord,CString dbName,int port){
	if(MysqlSucceed != 1) return;

	mysql_close(mysql);
	mysql = mysql_init(NULL);
	IsSucceed = mysql_real_connect(mysql,IP,User,PassWord,dbName,port,NULL,0);
	//�������ֵ��ָ�룬����Ϊ��ʱ��˵��ִ�гɹ�
	if(IsSucceed != 0){
		ConnectParameter.IP = IP;
		ConnectParameter.User = User;
		ConnectParameter.PassWord = PassWord;
		ConnectParameter.dbName = dbName;
		ConnectParameter.port = port;
	}
	else MysqlSucceed = 0;
	return;
}



void CMysql::SelectTable(CString TableName){
	if(MysqlSucceed != 1) return;

	ConnectParameter.TableName = TableName;
	return;
}*/
