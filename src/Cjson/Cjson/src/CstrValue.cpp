#include "CstrValue.h"
#include "CStringManager/CStringManagerAPI.h"

CstrValue::CstrValue(){
	type = 0;
	strValue = "";
	nValue = 0;
	dValue = 0;
}

CstrValue::CstrValue(BOOL type,string strValue,int nValue,double dValue){
	this->type = type;
	this->strValue = strValue;
	this->nValue = nValue;
	this->dValue = dValue;
}

CstrValue::CstrValue(string strValue){
	//��Ҫ�Ķ�����ֹ�û�����������-"123".6
	//�ȳ�ʼ��
	type = 0;
	this->strValue = "";
	nValue = 0;
	dValue = 0;

	//��ȥ���������ߵ���Ч�ַ���Ϊ�˷�ֹ�ǲ���ʶ���ַ����ȱ���
	string strValueTemp = strValue;
	int i = -1;
	while(i++ != CStringManager::GetLength(strValueTemp) - 1){
		//������Ч�ַ�������
		if(strValueTemp[i] == ' ' || (strValueTemp[i] == '\r' && strValueTemp[i + 1] == '\n') || strValueTemp[i] == '\n' || strValueTemp[i] == '\t') continue;
		else break;
	}
	//����Ч�ַ���ʼȡ��ĩβ
	strValueTemp = CStringManager::Mid(strValueTemp, i, CStringManager::GetLength(strValueTemp) - i);
	//���ȡ�����ǿ��ַ���˵������������Ч�ַ���˵�����ǲ���ʶ���ַ���
	if(strValueTemp == ""){
		goto rem;
	}
	//ˮƽ��ת
	CStringManager::MakeReverse(strValueTemp);
	i = -1;
	while (i++ != CStringManager::GetLength(strValueTemp) - 1){
		//������Ч�ַ�������
		if(strValueTemp[i] == ' ' || strValueTemp[i] == '\r' || strValueTemp[i] == '\n' || strValueTemp[i] == '\t') continue;
		else break;
	}
	//����Ч�ַ���ʼȡ��ĩβ
	strValueTemp = CStringManager::Mid(strValueTemp, i, CStringManager::GetLength(strValueTemp) - i);
	//ˮƽ��ת
	CStringManager::MakeReverse(strValueTemp);

	//���ȥ��ͷβ����Ч�ַ�֮���һ�������һ����������˵�����ַ���
	if (strValueTemp[0] == '\"' && strValueTemp[CStringManager::GetLength(strValueTemp) - 1] == '\"'){
		type = 1;
		this->strValue = CStringManager::Mid(strValueTemp, 1, CStringManager::GetLength(strValueTemp) - 2);
	}
	//˵��������һ�����ֶ�ֵ��Ĭ��ת������0
	else if(strValueTemp == "null"){
		type = 2;
		this->strValue = strValueTemp;
		this->nValue = 0;
	}
	//����Ǹ�С������������λ����ֻ��һ��С����
	else if ((CStringManager::Replace(strValueTemp, "-", "-") == 1 && CStringManager::Find(strValueTemp, '-') == 0) && CStringManager::Replace(strValueTemp,".", ".") == 1){
		//�������ȫ����������˵������С��
		i = -1;
		while (i++ != CStringManager::GetLength(strValueTemp) - 1){
			if((strValueTemp[i] >= '0' && strValueTemp[i] <= '9') || strValueTemp[i] == '-' || strValueTemp[i] == '.') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ����С������
		type = 3;
		this->strValue = strValueTemp;
		dValue = atof(this->strValue.c_str());
	}
	//����Ǹ�����
	else if ((CStringManager::Replace(strValueTemp, "-", "-") == 1 && CStringManager::Find(strValueTemp, '-') == 0) && CStringManager::Replace(strValueTemp,".", ".") == 0){
		//�������ȫ����������˵����������
		i = -1;
		while (i++ != CStringManager::GetLength(strValueTemp) - 1){
			if((strValueTemp[i] >= '0' && strValueTemp[i] <= '9') || strValueTemp[i] == '-') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ������������
		type = 2;
		this->strValue = strValueTemp;
		nValue = atoi(this->strValue.c_str());
	}
	else if (CStringManager::Replace(strValueTemp, "-", "-") == 0 && CStringManager::Replace(strValueTemp,".", ".") == 1){
		//�������ȫ����������˵������С��
		i = -1;
		while (i++ != CStringManager::GetLength(strValueTemp) - 1){
			if((strValueTemp[i] >= '0' && strValueTemp[i] <= '9') || strValueTemp[i] == '.') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ����С������
		type = 3;
		this->strValue = strValueTemp;
		dValue = atof(this->strValue.c_str());
	}
	//�������������0
	else if (CStringManager::Replace(strValueTemp, "-", "-") == 0 && CStringManager::Replace(strValueTemp,".", ".") == 0){
		//�������ȫ����������˵����������
		i = -1;
		while (i++ != CStringManager::GetLength(strValueTemp) - 1){
			if(strValueTemp[i] >= '0' && strValueTemp[i] <= '9') continue;
			else{
				//������������ַ���˵�������ַ�������ʶ��
				goto rem;
			}
		}
		//�������Ȼ�˳�ѭ����˵������һ����С������
		type = 2;
		this->strValue = strValueTemp;
		nValue = atoi(this->strValue.c_str());
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

CstrValue::operator int(){
	return nValue;
}

CstrValue::operator string(){
	return strValue;
}

CstrValue::operator double(){
	return dValue;
}

CstrValue::~CstrValue(){

}