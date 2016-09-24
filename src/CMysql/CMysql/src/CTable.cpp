#include <SDKDDKVer.h>
#include "CTable.h"
#include "CMysqlManager.h"
#include "CDataBase.h"
#include "CCondition.h"
#include "CUpdate.h"
#include "CSelect.h"


CTable::CTable(){
	//���ⲿ���������ָ��
	this->pMysqlManager = NULL;
	this->IfHasT_e_s_t = 0;
	this->pDataBase = NULL;
}

CTable::CTable(CMysqlManager *pMysqlManager,CDataBase *pDataBase,CString TableName,bool IfHasT_e_s_t){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->listTable.push_back(this);

	this->TableName = TableName;
	this->IfHasT_e_s_t = IfHasT_e_s_t;
	this->pDataBase = pDataBase;
}

void CTable::Close(){
	//��Ϊ�����ڣ������޷�ֱ��delete this��Ҳ���޷�ͨ��������ɾ���ռ��ˣ�ֻ���ڲ��ֶ��ͷ�mysql�����ߣ�Ȼ�����ⲿ�ͷű���
	
	//�ҵ����������ָ�벢ɾ����ɾ���������б���ĵ�ַ��������ִ�����֮����ռ�Ҳ���ͷ�
	pMysqlManager->DeleteOne(this);
}

CRecord CTable::operator[](int num){
	int n = 0;
	for(auto it = listRecord.begin();it != listRecord.end();it++){
		if(n == num) return *it;
		n++;
	}
	return CRecord(NULL);
}

int CTable::Add(CRecord* pRecord){
	//��ΪAdd�������β������ݿ⣬���Բ������ⲿ��û�����ûع��������ڲ���Ҫ���ûع�
	
	//�鿴�Ƿ������ֶ���ӣ����ǲ�Ϊ���ֶ���������
	for(auto itFieldInRecord = pRecord->mapValue.begin();itFieldInRecord != pRecord->mapValue.end();itFieldInRecord++){
		for(auto itFieldInTable = mapAttri.begin();itFieldInTable != mapAttri.end();itFieldInTable++){
			//�����¼����һ���ֶκ�Table�е������˵���������ֶ�
			if(itFieldInRecord->first == itFieldInTable->first) goto Next;
		}
		//�����Ȼ�˳���˵��ȫ���������˵�����ֶ������ֶ�
		int nResult = AddNewFieldWithNoAttri(itFieldInRecord->first);
		//���������ֶ�ʧ���򷵻�
		if(nResult != 0) return nResult;
		Next:;
	}

	//����listReviseAttri�ṩ���޸����Ե��ֶ������������޸�
	if(pRecord->listReviseAttri.size() != 0){
		for(auto itRevise = pRecord->listReviseAttri.begin();itRevise != pRecord->listReviseAttri.end();itRevise++){
			int nResult = ReviseAttri(&mapAttri[*itRevise]);
			//˵���������޸Ĳ��ɹ�
			if(nResult != 0) return nResult;
		}
	}
	//�޸������
	pRecord->listReviseAttri.clear();

	//�����Ժ��ֶ����ȫ���ɹ�֮����Ӽ�¼
	CString SQL = "INSERT INTO " + TableName + " SET " + pRecord->ToCString();
	
	//���ȳ�����ӣ������ӳɹ�˵���û���Ŀ��Ϊ��Ӽ�¼
	return mysql_query(pDataBase->mysql,SQL);
}

int CTable::Delete(CCondition* pCondition){
	CString SQL = "DELETE FROM " + TableName + " WHERE " + pCondition->strSQL;

	return mysql_query(pDataBase->mysql,SQL);
}

int CTable::UpdateRecord(CUpdate* pUpdate,CCondition* pCondition){
	CString SQL = "UPDATE " + TableName + " SET " + pUpdate->ToCString() + " WHERE " + pCondition->strSQL;
	//AfxMessageBox(SQL);
	//return mysql_query(pDataBase->mysql,SQL);
	return 0;
}

