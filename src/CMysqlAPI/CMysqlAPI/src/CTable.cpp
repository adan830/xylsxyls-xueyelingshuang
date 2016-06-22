#include "CTable.h"

CTable::CTable(CMysqlManager *pMysqlManager,CString TableName,BOOL IfHasT_e_s_t){
	//���ⲿ���������ָ��
	this->pMysqlManager = pMysqlManager;
	//�Ȱ��¿���ָ��ŵ�������
	this->pMysqlManager->vecTable.push_back(this);

	this->TableName = TableName;
	this->IfHasT_e_s_t = IfHasT_e_s_t;
	mysql = mysql_init(NULL);
}

CTable::~CTable(){
	//��Ϊ�����ڣ������޷�ֱ��delete this��Ҳ���޷�ͨ��������ɾ���ռ��ˣ�ֻ���ڲ��ֶ��ͷ�mysql�����ߣ�Ȼ�����ⲿ�ͷű���
	//�ر�����������
	if(mysql != 0){
		mysql_close(mysql);
		mysql = 0;
	}
	//�ҵ����������ָ�벢ɾ����ɾ���������б���ĵ�ַ��������ִ�����֮����ռ�Ҳ���ͷ�
	VecErase(&(pMysqlManager->vecTable),this);
}

BOOL CTable::AddRecord(CRecord* pSetRecord){
	if(pMysqlManager->MysqlSucceed != 1) return 0;

	//��ǿת������Ҫ�ж��Ƿ�Ϊ���ü�¼
	CString SQL = "insert into " + TableName + " set " + pSetRecord->ConditionToSet().RecordToCString();
	
	int nIsSucceed = mysql_query(mysql,SQL);
	CString error = mysql_error(mysql);
	
	if(nIsSucceed != 0){
		//���������֧˵�������������ظ��Ĵ������Ĵ��󣬶�Ӧ�÷���0
		//����Ҳ���primary˵�����������ظ��Ĵ�����Ϊ��Ĵ���
		if(error.Find("'PRIMARY'") < 0) pMysqlManager->MysqlSucceed = 0;
		return 0;
	}
	return 1;
}

