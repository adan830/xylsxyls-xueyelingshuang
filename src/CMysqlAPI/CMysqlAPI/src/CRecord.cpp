#include "CRecord.h"

CRecord::CRecord(){
	
}

CRecord::CRecord(CField x){
	*this = x;
}

CRecord::CRecord(CFieldValue x){
	*this = x;
}

CRecord CRecord::operator = (CField x){
	CRecord result;
	*this = result;
	this->vecFieldValue.push_back(CFieldValue(x,""));
	return *this;
}

CRecord CRecord::operator = (CFieldValue x){
	CRecord result;
	*this = result;
	this->vecFieldValue.push_back(x);
	return *this;
}

CRecord operator + (CRecord x,CFieldValue y){
	CRecord result = x;
	result.vecFieldValue.push_back(y);
	//ͨ�������Ϊ��������Ϊ�գ���������=�ֶ�ֵ����-1����ͨ����Ϊ��
	if(!((result.vecCondition.size() == 0) || (result.vecCondition.size() == result.vecFieldValue.size() - 1))){
		CRecord empty;
		return empty;
	}
	return result;
}

CRecord operator + (CFieldValue x,CRecord y){
	CRecord result = y;
	result.vecFieldValue.push_back(x);
	//ͨ�������Ϊ��������Ϊ0����ͨ����Ϊ��
	if(!(result.vecCondition.size() == 0)){
		CRecord empty;
		return empty;
	}
	return result;
}

CRecord operator + (CRecord x,CRecord y){
	CRecord result = x;
	int i = -1;
	while(i++ != y.vecFieldValue.size() - 1){
		result.vecFieldValue.push_back(y.vecFieldValue.at(i));
	}
	i = -1;
	while(i++ != y.vecCondition.size() - 1){
		result.vecCondition.push_back(y.vecCondition.at(i));
	}
	//ͨ�������Ϊ��������Ϊ0����ͨ����Ϊ��
	if(!(result.vecCondition.size() == 0)){
		CRecord empty;
		return empty;
	}
	return result;
}

CRecord operator + (CRecord x,CString y){
	CRecord result = x;
	if(y != ",") result.vecCondition.push_back(y);
	//ͨ�������Ϊ�ֶ�ֵ����=������������ͨ����Ϊ��
	if((!(result.vecCondition.size() == result.vecFieldValue.size())) || (y != "and" && y != "or")){
		CRecord empty;
		return empty;
	}
	return result;
}

CRecord operator + (CFieldValue x,CString y){
	CRecord result = x;
	return result + y;
}

CRecord operator + (CFieldValue x,CFieldValue y){
	CRecord result;
	result.vecFieldValue.push_back(x);
	result.vecFieldValue.push_back(y);
	return result;
}

CRecord operator + (CRecord x,CField y){
	CRecord result = x;
	result.vecFieldValue.push_back(CFieldValue(y,""));
	return result;
}

CRecord operator + (CField x,CRecord y){
	return y + x;
}

CRecord operator + (CField x,CField y){
	CRecord result;
	return result + x + y;
}

CRecord* CRecord::SetValue(vector<CField> vecField,...){
	va_list parameterlist;
	va_start(parameterlist,vecField);

	//����գ�CRecord��ֻ��һ��������Ա
	vector<CFieldValue> empty;
	vecFieldValue = empty;

	int i = -1;
	//����ɲ����е�char*�������е��ֶ�����һһ��Ӧ�����ֶ�ֵ�У��ټӵ���¼��
	while(i++ != vecField.size() - 1) *this = *this + CFieldValue(va_arg(parameterlist,char*),vecField.at(i));
	
	va_end(parameterlist);
	return this;
}

BOOL CRecord::IsConditionRecord(){
	int x = this->vecCondition.size();
	int y = this->vecFieldValue.size();
	return (this->vecFieldValue.size() >= 1) && (this->vecCondition.size() == this->vecFieldValue.size() - 1);
}

BOOL CRecord::IsSetRecord(){
	return (this->vecFieldValue.size() >= 1) && (this->vecCondition.size() == 0);
}

CString CRecord::OutPutFieldName(){
	CString SQL = "";
	int i = -1;
	while(i++ != vecFieldValue.size() - 1){
		if(i != 0) SQL = SQL + ",";
		SQL = SQL + vecFieldValue.at(i).Field.FieldName;
	}
	return SQL;
}

CString CRecord::RecordToCString(){
	CString SQL = "";
	int i = -1;
	while(i++ != vecFieldValue.size() - 1){
		if(i != 0){
			//��������ü�¼
			if(IsSetRecord() == 1) SQL = SQL + ",";
			//�����������¼
			if(IsConditionRecord() == 1) SQL = SQL + " " + vecCondition.at(i - 1) + " ";
		}
		SQL = SQL + vecFieldValue.at(i).Field.FieldName + vecFieldValue.at(i).CompareFlag + vecFieldValue.at(i).strValue;
	}
	return SQL;
}

CRecord CRecord::ConditionToSet(){
	CRecord result = *this;
	result.vecCondition.clear();
	return result;
}