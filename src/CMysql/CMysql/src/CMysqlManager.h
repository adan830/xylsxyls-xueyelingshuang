#pragma once
#include <list>
using namespace std;

class CIP;
class CUser;
class CDataBase;
class CTable;

class CMysqlManager{
	//���е�ǰCMysql�¿����ڴ�ȫ������ڹ����ߵ������У�������һ����ɾ���������ڴ��ͷ�
public:
	//������¼�ڴ濪����������п��ٵ��ڴ��ַ�����������¼
	list<CIP      *> listIP      ;
	list<CUser    *> listUser    ;
	list<CDataBase*> listDataBase;
	list<CTable   *> listTable   ;

	bool DeleteOne(CIP      * pDelete);
	bool DeleteOne(CUser    * pDelete);
	bool DeleteOne(CDataBase* pDelete);
	bool DeleteOne(CTable   * pDelete);

public:
	CMysqlManager();
	//��������߱�ɾ��������е��ڴ��ַȫ��ɾ��
	~CMysqlManager();
};