#include <SDKDDKVer.h>
#include "CMysql.h"
#include "CMysqlManager.h"
#include "CDataBase.h"
#include "CTable.h"
#include "CIP.h"
#include "CUser.h"

CMysql::CMysql(CString IP,int port,CString User,CString PassWord,CString dbName){
	//��ʼ��������
	pMysqlManager = new CMysqlManager;
	
	//�ѳ�ʼ���Ĳ����������еļ�¼������
	this->IP = IP;
	this->port = port;
	this->User = User;
	this->PassWord = PassWord;
	this->dbName = dbName;
}

CMysql::~CMysql(){
	delete pMysqlManager;
}

//ֻ�ǽ�IP��port�ļ�¼�����¿�����
CIP* CMysql::OpenIPInterface(){
	return OpenIPInterface(IP,port);
}

CIP* CMysql::OpenIPInterface(CString IP,int port){
	//�ڴ���ʱ�ڴ����г�Ա����������ʼ��
	return new CIP(pMysqlManager,IP,port);
}

CUser* CMysql::OpenUserInterface(){
	return OpenUserInterface(User,PassWord);
}

CUser* CMysql::OpenUserInterface(CString User,CString PassWord){
	//�ڴ���ʱ�ڴ����г�Ա����������ʼ��
	return new CUser(pMysqlManager,IP,port,User,PassWord);
}

CDataBase* CMysql::OpenDataBaseInterface(){
	return OpenDataBaseInterface(dbName);
}

CDataBase* CMysql::OpenDataBaseInterface(CString dbName){
	bool bSucceed = 0;
	CDataBase* pDataBase = new CDataBase(&bSucceed,pMysqlManager,IP,port,User,PassWord,dbName);
	if(bSucceed == 0) pDataBase = 0;
	return pDataBase;
}

CTable* CMysql::OpenTableInterface(CString TableName,bool AutoCommit){
	CDataBase* pDataBase = OpenDataBaseInterface(dbName);
	//�ڴ���ʱ�ڴ����г�Ա����������ʼ��
	CTable* pTable = new CTable(pMysqlManager,pDataBase,TableName);

	//���¿���CDataBase��������߽�������
	MYSQL *IsSucceed = mysql_real_connect(pTable->pDataBase->mysql,IP,User,PassWord,dbName,port,NULL,0);
	//�������ʧ�����ͷţ����ǲ��ͷŹ����ߣ�������ֻ����CMysql���ͷ�ʱ�Ż��ͷ�
	if(IsSucceed == NULL){
		delete pTable;
		pTable = 0;
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

#include "CTableField.h"
#include "CCondition.h"
#include "CUpdate.h"
#include "CSelect.h"
int main(){
	CCondition con;
	con && (CTableField()("User")["Name"] && CTableField()("Department")["strName"]);
	con || (CTableField()("User")["ID"] || CTableField()("User")["ID"]);
	!con;
	CUpdate upd;
	upd["User"] = "a";
	upd["departID"] = 3;
	CSelect sel;
	CSelect s;
	s = sel("User");sel["ID"];
	sel("Depart")["Name"];
	CMysql mysql;
	CTable* pTable = mysql.OpenTableInterface("test",1);
	pTable->UpdateRecord(&upd,&con);
	pTable->SelectRecord(&sel,&con);
	CRecord rec;
	rec["User"] = "3";
	rec["ID"] = 3;
	pTable->Add(&rec);
	pTable->Delete(&con);
	return 0;
}