#include <SDKDDKVer.h>
#include "CTable.h"
#include "CMysqlManager.h"

CTable::CTable(CMysqlManager *pMysqlManager,CString TableName,bool IfHasT_e_s_t){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->listTable.push_back(this);

	this->TableName = TableName;
	this->IfHasT_e_s_t = IfHasT_e_s_t;
	mysql = mysql_init(NULL);
}

void CTable::Close(){
	//��Ϊ�����ڣ������޷�ֱ��delete this��Ҳ���޷�ͨ��������ɾ���ռ��ˣ�ֻ���ڲ��ֶ��ͷ�mysql�����ߣ�Ȼ�����ⲿ�ͷű���
	
	//�ҵ����������ָ�벢ɾ����ɾ���������б���ĵ�ַ��������ִ�����֮����ռ�Ҳ���ͷ�
	pMysqlManager->DeleteOne(this);
}

int CTable::Add(CRecord* pRecord){
	//��ǿת������Ҫ�ж��Ƿ�Ϊ���ü�¼
	CString SQL = "insert into " + TableName + " set " + pRecord->ToCString();
	
	int nIsSucceed = mysql_query(mysql,SQL);
	//CString error = mysql_error(mysql);
	
	//if(nIsSucceed != 0){
		//���������֧˵�������������ظ��Ĵ������Ĵ��󣬶�Ӧ�÷���0
		//����Ҳ���primary˵�����������ظ��Ĵ�����Ϊ��Ĵ���
		//if(error.Find("'PRIMARY'") < 0) pMysqlManager->MysqlSucceed = 0;
		//return 0;
	//}
	return nIsSucceed;
}

int CTable::Delete(CCondition* pCondition){
	CString SQL = "delete from " + TableName + " where " + pCondition->strSQL;
	return mysql_query(mysql,SQL);
}

int CTable::UpdateRecord(CUpdate* pUpdate,CCondition* pCondition){
	CString SQL = "update " + TableName + " set " + pUpdate->ToCString() + " where " + pCondition->strSQL;
	return mysql_query(mysql,SQL);
}

vector<CRecord> CTable::SelectRecord(CSelect *pSelect,CCondition* pCondition){
	//���ڴ�Ų�ѯ���ļ�¼
	
	vector<CRecord> vecRecord;/*
	//����
	//CString strBeginEndLine = "";
	//if(LineEnd > LineBegin && LineBegin >= 0) strBeginEndLine.Format("%d,%d",LineBegin,LineEnd);
	//��ʾ����
	CString strSelectField = "";
	if(pSelectField == NULL) strSelectField = "*";
	else strSelectField = pSelectField->OutPutFieldName();
	//�����������ݵ���
	CString strOrderField = "";
	if(pOrderField != NULL) strOrderField = pOrderField->OutPutFieldName();
	//1��ʾ����0��ʾ����
	CString strAscDesc = "";
	if(AscDesc == 1) strAscDesc = "asc";
	if(AscDesc == 0) strAscDesc = "desc";

	//CString SQL = "SELECT abc,bcd FROM abcdefg WHERE bcd='yi' AND cde='YI' ORDER BY def AND efg LIMIT 0,1";// order by strchar limit 0,2;";

	CString SQL = "select " + strSelectField + " from " + TableName;
	if(pCondition != NULL) SQL = SQL + " where " + pCondition->RecordToCString();

	if(strOrderField != "") SQL = SQL + " order by " + strOrderField + " " + strAscDesc;

	if(strBeginEndLine != "") SQL = SQL + " limit " + strBeginEndLine;
	
	int nIsSucceed = mysql_query(mysql,SQL);

	const char *s = mysql_error(mysql);
	//�洢�õ��Ľ��
	MYSQL_RES* result = mysql_store_result(mysql);
	
	int i = -1;
	//����
	while(i++ != result->row_count - 1){
		int j = -1;
		//���ҵ���һ�е�ֵ��Ȼ����ݵ�ǰ����תnext�ҵ���Ӧ����
		MYSQL_ROWS* pRow = result->data->data;
		int temp = i;
		while(temp-- != 0) pRow = pRow->next;
		//׼��һ���ռ�¼
		CRecord record;
		//����ѭ��������Чֵѭ���ӵ���¼��
		while(j++ != result->field_count - 1){
			//�ֶκ��ֶ�ֵ�Ǹ���������ѭ���ģ�����ͬ��һ������
			CString FieldName = ((result->fields) + j)->name; //�ֱ���ÿ�е��ֶ���
			int nType = ((result->fields) + j)->type; //����
			int length = ((result->fields) + j)->length; //����
			CField field(FieldName,nType,length);
			CString strValue = pRow->data[j];
			CFieldValue FieldValue(field,strValue);
			record = record + FieldValue;
		}
		vecRecord.push_back(record);
	}

	if(nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;*/
	return vecRecord;
}

