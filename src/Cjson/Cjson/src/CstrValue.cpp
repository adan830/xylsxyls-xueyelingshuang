#include <SDKDDKVer.h>
#include "CstrValue.h"
#include "CStringManager/CStringManagerAPI.h"

CstrValue::CstrValue(){
	type = 0;
	strValue = "";
	nValue = 0;
	dValue = 0;
}

CstrValue::CstrValue(BOOL type,CString strValue,int nValue,double dValue){
	this->type = type;
	this->strValue = strValue;
	this->nValue = nValue;
	this->dValue = dValue;
}

CstrValue::CstrValue(CString strValue){
	//��Ҫ�Ķ�����ֹ�û�����������-"123".6
	//�ȳ�ʼ��
	type = 0;
	this->strValue = "";
	nValue = 0;
	dValue = 0;

	//��ȥ���������ߵ���Ч�ַ���Ϊ�˷�ֹ�ǲ���ʶ���ַ����ȱ���
	CString strValueTemp = strValue;
	int i = -1;
	while(i++ != strValueTemp.GetLength() - 1){
		//������Ч�ַ�������
		if(strValueTemp[i] == ' ' || (strValueTemp[i] == '\r' && strValueTemp[i + 1] == '\n') || strValueTemp[i] == '\n' || strValueTemp[i] == '\t') continue;
		else break;
	}
	//����Ч�ַ���ʼȡ��ĩβ
	strValueTemp = strValueTemp.Mid(i,strValueTemp.GetLength() - i);
	//���ȡ�����ǿ��ַ���˵������������Ч�ַ���˵�����ǲ���ʶ���ַ���
	if(strValueTemp == ""){
		goto rem;
	}
	//ˮƽ��ת
	strValueTemp.MakeReverse();
	i = -1;
	while(i++ != strValueTemp.GetLength() - 1){
		//������Ч�ַ�������
		if(strValueTemp[i] == ' ' || (strValueTemp[i] == '\n' && strValueTemp[i + 1] == '\r') || strValueTemp[i] == '\n' || strValueTemp[i] == '\t') continue;
		else break;
	}
	//����Ч�ַ���ʼȡ��ĩβ
	strValueTemp = strValueTemp.Mid(i,strValueTemp.GetLength() - i);
	//ˮƽ��ת
	strValueTemp.MakeReverse();

	//���ȥ��ͷβ����Ч�ַ�֮���һ�������һ����������˵�����ַ���
	if(strValueTemp[0] == '\"' && strValueTemp[strValueTemp.GetLength() - 1] == '\"'){
		type = 1;
		this->strValue = strValueTemp.Mid(1,strValueTemp.GetLength() - 2);
	}
	//����Ǹ�С������������λ����ֻ��һ��С����
	else if((strValueTemp.Replace("-","-") == 1 && strValueTemp.Find('-') == 0) && strValueTemp.Replace(".",".") == 1){
		//�������ȫ����������˵������С��
		i = -1;
		while(i++ != strValueTemp.GetLength() - 1){
			if((strValueTemp[i] >= '0' && strValueTemp[i] <= '9') || strValueTemp[i] == '-' || strValueTemp[i] == '.') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ����С������
		type = 3;
		this->strValue = strValueTemp;
		dValue = atof(this->strValue);
	}
	//����Ǹ�����
	else if((strValueTemp.Replace("-","-") == 1 && strValueTemp.Find('-') == 0) && strValueTemp.Replace(".",".") == 0){
		//�������ȫ����������˵����������
		i = -1;
		while(i++ != strValueTemp.GetLength() - 1){
			if((strValueTemp[i] >= '0' && strValueTemp[i] <= '9') || strValueTemp[i] == '-') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ������������
		type = 2;
		this->strValue = strValueTemp;
		nValue = atoi(this->strValue);
	}
	else if(strValueTemp.Replace("-","-") == 0 && strValueTemp.Replace(".",".") == 1){
		//�������ȫ����������˵������С��
		i = -1;
		while(i++ != strValueTemp.GetLength() - 1){
			if((strValueTemp[i] >= '0' && strValueTemp[i] <= '9') || strValueTemp[i] == '.') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ����С������
		type = 3;
		this->strValue = strValueTemp;
		dValue = atof(this->strValue);
	}
	//�������������0
	else if(strValueTemp.Replace("-","-") == 0 && strValueTemp.Replace(".",".") == 0){
		//�������ȫ����������˵����������
		i = -1;
		while(i++ != strValueTemp.GetLength() - 1){
			if(strValueTemp[i] >= '0' && strValueTemp[i] <= '9') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ����С������
		type = 2;
		this->strValue = strValueTemp;
		nValue = atoi(this->strValue);
	}
	//����֮�ⶼ�ǲ���ʶ���ַ���
	else{
		goto rem;
	}

	return;

	rem:
	type = -1;
	this->strValue = strValue;
	return;

	/*
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
			if((strValue[i] < 48 || strValue[i] > 57) && strValue[i] != '.' && strValue[i] != '-') break;
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
	}*/
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