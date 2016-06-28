#pragma once
#include <vector>
using namespace std;
#include "CIp.h"
#include "CUser.h"
#include "CDataBase.h"
#include "CTable.h"
#include "API.h"
#include "vec.inl"

class CIp;
class CUser;
class CDataBase;
class CTable;

//class __declspec( dllexport ) CString;
//template  class __declspec( dllexport ) std::allocator<int>;
//template  class __declspec( dllexport ) std::vector<int,std::allocator<int>>;

class CMysqlAPI CMysqlManager{
	//���е�ǰCMysql�¿����ڴ�ȫ������ڹ����ߵ������У�������һ����ɾ���������ڴ��ͷ�
public:
	//���ֵ������⴫�Σ������Ƿ���ִ���ֻ�е����ֵΪ1��ʱ��Ż�ִ�г�Ա������һ�����ִ������ֵ��Ϊ0
	BOOL MysqlSucceed;

	//������¼�ڴ濪����������п��ٵ��ڴ��ַ�����������¼
	vector<CIp      *> vecIp      ;
	vector<CUser    *> vecUser    ;
	vector<CDataBase*> vecDatabase;
	vector<CTable   *> vecTable   ;
	
public:
	CMysqlManager();
	//��������߱�ɾ��������е��ڴ��ַȫ��ɾ��
	~CMysqlManager();
};