vector<CRecord> CTable::SearchKey(CString FieldName,CString KeyName){
	
	//���ڴ�Ų�ѯ���ļ�¼
	vector<CRecord> vecRecord;/*
	if(pMysqlManager->MysqlSucceed != 1) return vecRecord;

	CString SQL = "select * from " + TableName + " where " + FieldName + " like '" + KeyName + "'";

	int nIsSucceed = mysql_query(mysql,SQL);

	//�洢�õ��Ľ��
	MYSQL_RES* result = mysql_store_result(mysql);

	int i = -1;
	//����
	while(i++ != result->row_count - 1){
		int j = -1;
		//���ҵ���һ�е�ֵ��Ȼ����ݵ�ǰ����תnext�ҵ���Ӧ����
		MYSQL_ROWS* pRow = result->data->data;
		int temp = i;
		while(temp-- != 0) pRow = pRow->next;
		//׼��һ���ռ�¼
		CRecord record;
		//����ѭ��������Чֵѭ���ӵ���¼��
		while(j++ != result->field_count - 1){
			//�ֶκ��ֶ�ֵ�Ǹ���������ѭ���ģ�����ͬ��һ������
			CString FieldName = ((result->fields) + j)->name; //�ֱ���ÿ�е��ֶ���
			int nType = ((result->fields) + j)->type; //����
			int length = ((result->fields) + j)->length; //����
			CField field(FieldName,nType,length);
			CString strValue = pRow->data[j];
			CFieldValue FieldValue(field,strValue);
			record = record + FieldValue;
		}
		vecRecord.push_back(record);
	}

	if(nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;*/
	return vecRecord;
}

void CTable::ImportTable(CString mysql_exe_path,CString sqlpath){
	CString para = "";
	CString strPasswd = mysql->passwd;
	//�������������û���
	para = para + " -h" + mysql->host + " -u" + mysql->user;
	//����������������
	if(strPasswd != "")  para = para + " -p" + strPasswd;
	//�������Ҫ��������ݿ���
	para = para + " " + mysql->db + " < " + sqlpath;

	//ִ�г���ShellExecute����
	system("\"" + mysql_exe_path + "\"" + para);
	//ShellExecute(NULL,_T("open"),_T(mysql_exe_path),para,NULL,SW_SHOWNORMAL);
	return;
}

void CTable::ExportTable(CString mysqldump_exe_path,CString sqlpath){
	CString para = "";
	CString strPasswd = mysql->passwd;
	//�������������û���
	para = para + " -h" + mysql->host + " -u" + mysql->user;
	//����������������
	if(strPasswd != "")  para = para + " -p" + strPasswd;
	//�������Ҫ���������ݿ�ͱ���
	para = para + " " + mysql->db + " " + TableName + " > " + sqlpath;
	
	//ִ�г���ShellExecute����
	system("\"" + mysqldump_exe_path + "\"" + para);
	//ShellExecute(NULL,_T("open"),_T(mysqldump_exe_path),para,NULL,SW_SHOWNORMAL);
	return;
}