void CTable::DeleteRecord(CRecord* pConditionRecord){
	if(pMysqlManager->MysqlSucceed != 1) return;

	//����Ҫ�ж��Ƿ���������¼���������������¼��ֱ�ӷ��ش���
	if(pConditionRecord->IsConditionRecord() == 0){
		pMysqlManager->MysqlSucceed = 0;
		return;
	}

	CString SQL = "delete from " + TableName + " where " + pConditionRecord->RecordToCString();

	int nIsSucceed = mysql_query(mysql,SQL);
	const char *s = mysql_error(mysql);
	if(nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;
	return;
}

void CTable::ReviseRecord(CRecord* pSetRecord,CRecord* pConditionRecord){
	if(pMysqlManager->MysqlSucceed != 1) return;

	//����Ҫ�ж��Ƿ���������¼���������������¼��ֱ�ӷ��ش���Set��ǿת������Ҫ�ж���
	if(pConditionRecord->IsConditionRecord() == 0){
		pMysqlManager->MysqlSucceed = 0;
		return;
	}

	CString SQL = "update " + TableName + " set " + pSetRecord->ConditionToSet().RecordToCString() + " where " + pConditionRecord->RecordToCString();

	int nIsSucceed = mysql_query(mysql,SQL);
	if(nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;
	return;
}

vector<CRecord> CTable::SelectRecord(CRecord* pCondition,int LineBegin,int LineEnd,CRecord* pSelectField,CRecord *pOrderField,int AscDesc){
	//���ڴ�Ų�ѯ���ļ�¼
	vector<CRecord> vecRecord;
	if(pMysqlManager->MysqlSucceed != 1) return vecRecord;
	
	if(pCondition != NULL && pCondition->IsConditionRecord() == 0){
		pMysqlManager->MysqlSucceed = 0;
		return vecRecord;
	}
	//����
	CString strBeginEndLine = "";
	if(LineEnd > LineBegin && LineBegin >= 0) strBeginEndLine.Format("%d,%d",LineBegin,LineEnd);
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

	if(nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;
	return vecRecord;
}

vector<CRecord> CTable::SearchKey(CString FieldName,CString KeyName){
	//���ڴ�Ų�ѯ���ļ�¼
	vector<CRecord> vecRecord;
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

	if(nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;
	return vecRecord;
}

void CTable::AddField(CField *pField,BOOL ifExists){
	if(pMysqlManager->MysqlSucceed != 1) return;

	CString SQL = "alter table " + TableName + " add " + pField->FieldName + " " + pField->Type + "(" + pField->strLength + ")";
	//�����Ĭ��ֵ
	if(pField->Default != 0) SQL = SQL + " not null default " + pField->strDefault;
	//���������
	if(pField->ifPrimaryKey == 1) SQL = SQL + " primary key";

	//ִ��
	int nIsSucceed = mysql_query(mysql,SQL);
	const char*s = mysql_error(mysql);

	//�������ֶγɹ��������¿��ı��һ�μ����ֶ�ʱ��Ҫɾ���ֶ�T_e_s_t
	if(nIsSucceed == 0 && IfHasT_e_s_t == 1){
		DropField(&CField("T_e_s_t"));
		IfHasT_e_s_t = 0;
	}

	//������Ǳض����룬��mysql���ش�������Ҫ��ִ��������Ϊ0
	if(ifExists == 0 && nIsSucceed != 0) pMysqlManager->MysqlSucceed = 0;
	return;
}

BOOL CTable::DropField(CField *pField,BOOL ifExists){
	if(pMysqlManager->MysqlSucceed != 1) return 0;

	vector<CField> vecField = GetField();
	BOOL ifExist = 0;
	int i = -1;
	while(i++ != vecField.size() - 1){
		ifExist = ifExist || (vecField.at(i).FieldName == pField->FieldName);
	}
	
	int nIsSucceed = -1;
	//������в����ڸ��ֶΣ��Ҳ��Ǳض�ɾ����˵������Ҫɾһ�������ڵ��ֶΣ�ֱ�ӷ��ش����0
	if(ifExist == 0 && ifExists == 0){
		pMysqlManager->MysqlSucceed = 0;
		return 0;
	}
	//������в����ڸ��ֶΣ����Ǳض�ɾ����˵���ض�Ҫɾ������ֶΣ����Բ���Ҫִ��mysql����ֱ�ӷ���1
	if(ifExist == 0 && ifExists == 1) return 1;
	//������д��ڸ��ֶΣ������ǲ��Ǳض�ɾ������Ҫִ��mysql���ж��Ƿ��Ѿ�ɾ���ɹ���ɾ���ɹ�����1��ʧ�ܷ��ش����0
	nIsSucceed = mysql_query(mysql,"alter table " + TableName + " drop column " + pField->FieldName);
	if(nIsSucceed == 0) return 1;
	else{
		pMysqlManager->MysqlSucceed = 0;
		return 0;
	}
}

vector<CField> CTable::GetField(){
	if(pMysqlManager->MysqlSucceed != 1){
		vector<CField> error;
		return error;
	}

	//���������ű�
	mysql_query(mysql,"select * from " + TableName);
	//�洢�õ��Ľ��
	MYSQL_RES* result = mysql_store_result(mysql);
	
	vector<CField> vecField;
	int i = -1;
	while(i++ != result->field_count - 1){
		CField Field(((result->fields) + i)->name,((result->fields) + i)->type,((result->fields) + i)->length);
		vecField.push_back(Field);
	}
	return vecField;
}

void CTable::ImportTable(CString mysql_exe_path,CString sqlpath){
	if(pMysqlManager->MysqlSucceed != 1) return;

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
	if(pMysqlManager->MysqlSucceed != 1) return;
	
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