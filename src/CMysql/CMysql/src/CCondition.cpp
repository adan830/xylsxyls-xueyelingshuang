#include <SDKDDKVer.h>
#include "CCondition.h"

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