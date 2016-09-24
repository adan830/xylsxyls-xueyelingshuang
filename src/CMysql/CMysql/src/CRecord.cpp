#include <SDKDDKVer.h>
#include "CRecord.h"
#include "CTable.h"

CRecord::CRecord(CTable* pTable){
	this->pTable = pTable;
}

CRecord::CRecord(const CRecord& record){
	this->mapValue = record.mapValue;
	this->strCurrentField = record.strCurrentField;
	this->pTable = record.pTable;
	this->listReviseAttri = record.listReviseAttri;
}

CRecord CRecord::operator=(const CRecord& record){
	this->mapValue = record.mapValue;
	this->strCurrentField = record.strCurrentField;
	this->pTable = record.pTable;
	this->listReviseAttri = record.listReviseAttri;
	return *this;
}

CRecord& CRecord::operator[](CString Field){
	this->strCurrentField = Field;
	return *this;
}

CRecord CRecord::operator=(const CValue& value){
	mapValue[strCurrentField] = value;
	return *this;
}

CAttri* CRecord::operator->(){
	listReviseAttri.push_back(strCurrentField);
	return &(pTable->mapAttri[strCurrentField]);
}

CValue CRecord::toValue(){
	//����ֱ��return�������᷵��һ����CValue����Ҫ����һ������CValue�������ֱ�Ӷ���CRecord������һ�������ֶ�
	//return mapValue[strCurrentField];
	
	//����вŷ���
	auto it = mapValue.find(strCurrentField);
	if(it != mapValue.end()){
		return it->second;
	}
	else return CValue();
}

CString CRecord::ToCString(){
	CString strResult;
	for(auto it = mapValue.begin();it != mapValue.end();it++){
		strResult = strResult + it->first + "=" + it->second.strValue + ",";
	}
	strResult.Delete(strResult.GetLength() - 1,1);
	return strResult;
}