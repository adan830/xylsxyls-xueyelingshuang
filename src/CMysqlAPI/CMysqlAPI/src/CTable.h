#pragma once
#include <SDKDDKVer.h>
#include <afx.h>
#include "mysql.h"
#include "CMysqlManager.h"
#include "CField.h"
#include "CRecord.h"
#include "vec.inl"
#include "API.h"
#include <vector>
using namespace std;

class CMysqlManager;
class CField;
class CRecord;

class API CTable{
	//�����������ܣ��ֱ���ֶκͼ�¼
public:
	MYSQL *mysql;
	CMysqlManager *pMysqlManager;

public:
	CString TableName;
	//��¼�Ƿ����testĬ���ֶ�
	BOOL IfHasT_e_s_t;

public:
	CTable(CMysqlManager *pMysqlManager,CString TableName,BOOL IfHasT_e_s_t = 0);
	~CTable();

public:
	//AddRecord��DeleteRecord�����е�CRecord���岻ͬ
	//��Ӽ�¼��CRecord�м�¼��һ���ֶ����Ժ��ֶ�ֵ����Щ�ϳ�һ����¼
	//BOOL�ķ���ֵԭ����������������������ܳ��ֲ岻�������
	BOOL AddRecord(CRecord* pSetRecord);
	//ɾ����¼��CRecord�м�¼��һ���ֶ����Ժ��ֶ�ֵ����Ϊ��ѯ���������ϼ�ɾ����AndOrΪ1��ʾand��Ϊ0��ʾor��Ĭ��Ϊand
	void DeleteRecord(CRecord* pConditionRecord);
	//�޸ļ�¼
	void ReviseRecord(CRecord* pSetRecord,CRecord* pConditionRecord);
	//��ѯ��¼
	vector<CRecord> SelectRecord(CRecord* pCondition = NULL,int LineBegin = 0,int LineEnd = 0,CRecord* pSelectField = NULL,CRecord *pOrderField = NULL,int AscDesc = 1);
	//�����ؼ���
	vector<CRecord> SearchKey(CString FieldName,CString KeyName);

	//����ֶ�
	void AddField(CField *pField,BOOL ifExists = 1);
	//ɾ���ֶ�
	BOOL DropField(CField *pField,BOOL ifExists = 1);
	//��ȡ�ֶ���Ϣ������mysql�ṩ��API�ڲ����ھ�̬���������ڲ�֪����û�м��������ܻ��̲߳���ȫ
	vector<CField> GetField();
	
};