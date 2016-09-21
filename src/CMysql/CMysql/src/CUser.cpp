#include <SDKDDKVer.h>
#include "CUser.h"
#include "CMysqlManager.h"
#include "CDataBase.h"

CUser::CUser(CMysqlManager *pMysqlManager,CString IP,int port,CString User,CString PassWord){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->listUser.push_back(this);

	this->IP = IP;
	this->port = port;
	this->User = User;
	this->PassWord = PassWord;

	mysql = mysql_init(NULL);
}

void CUser::Close(){
	//�ر�����������
	if(mysql != 0){
		mysql_close(mysql);
		mysql = 0;
	}
	//�ҵ����������ָ�벢ɾ��
	pMysqlManager->DeleteOne(this);
}

CDataBase* CUser::CreateDataBase(CString NewdbName,bool ifExists){
	int nIsSucceed = -1;
	//�ж��Ƿ񴴽��ɹ�
	if(ifExists == 0) nIsSucceed = mysql_query(mysql,"create database " + NewdbName);
	if(ifExists == 1) nIsSucceed = mysql_query(mysql,"create database if not exists " + NewdbName);

	CDataBase* pDataBase = NULL;
	//����ɹ���ת�������ݿ�
	if(nIsSucceed == 0) pDataBase = OpenDataBaseInterface(NewdbName);
	return pDataBase;
}

int CUser::DropDataBase(CDataBase *pDataBase){
	int nIsSucceed = mysql_query(mysql,"drop database " + pDataBase->dbName);
	if(nIsSucceed == 0) pMysqlManager->DeleteOne(pDataBase);
	//���ɾ��ʧ�ܣ�����ʧ��ֵ
	return nIsSucceed;
}

CDataBase* CUser::OpenDataBaseInterface(CString dbName){
	bool bSucceed = 0;
	//����������ݿ⿴�Ƿ��������ϣ������ϱ�ʾȷʵ��������ݿ⣬���Ӳ��Ϸ��ش���
	CDataBase* pDataBase = new CDataBase(&bSucceed,pMysqlManager,IP,port,User,PassWord,dbName);
	//������Ӳ��ϣ�����0
	if(bSucceed == 0){
		//������ʧ��ʱ���캯���ڲ��Ѿ���delete this�Ĳ���������ֻ��Ҫ���ó�0����
		pDataBase = 0;
	}
	return pDataBase;
}

void CUser::CloseDataBaseInterface(CDataBase *pDataBase){
	pMysqlManager->DeleteOne(pDataBase);
	return;
}