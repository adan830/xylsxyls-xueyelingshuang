#include "CRecord.h"

CRecord::CRecord(){
	
}

CRecord::CRecord(const CRecord& record){
	this->mapAttri = record.mapAttri;
	this->mapValue = record.mapValue;
}

CRecord CRecord::operator=(const CRecord& record){
	this->mapAttri = record.mapAttri;
	this->mapValue = record.mapValue;
	return *this;
}

CAttri& CRecord::operator[](CString Field){
	this->strCurrentField = Field;
	//��thisָ�����ȥ
	mapAttri[Field].pRecord = this;
	return mapAttri[Field];
}

CAttri CRecord::operator=(const CAttri& attri){
	return mapAttri[strCurrentField];
}