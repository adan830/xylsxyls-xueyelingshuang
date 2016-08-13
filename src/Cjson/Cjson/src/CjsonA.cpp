#include <SDKDDKVer.h>
#include "CjsonA.h"
#include "CstrValue.h"
#include "CszValue.h"
#include "Cjson.h"
#include "CFieldType.h"
#include "CStringManager/CStringManagerAPI.h"

extern vector<void *> vecp;

CjsonA::CjsonA(){
	
}

CjsonA::~CjsonA(){

}

CjsonA::CjsonA(const CjsonA& json){
	this->mapdata  = json.mapdata;
	this->vecField = json.vecField;
	this->vecCjson = json.vecCjson;
	this->mapError = json.mapError;
}

CjsonA CjsonA::operator = (const CjsonA& json){
	this->mapdata  = json.mapdata;
	this->vecField = json.vecField;
	this->vecCjson = json.vecCjson;
	this->mapError = json.mapError;
	return *this;
}

BOOL CjsonA::GetOneModule(CString* strJson,BOOL* flag,CString* strName,CString *strValue){
	int nNameLeft = strJson->Find('{');
	nNameLeft++;
	int nNameRight = nNameLeft;
	//��һ���ҵ������ֶ����������λ��
	nNameRight = strJson->Find('\"',nNameRight);
	if(nNameRight >= 0){
		name:
		//�ڶ����ҵ������Ҳ�����
		nNameRight = strJson->Find('\"',nNameRight);
		if((*strJson)[nNameRight - 1] == '\\') goto name;
	}
	//��ʱnNameRight��λ��������
	//Ѱ��˫����֮���ð��
	int nColon = strJson->Find(':',nNameRight + 1);
	//������ֶ�����ð�����п���ȫ������Ч�ַ���һ����json��Ӧ�÷���0
	if(nNameRight < 0 && nColon < 0){
		CString strJsonTemp = *strJson;
		strJsonTemp.Replace("\t","");
		strJsonTemp.Replace("\r\n","");
		strJsonTemp.Replace("\n","");
		strJsonTemp.Replace(" ","");
		if(strJsonTemp != "{}") mapError[*strJson] = "����ʶ��Ĳ����ַ���";
		return 0;
	}
	//����Ҳ����Ҳ����ŵ���ð��
	if(nNameRight == -1 && nColon >= 0){
		mapError[*strJson] = "�ֶ�ֵֻ�����������";
		return 0;
	}
	//����Ҳ���
	if(nColon == -1 && nNameRight >= 0){
		mapError[*strJson] = "���ֶ�������ð��";
		return 0;
	}
	//���ֶ�ȡ��
	CstrValue strNameValue = strJson->Mid(nNameLeft,nColon - nNameLeft);
	if(strNameValue.type == 1) *strName = strNameValue.strValue;
	else{
		*strName = strNameValue.strValue;
		mapError[strJson->Mid(nNameLeft,nColon - nNameLeft)] = "����ʶ����ֶ���";
	}

	int temp = nColon;
	while(1){
		temp++;
		//�����һ����������˵���ҵ���һ���ֶ�
		if((*strJson)[temp] == '\"'){
			*flag = 1;
			rem:
			temp = strJson->Find("\"",temp + 1);
			if((*strJson)[temp - 1] == '\\') goto rem;
			//��ʱtemp��ֵʱ�Ҳ����ŵ�λ�ã������ﵽ���ű��붼����Ч�ַ�
			*strValue = strJson->Mid(nColon + 1,temp - nColon);
			while(1){
				temp++;
				if((*strJson)[temp] == '\t' || ((*strJson)[temp] == '\r' && (*strJson)[temp + 1] == '\n') || (*strJson)[temp] == '\n' || (*strJson)[temp] == ' ') continue;
				else if((*strJson)[temp] == ','){
					strJson->Delete(nNameLeft,temp - nNameLeft + 1);
					return 1;
				}
				//˵�����˽�β
				else if((*strJson)[temp] == '}'){
					strJson->Delete(nNameLeft,temp - nNameLeft);
					return 1;
				}
				else if((*strJson)[temp] == 0){
					mapError[*strJson] = "�ֶ�ֵ���޴�����";
					return 0;
				}
				else mapError[*strJson] = "�ַ����ֶ�ֵ���ж����ַ�";
			}
		}
		//�����һ�����ֶ���˵������ҵ�����һ���ֶ�
		if((*strJson)[temp] == ','){
			*strValue = strJson->Mid(nColon + 1,temp - nColon - 1);
			//ɾ���ҵ��Ĳ��֣���������
			strJson->Delete(nNameLeft,temp - nNameLeft + 1);
			//�ҵ��ֶ����־��Ϊ1
			*flag = 1;
			break;
		}
		//�����һ������[˵���ҵ���һ�����飬ȡ��strValue�ﲻ����[]��ɾ��ʱ����]ɾ��
		if((*strJson)[temp] == '['){
			//����ҵ���һ�����飬��ôð�ź�[֮ǰ���붼����Ч�ַ�
			CString strTemp = strJson->Mid(nColon + 1,temp - nColon - 1);
			strTemp.Replace("\t","");
			strTemp.Replace("\r\n","");
			strTemp.Replace("\n","");
			strTemp.Replace(" ","");
			if(strTemp != "") mapError[strJson->Mid(nColon + 1,temp - nColon - 1)] = "ð�ź�������ж����ַ�";

			CStringManager manager = *strJson;
			int nszRight = manager.FindOther('[',']',temp);
			if(nszRight == -1) mapError[*strJson] = "[]��ƥ��";
			*strValue = strJson->Mid(temp + 1,nszRight - temp - 1);
			//���ҵ�����Ķ���Ȼ����ɾ���������}˵��ģ���������ȡ}֮ǰ��λ��
			while(1){
				nszRight++;
				if((*strJson)[nszRight] == '\t' || ((*strJson)[nszRight] == '\r' && (*strJson)[nszRight + 1] == '\n') || (*strJson)[nszRight] == '\n' || (*strJson)[nszRight] == ' ') continue;
				else if((*strJson)[nszRight] == '}'){
					nszRight--;
					break;
				}
				else if((*strJson)[nszRight] == ',') break;
				else mapError[*strJson] = "������ж����ַ�";
			}
			strJson->Delete(nNameLeft,nszRight - nNameLeft + 1);
			
			//�ҵ������־��Ϊ2
			*flag = 2;
			break;
		}
		//����ҵ��˴������Ҳ�˵��ֻ��һ���ֶ�
		if((*strJson)[temp] == '}'){
			*strValue = strJson->Mid(nColon + 1,temp - nColon - 1);
			//ɾ���ҵ��Ĳ��֣�������������
			strJson->Delete(nNameLeft,temp - nNameLeft);
			//�ҵ��ֶα�־��Ϊ1
			*flag = 1;
			break;
		}
		//����ҵ���һ�����������˵��������һ��json��ȡ������������
		if((*strJson)[temp] == '{'){
			//����ҵ���һ�����飬��ôð�ź�[֮ǰ���붼����Ч�ַ�
			CString strTemp = strJson->Mid(nColon + 1,temp - nColon - 1);
			strTemp.Replace("\t","");
			strTemp.Replace("\r\n","");
			strTemp.Replace("\n","");
			strTemp.Replace(" ","");
			if(strTemp != "") mapError[strJson->Mid(nColon + 1,temp - nColon - 1)] = "ð�ź�json���ж����ַ�";

			CStringManager manager = *strJson;
			int nszRight = manager.FindOther('{','}',temp);
			if(nszRight == -1) mapError[*strJson] = "{}��ƥ��";
			*strValue = strJson->Mid(temp,nszRight - temp + 1);
			//���ҵ�����Ķ���Ȼ����ɾ���������}˵��ģ���������ȡ}֮ǰ��λ��
			while(1){
				nszRight++;
				if((*strJson)[nszRight] == '\t' || ((*strJson)[nszRight] == '\r' && (*strJson)[nszRight + 1] == '\n') || (*strJson)[nszRight] == '\n' || (*strJson)[nszRight] == ' ') continue;
				else if((*strJson)[nszRight] == '}'){
					nszRight--;
					break;
				}
				else if((*strJson)[nszRight] == ',') break;
				else mapError[*strJson] = "json���ж����ַ�";
			}
			strJson->Delete(nNameLeft,nszRight - nNameLeft + 1);
			//�ҵ�json��־��Ϊ3
			*flag = 3;
			break;
		}
	}
	return 1;
}

