#include <SDKDDKVer.h>
#include "CstrValue.h"

CstrValue::CstrValue(){

}

CstrValue::CstrValue(CString strValue){
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
	//����ֻ�������������
	else{
		nValue = atoi(strValue);
		this->strValue.Format("%d",nValue);
		type = 2;
	}
}

CstrValue::~CstrValue(){

}