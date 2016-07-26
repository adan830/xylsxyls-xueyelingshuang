#include <SDKDDKVer.h>
#include "CstrValue.h"

CstrValue::CstrValue(){
	type = 0;
	strValue = "";
	nValue = 0;
	dValue = 0;
}

CstrValue::CstrValue(CString strValue){
	//�ȳ�ʼ��
	CstrValue();
	//���������˵�����ַ���
	if(strValue.Find('\"') >= 0){
		int nLeft = strValue.Find('\"');
		int nRight = strValue.Find('\"',nLeft + 1);
		this->strValue = strValue.Mid(nLeft + 1,nRight - nLeft - 1);
		type = 1;
	}
	//���û�����ŵ���С����˵����С��
	else if(strValue.Find('.') >= 0){
		dValue = atof(strValue);
		this->strValue.Format("%lf",dValue);
		type = 3;
	}
	//����ֻ���������������������ʽ�����
	else{
		int i = -1;
		strValue.Replace(" " ,"");
		strValue.Replace("\n","");
		strValue.Replace("\r","");
		strValue.Replace("\t","");
		while(i++ != strValue.GetLength() - 1){
			if(strValue[i] < 48 || strValue[i] > 57) break;
		}
		//�������˵���������������ţ�����������ʽ�����ܴ���
		if(i != strValue.GetLength()){
			this->strValue = strValue;
			type = -1;
		}
		else{
			nValue = atoi(strValue);
			this->strValue.Format("%d",nValue);
			type = 2;
		}
	}
}

CstrValue::CstrValue(const CstrValue& x){
	this->dValue = x.dValue;
	this->nValue = x.nValue;
	this->strValue = x.strValue;
	this->type = x.type;
}

CstrValue CstrValue::operator = (const CstrValue& x){
	this->dValue = x.dValue;
	this->nValue = x.nValue;
	this->strValue = x.strValue;
	this->type = x.type;
	return *this;
}

CstrValue::~CstrValue(){

}