void CjsonA::LoadOneModule(CString strName,CString strValue,BOOL flag){
	//����ҵ���һ���ֶ�
	if(flag == 1){
		CstrValue strValueTemp = strValue;
		if(strValueTemp.type == -1){
			mapError[strValue] = "����ʶ����ֶ�ֵ";
		}
		mapdata[strName] = (Cjson)strValueTemp;
	}
	//����ҵ���һ������
	if(flag == 2){
		CszValue szValueTemp = strValue;
		mapdata[strName] = szValueTemp;
		if(szValueTemp.mapszError.size() != 0){
			auto it = szValueTemp.mapszError.begin();
			for(;it != szValueTemp.mapszError.end();it++){
				mapError[it->first] = it->second;
			}
		}
	}
	//����ҵ���һ��json
	if(flag == 3){
		CjsonA jsonTemp;
		map<CString,CString> mapJsonError = jsonTemp.LoadJson(strValue);
		mapdata[strName] = jsonTemp;

		if(mapJsonError.size() != 0){
			auto it = mapJsonError.begin();
			for(;it != mapJsonError.end();it++){
				mapError[it->first] = it->second;
			}
		}
	}
}

void CjsonA::OnlyLoadOneJson(CString strJson){
	//��ȡ����һ�飬���д�����ȡ�ڶ�����д���ֱ������˳�ѭ��
	while(1){
		CString strName = "";
		CString strValue = "";
		BOOL flag = 0;
		//ȡ��һ��ģ�飬���ģ�������һ���ֶο�����һ�����飬flag0��ʾ�ֶΣ�1��ʾ���飬ȡ��strOneJson�У�ͬʱstrJson��ȥ��ȡ���Ĳ���
		BOOL nNext = GetOneModule(&strJson,&flag,&strName,&strValue);
		if(nNext == 0) break;
		//������ֶλ�������ص���Ա������
		LoadOneModule(strName,strValue,flag);
	}
}

