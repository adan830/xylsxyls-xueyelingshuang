#pragma once
#include <afxwin.h>
#include "CCondition.h"
#include "CRecord.h"
#include "CUpdate.h"
#include "CSelect.h"
#include "mysql.h"
#include <vector>
using namespace std;

class CMysqlManager;
class CField;
class CRecord;
class CTable{
	//�����������ܣ��ֱ���ֶκͼ�¼
	//�������ֶ������ֶ����Ե�map����¼�����ֶ������ֶ�ֵ��map
public:
	MYSQL *mysql;
	CMysqlManager *pMysqlManager;

public:
	CString TableName;
	//��¼�Ƿ����testĬ���ֶ�
	bool IfHasT_e_s_t;

	map<CString,CAttri> mapAttri;

public:
	CTable(CMysqlManager *pMysqlManager,CString TableName,bool IfHasT_e_s_t = 0);
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
	vector<CRecord> SelectRecord(CSelect *pSelect,CCondition* pCondition);

	//�����ؼ���
	vector<CRecord> SearchKey(CString FieldName,CString KeyName);

	//�����ű��룬�����ṹ������
	void ImportTable(CString mysql_exe_path,CString sqlpath);
	//�����ű�����������ṹ������
	void ExportTable(CString mysqldump_exe_path,CString sqlpath);
};