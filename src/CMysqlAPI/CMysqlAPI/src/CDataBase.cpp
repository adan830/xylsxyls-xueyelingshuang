#include "CDataBase.h"

CDataBase::CDataBase(CMysqlManager* pMysqlManager,CString Ip,int port,CString User,CString PassWord,CString dbName){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->vecDatabase.push_back(this);

	this->Ip = Ip;
	this->port = port;
	this->User = User;
	this->PassWord = PassWord;
	this->dbName = dbName;
	mysql = mysql_init(NULL);

	MYSQL *IsSucceed = mysql_real_connect(this->mysql,Ip,User,PassWord,dbName,port,NULL,0);
	//�������ʧ�����ͷţ����ǲ��ͷŹ����ߣ�������ֻ����CMysql���ͷ�ʱ�Ż��ͷ�
	if(IsSucceed == NULL){
		//�ͷſռ�
		mysql_close(mysql);
		mysql = 0;
		//���г�Ա������ִ��������Ϊ0
		pMysqlManager->MysqlSucceed = 0;
	}
}

CDataBase::CDataBase(CMysqlManager* pMysqlManager,CString dbName){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->vecDatabase.push_back(this);

	Ip = "";
	port = 0;
	User = "";
	PassWord = "";
	this->dbName = dbName;
	mysql = mysql_init(NULL);
}

CDataBase::~CDataBase(){
	//�ر�����������
	if(mysql != 0){
		mysql_close(mysql);
		mysql = 0;
	}
	//�ҵ����������ָ�벢ɾ��
	VecErase(&(pMysqlManager->vecDatabase),this);
}

CTable* CDataBase::CreateTable(CString TableName,BOOL ifExists){
	if(pMysqlManager->MysqlSucceed != 1) return 0;

	int nIsSucceed = -1;
	//����Ĭ����һ��test��int�ֶΣ���Ϊ���ݿ��޷������ձ�
	if(ifExists == 0) nIsSucceed = mysql_query(mysql,"create table " + TableName + "(T_e_s_t int(1))");
	if(ifExists == 1) nIsSucceed = mysql_query(mysql,"create table if not exists " + TableName + "(T_e_s_t int(1))");

	CTable* pTable = NULL;
	if(nIsSucceed == 0){
		//�¿�һ����ӿڲ�Ϊ�����ڲ�����һ��������
		pTable = new CTable(pMysqlManager,TableName,1);
		//�����ݿ�����ڲ�����������������һ���Ž�CTable��
		mysql_real_connect(pTable->mysql,Ip,User,PassWord,dbName,port,NULL,0);
	}
	else pMysqlManager->MysqlSucceed = 0;
	return pTable;
}

void CDataBase::DropTable(CString TableName,BOOL ifExists){
	if(pMysqlManager->MysqlSucceed != 1) return;

	int nIsSucceed = -1;
	//ɾ��
	if(ifExists == 0) nIsSucceed = mysql_query(mysql,"drop table " + TableName);
	if(ifExists == 1) nIsSucceed = mysql_query(mysql,"drop table if exists " + TableName);

	if(nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;
	return;
}

CTable* CDataBase::OpenTableInterface(CString TableName){
	if(pMysqlManager->MysqlSucceed != 1) return 0;

	CTable* pTable = NULL;
	//����0��ʾȷʵ�����ű�
	mysql_query(mysql,"SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='" + dbName + "' AND TABLE_NAME='" + TableName + "'");
	//������������ == 1˵��ȷʵ�����ű�
	if(mysql_store_result(mysql)->row_count == 1){
		//�¿�һ����ӿڲ�Ϊ�����ڲ�����һ��������
		pTable = new CTable(pMysqlManager,TableName);
		//�����ݿ�����ڲ�����������������һ���Ž�CTable��
		mysql_real_connect(pTable->mysql,Ip,User,PassWord,dbName,port,NULL,0);
	}
	else pMysqlManager->MysqlSucceed = 0;
	return pTable;
}

void CDataBase::CloseTableInterface(CTable* pTable){
	if(pMysqlManager->MysqlSucceed != 1) return;

	delete pTable;
	pTable = 0;
}