void CjsonA::GetOneJson(CString *strJson,CString* strOneJson){
	int nLeft = strJson->Find('{');
	if(nLeft == -1) mapError[*strJson] = "�Ҳ���{";
	else{
		CString strTemp = strJson->Mid(0,nLeft);
		strTemp.Replace("\t","");
		strTemp.Replace("\r\n","");
		strTemp.Replace("\n","");
		strTemp.Replace(" ","");
		if(strTemp != "") mapError[*strJson] = "jsonǰ�ж����ַ�";
	}
	CStringManager manager = *strJson;
	int nRight = manager.FindOther('{','}',nLeft);
	if(nRight == -1) mapError[*strJson] = "{}��ƥ��";
	else{
		CString strJsonNext = strJson->Mid(nRight + 1,strJson->GetLength() - nRight - 1);
		strJsonNext.Replace("\t","");
		strJsonNext.Replace("\r\n","");
		strJsonNext.Replace("\n","");
		strJsonNext.Replace(" ","");
		if(strJsonNext != "") mapError[*strJson] = "json���ж����ַ�";
	}
	*strOneJson = strJson->Mid(nLeft,nRight - nLeft + 1);
	*strJson = strJson->Mid(nRight + 1,strJson->GetLength() - nRight);
}

map<CString,CString> CjsonA::LoadJson(CString strJson){
	//�Ȱ��ڲ����
	mapdata.clear();
	mapError.clear();
	//��ȡ����һ��json��ͬʱȥ��ȡ���Ĳ���
	CString strOneJson = "";
	GetOneJson(&strJson,&strOneJson);
	OnlyLoadOneJson(strOneJson);
	return mapError;
}

