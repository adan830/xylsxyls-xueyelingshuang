#include <SDKDDKVer.h>
#include "CDataBase.h"

CDataBase::CDataBase(bool* bSucceed,CMysqlManager* pMysqlManager,CString IP,int port,CString User,CString PassWord,CString dbName){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->listDataBase.push_back(this);

	this->IP = IP;
	this->port = port;
	this->User = User;
	this->PassWord = PassWord;
	this->dbName = dbName;
	mysql = mysql_init(NULL);

	MYSQL *IsSucceed = mysql_real_connect(mysql,IP,User,PassWord,dbName,port,NULL,0);
	//�������ʧ�����ͷţ����ǲ��ͷŹ����ߣ�������ֻ����CMysql���ͷ�ʱ�Ż��ͷ�
	if(IsSucceed == NULL){
		this->pMysqlManager->DeleteOne(this);
		*bSucceed = 0;
	}
	*bSucceed = 1;
}

CTable* CDataBase::CreateTable(CString TableName,CString FieldName,BOOL type,int length,bool ifExists,bool AutoCommit){
	int nIsSucceed = -1;
	CString strType;
	if(type == 1) strType = "varchar";
	else if(type == 2) strType = "int";
	else if(type == 3) strType = "double";
	CString strLength;
	strLength.Format("%d",length);
	//����Ĭ����һ��test��int�ֶΣ���Ϊ���ݿ��޷������ձ�
	if(ifExists == 0) nIsSucceed = mysql_query(mysql,"create table " + TableName + "(" + FieldName + " " + strType + "(" + strLength + "))");
	if(ifExists == 1) nIsSucceed = mysql_query(mysql,"create table if not exists " + TableName + "(" + FieldName + " " + strType + "(" + strLength + "))");

	CTable* pTable = NULL;
	if(nIsSucceed == 0){
		//�¿�һ����ӿڲ�Ϊ�����ڲ�����һ��������
		pTable = new CTable(pMysqlManager,TableName,1);
		//�����ݿ�����ڲ�����������������һ���Ž�CTable��
		mysql_real_connect(pTable->mysql,IP,User,PassWord,dbName,port,NULL,0);
	}
	return pTable;
}

int CDataBase::DropTable(CString TableName,bool ifExists){
	int nIsSucceed = -1;
	//ɾ��
	if(ifExists == 0) nIsSucceed = mysql_query(mysql,"drop table " + TableName);
	else if(ifExists == 1) nIsSucceed = mysql_query(mysql,"drop table if exists " + TableName);

	return nIsSucceed;
}

CTable* CDataBase::OpenTableInterface(CString TableName,bool AutoCommit){
	CTable* pTable = NULL;
	//����0��ʾȷʵ�����ű�
	mysql_query(mysql,"SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='" + dbName + "' AND TABLE_NAME='" + TableName + "'");
	//������������ == 1˵��ȷʵ�����ű�
	if(mysql_store_result(mysql)->row_count == 1){
		//�¿�һ����ӿڲ�Ϊ�����ڲ�����һ��������
		pTable = new CTable(pMysqlManager,TableName);
		//�����ݿ�����ڲ�����������������һ���Ž�CTable��
		mysql_real_connect(pTable->mysql,IP,User,PassWord,dbName,port,NULL,0);
	}
	return pTable;
}

void CDataBase::CloseTableInterface(CTable* pTable){
	pMysqlManager->DeleteOne(pTable);
	return;
}