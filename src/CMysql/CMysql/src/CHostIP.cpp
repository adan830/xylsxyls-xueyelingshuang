#include <SDKDDKVer.h>
#include "CHostIP.h"
#include "CDataBase.h"
#include "CMysqlManager.h"

CHostIP::CHostIP(CMysqlManager *pMysqlManager,CString IP,int port){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->listIP.push_back(this);

	this->IP = IP;
	this->port = port;
	mysql = mysql_init(NULL);
}

CDataBase* CHostIP::OpenUserDataBaseInterface(CString User,CString PassWord,CString dbName){
	bool bSucceed = 0;
	CDataBase* pDataBase = new CDataBase(&bSucceed,pMysqlManager,IP,port,User,PassWord,dbName);
	if(bSucceed == 0) pDataBase = 0;
	return pDataBase;
}

void CHostIP::CloseDataBaseInterface(CDataBase* pDataBase){
	pMysqlManager->DeleteOne(pDataBase);
	return;
}