vector<CString> CjsonA::GetField(){
	vector<CString> vecField;
	auto it = mapdata.begin();
	for(;it != mapdata.end();it++){
		vecField.push_back(it->first);
	}
	return vecField;
}

int CjsonA::size(){
	return mapdata.size();
}

CString CjsonA::toCString(CString NewLineSign,CString FormatSign,int FormatLength){
	CString strResult = "{}";
	int nInsert = strResult.GetLength() - 1;
	int i = -1;
	auto it = mapdata.begin();
	for(;it != mapdata.end();it++){
		i++;
		CString strFieldTemp = it->first;
		Cjson TypeValueTemp = it->second;
		strResult = AddTypeValue(strResult,&nInsert,!i,strFieldTemp,TypeValueTemp,NewLineSign,FormatSign,FormatLength);
	}
	CString strt = "";
	int lengthtemp = FormatLength - 1;
	while(lengthtemp--!=0){
		strt = strt + FormatSign;
	}
	strResult.Insert(strResult.GetLength() - 1,NewLineSign + strt);
	return strResult;
}

CString CjsonA::AddTypeValue(CString strResult,int *nInsert,BOOL ifFirst,CString strField,Cjson TypeValue,CString NewLineSign,CString FormatSign,int FormatLength){
	int length = FormatLength;
	CString strFormatSign = "";
	while(length--!=0){
		strFormatSign = strFormatSign + FormatSign;
	}
	CString strOne = strFormatSign + "\"" + strField + "\"";
	if(TypeValue.type == "class CstrValue"){
		CstrValue strValueTemp = TypeValue.toValue();
		//�ַ���
		if(strValueTemp.type == 1){
			strOne = strOne + " : \"" + strValueTemp.strValue + "\"";
		}
		//������С��
		if(strValueTemp.type == 2 || strValueTemp.type == 3){
			strOne = strOne + " : " + strValueTemp.strValue;
		}
	}
	if(TypeValue.type == "class CszValue"){
		CszValue szValue = TypeValue.tosz();
		CString strszValue = "";
		int i = -1;
		while(i++ != szValue.size() - 1){
			if(i != 0) strszValue = strszValue + ",";
			Cjson TypeValueTemp = szValue.vecszValue.at(i);
			if(TypeValueTemp.type == "class CstrValue"){
				CstrValue strValueTemp = TypeValueTemp.toValue();
				//�ַ���
				if(strValueTemp.type == 1){
					strszValue = strszValue + "\"" + strValueTemp.strValue + "\"";
				}
				//������С��
				if(strValueTemp.type == 2 || strValueTemp.type == 3){
					strszValue = strszValue + strValueTemp.strValue;
				}
			}
			if(TypeValueTemp.type == "class CjsonA"){
				CjsonA jsonTemp = TypeValueTemp.toJson();
				CString strResultTemp = jsonTemp.toCString(NewLineSign,FormatSign,FormatLength + 1);
				strszValue = strszValue + strResultTemp;
			}
		}
		strOne = strOne + " : [" + strszValue + "]";//������
	}
	if(TypeValue.type == "class CjsonA"){
		CjsonA jsonTemp = TypeValue.toJson();
		CString strResultTemp = jsonTemp.toCString(NewLineSign,FormatSign,FormatLength + 1);
		strOne = strOne + " : " + strResultTemp;
	}
	if(ifFirst == 1){
		strOne = NewLineSign + strOne;
	}
	else{
		strOne = "," + NewLineSign + strOne;
	}
	strResult.Insert(*nInsert,strOne);
	*nInsert = *nInsert + strOne.GetLength();
	return strResult;
}