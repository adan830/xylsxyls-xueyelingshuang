#pragma once
#include <afxwin.h>
#include "CAttri.h"
#include "CRecord.h"
#include <list>
using namespace std;

class CMysqlManager;
class CField;
class CRecord;
class CDataBase;
class CCondition;
class CUpdate;
class CSelect;
class CAttri;
class CTable{
	//�����������ܣ��ֱ���ֶκͼ�¼
	//�������ֶ������ֶ����Ե�map����¼�����ֶ������ֶ�ֵ��map
public:
	//�����ݿ�ָ�뵼�����������ڲ���������
	CDataBase *pDataBase;
	CMysqlManager *pMysqlManager;

public:
	//�ڴ��еı�����
	list<CRecord> listRecord;

public:
	CString TableName;
	//��¼�Ƿ����testĬ���ֶ�
	bool IfHasT_e_s_t;

	map<CString,CAttri> mapAttri;

public:
	//���ڸ�ջ����
	CTable();
	//ֻ�ǳ�ʼ��
	CTable(CMysqlManager *pMysqlManager,CDataBase *pDataBase,CString TableName,bool IfHasT_e_s_t = 0);
	void Close();

public:
	CRecord operator[](int num);

public:
	//AddRecord��DeleteRecord�����е�CRecord���岻ͬ
	//��Ӽ�¼��CRecord�м�¼��һ���ֶ����Ժ��ֶ�ֵ����Щ�ϳ�һ����¼
	//bool�ķ���ֵԭ����������������������ܳ��ֲ岻�������
	int Add(CRecord* pRecord);
	//ɾ����¼��CRecord�м�¼��һ���ֶ����Ժ��ֶ�ֵ����Ϊ��ѯ���������ϼ�ɾ����AndOrΪ1��ʾand��Ϊ0��ʾor��Ĭ��Ϊand
	int Delete(CCondition* pCondition);
	//�޸ļ�¼
	int UpdateRecord(CUpdate* pUpdate,CCondition* pCondition);
	//��ѯ��¼
	CTable SelectRecord(CSelect *pSelect,CCondition* pCondition);

	//�޸��ֶ�����
	int ReviseAttri(CAttri* pAttri);
	//������ֶ�
	int AddNewFieldWithNoAttri(CString strFieldName);

	//�����ű��룬�����ṹ������
	void ImportTable(CString mysql_exe_path,CString sqlpath);
	//�����ű�����������ṹ������
	void ExportTable(CString mysqldump_exe_path,CString sqlpath);

	//�����ڴ�
	void Refresh();
};