CTable CTable::SelectRecord(CSelect *pSelect,CCondition* pCondition){
	//���ڴ�Ų�ѯ���ļ�¼
	
	CTable vecRecord;
	CString SQL = "SELECT " + pSelect->ToCString() + " FROM " + TableName + " WHERE " + pCondition->strSQL;
	int x = 3;
	/*
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

int CTable::ReviseAttri(CAttri* pAttri){
	return 0;
}

int CTable::AddNewFieldWithNoAttri(CString strFieldName){
	return 0;
}

void CTable::ImportTable(CString mysql_exe_path,CString sqlpath){
	CString para = "";
	CString strPasswd = pDataBase->mysql->passwd;
	//�������������û���
	para = para + " -h" + pDataBase->mysql->host + " -u" + pDataBase->mysql->user;
	//����������������
	if(strPasswd != "")  para = para + " -p" + strPasswd;
	//�������Ҫ��������ݿ���
	para = para + " " + pDataBase->mysql->db + " < " + sqlpath;

	//ִ�г���ShellExecute����
	system("\"" + mysql_exe_path + "\"" + para);
	//ShellExecute(NULL,_T("open"),_T(mysql_exe_path),para,NULL,SW_SHOWNORMAL);
	return;
}

void CTable::ExportTable(CString mysqldump_exe_path,CString sqlpath){
	CString para = "";
	CString strPasswd = pDataBase->mysql->passwd;
	//�������������û���
	para = para + " -h" + pDataBase->mysql->host + " -u" + pDataBase->mysql->user;
	//����������������
	if(strPasswd != "")  para = para + " -p" + strPasswd;
	//�������Ҫ���������ݿ�ͱ���
	para = para + " " + pDataBase->mysql->db + " " + TableName + " > " + sqlpath;
	
	//ִ�г���ShellExecute����
	system("\"" + mysqldump_exe_path + "\"" + para);
	//ShellExecute(NULL,_T("open"),_T(mysqldump_exe_path),para,NULL,SW_SHOWNORMAL);
	return;
}

void CTable::Refresh(){
	mysql_query(pDataBase->mysql,"SELECT * FROM " + TableName);

	//�洢�õ��Ľ�������������ⲽ�ſ��Բ�ѯ�ֶ�������Ϣ
	MYSQL_RES* result = mysql_store_result(pDataBase->mysql);
	//��ȡ���ֶ�������Ϣ
	MYSQL_RES* resField = mysql_list_fields(pDataBase->mysql,TableName,"%");
	
	//�ȴ��ֶ�����
	int j = -1;
	while(j++ != resField->field_count - 1){
		CString strFieldName = ((resField->fields) + j)->name;
		//�洢
		mapAttri[strFieldName].Type = ((resField->fields) + j)->type;
		mapAttri[strFieldName].nLength = ((resField->fields) + j)->length;
		mapAttri[strFieldName].strFieldName = strFieldName;
		//�õ����Լ�
		int flags = ((resField->fields) + j)->flags;
		if((flags & NOT_NULL_FLAG      ) == NOT_NULL_FLAG      ) mapAttri[strFieldName].bNotNull       = 1;
		if((flags & PRI_KEY_FLAG       ) == PRI_KEY_FLAG       ) mapAttri[strFieldName].bPrimaryKey    = 1;
		if((flags & UNIQUE_KEY_FLAG    ) == UNIQUE_KEY_FLAG    ) mapAttri[strFieldName].bUniqueKey     = 1;
		if((flags & BLOB_FLAG          ) == BLOB_FLAG          ) mapAttri[strFieldName].bBlob          = 1;
		if((flags & ZEROFILL_FLAG      ) == ZEROFILL_FLAG      ) mapAttri[strFieldName].bZeroFill      = 1;
		if((flags & AUTO_INCREMENT_FLAG) == AUTO_INCREMENT_FLAG) mapAttri[strFieldName].bAutoIncrement = 1;
		//�����Ĭ��ֵ��ȡĬ��ֵ
		if((CString)((resField->fields) + j)->def != ""){
			mapAttri[strFieldName].bHasDefault = 1;
			mapAttri[strFieldName].vDefault = (CString)((resField->fields) + j)->def;
		}
	}

	//��ʼ��ȡ�ֶ�ֵ
	int i = -1;
	//����
	while(i++ != result->row_count - 1){
		int j = -1;
		//���ҵ���һ�е�ֵ��Ȼ����ݵ�ǰ����תnext�ҵ���Ӧ����
		MYSQL_ROWS* pRow = result->data->data;
		int temp = i;
		while(temp-- != 0) pRow = pRow->next;
		//׼��һ���ռ�¼
		CRecord record(this);
		//����ѭ��������Чֵѭ���ӵ���¼��
		while(j++ != result->field_count - 1){
			//�ֱ���ÿ�е��ֶ���
			CString FieldName = ((result->fields) + j)->name;
			//�ֶ�ֵ
			CString strValue = pRow->data[j];
			//�γ�һ����¼
			record[FieldName] = strValue;
		}
		listRecord.push_back(record);
	}
	return;
}