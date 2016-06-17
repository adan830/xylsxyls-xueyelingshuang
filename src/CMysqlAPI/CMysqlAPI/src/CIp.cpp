#include "CIp.h"

CIp::CIp(CMysqlManager *pMysqlManager,CString Ip,int port){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->vecIp.push_back(this);

	this->Ip = Ip;
	this->port = port;
	mysql = mysql_init(NULL);
}

CIp::~CIp(){
	//�ر�����������
	if(mysql != 0){
		mysql_close(mysql);
		mysql = 0;
	}
	//�ҵ����������ָ�벢ɾ��
	VecErase(&(pMysqlManager->vecIp),this);
}

CDataBase* CIp::OpenUserDataBaseInterface(CString User,CString PassWord,CString dbName){
	if(pMysqlManager->MysqlSucceed != 1) return 0;

	CDataBase* pDataBase = new CDataBase(pMysqlManager,Ip,port,User,PassWord,dbName);

	if(pMysqlManager->MysqlSucceed == 0){
		delete pDataBase;
		pDataBase = 0;
	}
	return pDataBase;
}

void CIp::CloseDataBaseInterface(CDataBase* pDataBase){
	if(pMysqlManager->MysqlSucceed != 1) return;

	delete pDataBase;
	pDataBase = 0;
}