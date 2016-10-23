#include <SDKDDKVer.h>
#include "CCondition.h"

CCondition::CCondition(){
	nLineBegin = -1;
	nLineEnd = -1;
}

CCondition& CCondition::operator&&(CCondition con){
	//��һ��
	if(strSQL == ""){
		strSQL = con.strSQL;
		return *this;
	}
	strSQL = "(" + strSQL + " and " + con.strSQL + ")";
	return *this;
}

CCondition& CCondition::operator||(CCondition con){
	//��һ��
	if(strSQL == ""){
		strSQL = con.strSQL;
		return *this;
	}
	strSQL = "(" + strSQL + " or " + con.strSQL + ")";
	return *this;
}

CCondition& CCondition::operator!(){
	//��һ��
	if(strSQL == ""){
		return *this;
	}
	strSQL = "( not " + strSQL + ")";;
	return *this;
}

CCondition& CCondition::operator()(int nLineBegin,int nLineEnd){
	this->nLineBegin = nLineBegin;
	this->nLineEnd = nLineEnd;
	return *this;
}

CCondition& CCondition::operator[](CString strOrderField){
	this->strOrderField = strOrderField;
	return *this;
}

const CCondition& CCondition::operator++(int){
	strAscDesc = "asc";
	return *this;
}

const CCondition& CCondition::operator--(int){
	strAscDesc = "desc";
	return *this;
}

CString CCondition::toCString(){
	CString strResult = strSQL;
	//����
	if(strOrderField != "" && strAscDesc != ""){
		strResult = strResult + " order by " + strOrderField + " " + strAscDesc;
	}
	//����
	if(nLineBegin >= 0 && nLineEnd >= 0){
		CString strBeginEndLine;
		strBeginEndLine.Format(" limit %d,%d",nLineBegin,nLineEnd);
		strResult = strResult + strBeginEndLine;
	}
	return strResult;
}

void CCondition::Clear(){
	strSQL = "";
	return;
}