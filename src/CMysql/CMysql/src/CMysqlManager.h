#pragma once
#include <list>
using namespace std;
#include "CMysqlMacro.h"

class CHostIP;
class CUser;
class CDataBase;
class CTable;

template class CMysqlAPI std::allocator<CHostIP      *>;
template class CMysqlAPI std::allocator<CUser    *>;
template class CMysqlAPI std::allocator<CDataBase*>;
template class CMysqlAPI std::allocator<CTable   *>;
template class CMysqlAPI std::list<CHostIP      *,std::allocator<CHostIP      *>>;
template class CMysqlAPI std::list<CUser    *,std::allocator<CUser    *>>;
template class CMysqlAPI std::list<CDataBase*,std::allocator<CDataBase*>>;
template class CMysqlAPI std::list<CTable   *,std::allocator<CTable   *>>;

class CMysqlAPI CMysqlManager{
	//���е�ǰCMysql�¿����ڴ�ȫ������ڹ����ߵ������У�������һ����ɾ���������ڴ��ͷ�
public:
	
	//������¼�ڴ濪����������п��ٵ��ڴ��ַ�����������¼
	list<CHostIP      *> listIP      ;
	list<CUser    *> listUser    ;
	list<CDataBase*> listDataBase;
	list<CTable   *> listTable   ;

	bool DeleteOne(CHostIP      * pDelete);
	bool DeleteOne(CUser    * pDelete);
	bool DeleteOne(CDataBase* pDelete);
	bool DeleteOne(CTable   * pDelete);

public:
	CMysqlManager();
	//��������߱�ɾ��������е��ڴ��ַȫ��ɾ��
	~CMysqlManager();
};