#include <SDKDDKVer.h>
#include "CMysqlManager.h"
#include "CIP.h"
#include "CUser.h"
#include "CDataBase.h"
#include "CTable.h"

CMysqlManager::CMysqlManager(){

}

CMysqlManager::~CMysqlManager(){
	//�ͷ�listIP
	for(auto itIP = listIP.begin();itIP != listIP.end();itIP++){
		delete *itIP;
	}
	listIP.clear();

	//�ͷ�listUser
	for(auto itUser = listUser.begin();itUser != listUser.end();itUser++){
		delete *itUser;
	}
	listUser.clear();

	//�ͷ�listDataBase
	for(auto itDataBase = listDataBase.begin();itDataBase != listDataBase.end();itDataBase++){
		delete *itDataBase;
	}
	listDataBase.clear();

	//�ͷ�listTable
	for(auto itTable = listTable.begin();itTable != listTable.end();itTable++){
		delete *itTable;
	}
	listTable.clear();
}

bool CMysqlManager::DeleteOne(CIP* pDelete){
	//�ر�����������
	if(pDelete->mysql != 0){
		mysql_close(pDelete->mysql);
	}
	for(auto itIP = listIP.begin();itIP != listIP.end();itIP++){
		if(*itIP == pDelete){
			//�ͷ�ָ��
			delete pDelete;
			//�ͷ�list���ָ��
			listIP.erase(itIP);
			return 1;
		}
	}
	AfxMessageBox("��ָ��ָ�룬CIP*");
	return 0;
}

bool CMysqlManager::DeleteOne(CUser* pDelete){
	//�ر�����������
	if(pDelete->mysql != 0){
		mysql_close(pDelete->mysql);
	}
	for(auto itUser = listUser.begin();itUser != listUser.end();itUser++){
		if(*itUser == pDelete){
			//�ͷ�ָ��
			delete pDelete;
			//�ͷ�list���ָ��
			listUser.erase(itUser);
			return 1;
		}
	}
	AfxMessageBox("��ָ��ָ�룬CUser*");
	return 0;
}

bool CMysqlManager::DeleteOne(CDataBase* pDelete){
	//�ر�����������
	if(pDelete->mysql != 0){
		mysql_close(pDelete->mysql);
	}
	for(auto itDataBase = listDataBase.begin();itDataBase != listDataBase.end();itDataBase++){
		if(*itDataBase == pDelete){
			//�ͷ�ָ��
			delete pDelete;
			//�ͷ�list���ָ��
			listDataBase.erase(itDataBase);
			return 1;
		}
	}
	AfxMessageBox("��ָ��ָ�룬CDataBase*");
	return 0;
}

bool CMysqlManager::DeleteOne(CTable* pDelete){
	//�ر�����������
	if(pDelete->pDataBase->mysql != 0){
		mysql_close(pDelete->pDataBase->mysql);
	}
	for(auto itTable = listTable.begin();itTable != listTable.end();itTable++){
		if(*itTable == pDelete){
			//�ͷ�ָ��
			delete pDelete;
			//�ͷ�list���ָ��
			listTable.erase(itTable);
			return 1;
		}
	}
	AfxMessageBox("��ָ��ָ�룬CTable*");
	return 0;
}