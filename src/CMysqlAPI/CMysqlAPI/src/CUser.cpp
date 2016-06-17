#include "CUser.h"

CUser::CUser(CMysqlManager *pMysqlManager,CString Ip,int port,CString User,CString PassWord){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->vecUser.push_back(this);

	this->Ip = Ip;
	this->port = port;
	this->User = User;
	this->PassWord = PassWord;

	mysql = mysql_init(NULL);
}

CUser::~CUser(){
	//�ر�����������
	if(mysql != 0){
		mysql_close(mysql);
		mysql = 0;
	}
	//�ҵ����������ָ�벢ɾ��
	VecErase(&(pMysqlManager->vecUser),this);
}

CDataBase* CUser::CreateDataBase(CString NewdbName,BOOL ifExists){
	if(pMysqlManager->MysqlSucceed != 1) return 0;

	int nIsSucceed = -1;
	//�ж��Ƿ񴴽��ɹ�
	if(ifExists == 0) nIsSucceed = mysql_query(mysql,"create database " + NewdbName);
	if(ifExists == 1) nIsSucceed = mysql_query(mysql,"create database if not exists " + NewdbName);

	CDataBase* pDataBase = NULL;
	//����ɹ���ת�������ݿ�
	if(nIsSucceed == 0) pDataBase = OpenDataBaseInterface(NewdbName);
	//ִ�е����˵���������ݿ�ʧ�ܣ�֮����������Ա������������
	else pMysqlManager->MysqlSucceed = 0;
	return pDataBase;
}

void CUser::DropDataBase(CDataBase *pDataBase){
	if(pMysqlManager->MysqlSucceed != 1) return;

	int nIsSucceed = mysql_query(mysql,"drop database " + pDataBase->dbName);
	if(nIsSucceed == 0) delete pDataBase;
	//���ɾ��ʧ��
	else pMysqlManager->MysqlSucceed = 0;
	return;
}

CDataBase* CUser::OpenDataBaseInterface(CString dbName){
	if(pMysqlManager->MysqlSucceed != 1) return 0;

	//����������ݿ⿴�Ƿ��������ϣ������ϱ�ʾȷʵ��������ݿ⣬���Ӳ��Ϸ��ش���
	CDataBase* pDataBase = new CDataBase(pMysqlManager,Ip,port,User,PassWord,dbName);
	//������Ӳ��ϣ���Ȼȷʵ�з���ֵ�������ڲ���Ա��������ֵ��Ϊ0
	if(pMysqlManager->MysqlSucceed == 0){
		delete pDataBase;
		pDataBase = 0;
	}
	
	return pDataBase;
}

void CUser::CloseDataBaseInterface(CDataBase *pDataBase){
	if(pMysqlManager->MysqlSucceed != 1) return;

	delete pDataBase;
	pDataBase = 0;
}