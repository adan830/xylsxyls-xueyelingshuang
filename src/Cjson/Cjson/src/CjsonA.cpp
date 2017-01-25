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

BOOL CjsonA::GetOneModule(string* strJson,BOOL* flag,string* strName,string *strValue){
	int nNameLeft = CStringManager::Find(*strJson,'{');
	nNameLeft++;
	int nNameRight = nNameLeft;
	//��һ���ҵ������ֶ����������λ��
	nNameRight = CStringManager::Find(*strJson,'\"', nNameRight);
	if(nNameRight >= 0){
		name:
		//�ڶ����ҵ������Ҳ�����
		nNameRight = CStringManager::Find(*strJson,'\"', nNameRight);
		if((*strJson)[nNameRight - 1] == '\\') goto name;
	}
	//��ʱnNameRight��λ��������
	//Ѱ��˫����֮���ð��
	int nColon = CStringManager::Find(*strJson,':', nNameRight + 1);
	//������ֶ�����ð�����п���ȫ������Ч�ַ���һ����json��Ӧ�÷���0
	if(nNameRight < 0 && nColon < 0){
		string strJsonTemp = *strJson;
		CStringManager::Replace(strJsonTemp,"\t", "");
		CStringManager::Replace(strJsonTemp,"\r\n", "");
		CStringManager::Replace(strJsonTemp,"\n", "");
		CStringManager::Replace(strJsonTemp," ", "");
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
	CstrValue strNameValue = CStringManager::Mid(*strJson,nNameLeft,nColon - nNameLeft);
	if(strNameValue.type == 1) *strName = strNameValue.strValue;
	else{
		*strName = strNameValue.strValue;
		mapError[CStringManager::Mid(*strJson,nNameLeft, nColon - nNameLeft)] = "����ʶ����ֶ���";
	}

	int temp = nColon;
	while(1){
		temp++;
		//�����һ����������˵���ҵ���һ���ֶ�
		if((*strJson)[temp] == '\"'){
			*flag = 1;
			rem:
			temp = CStringManager::Find(*strJson,"\"", temp + 1);
			//����Ҳ������ţ�˵��������һ���������
			if(temp == -1){
				mapError[*strJson] = "���Ҳ�����";
				return 0;
			}
			if((*strJson)[temp - 1] == '\\') goto rem;
			//��ʱtemp��ֵʱ�Ҳ����ŵ�λ�ã������ﵽ���ű��붼����Ч�ַ�
			*strValue = CStringManager::Mid(*strJson,nColon + 1, temp - nColon);
			while(1){
				temp++;
				if((*strJson)[temp] == '\t' || ((*strJson)[temp] == '\r' && (*strJson)[temp + 1] == '\n') || (*strJson)[temp] == '\n' || (*strJson)[temp] == ' ') continue;
				else if((*strJson)[temp] == ','){
					CStringManager::Delete(*strJson,nNameLeft, temp - nNameLeft + 1);
					return 1;
				}
				//˵�����˽�β
				else if((*strJson)[temp] == '}'){
					CStringManager::Delete(*strJson,nNameLeft, temp - nNameLeft);
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
			*strValue = CStringManager::Mid(*strJson,nColon + 1, temp - nColon - 1);
			//ɾ���ҵ��Ĳ��֣���������
			CStringManager::Delete(*strJson,nNameLeft, temp - nNameLeft + 1);
			//�ҵ��ֶ����־��Ϊ1
			*flag = 1;
			break;
		}
		//�����һ������[˵���ҵ���һ�����飬ȡ��strValue�ﲻ����[]��ɾ��ʱ����]ɾ��
		if((*strJson)[temp] == '['){
			//����ҵ���һ�����飬��ôð�ź�[֮ǰ���붼����Ч�ַ�
			string strTemp = CStringManager::Mid(*strJson,nColon + 1,temp - nColon - 1);
			CStringManager::Replace(strTemp,"\t", "");
			CStringManager::Replace(strTemp,"\r\n", "");
			CStringManager::Replace(strTemp,"\n", "");
			CStringManager::Replace(strTemp," ", "");
			if(strTemp != "") mapError[CStringManager::Mid(*strJson,nColon + 1,temp - nColon - 1)] = "ð�ź�������ж����ַ�";

			CStringManager manager = *strJson;
			int nszRight = manager.FindOther('[',']',temp);
			if(nszRight == -1) mapError[*strJson] = "[]��ƥ��";
			*strValue = CStringManager::Mid(*strJson,temp + 1, nszRight - temp - 1);
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
			CStringManager::Delete(*strJson,nNameLeft, nszRight - nNameLeft + 1);
			
			//�ҵ������־��Ϊ2
			*flag = 2;
			break;
		}
		//����ҵ��˴������Ҳ�˵��ֻ��һ���ֶ�
		if((*strJson)[temp] == '}'){
			*strValue = CStringManager::Mid(*strJson,nColon + 1, temp - nColon - 1);
			//ɾ���ҵ��Ĳ��֣�������������
			CStringManager::Delete(*strJson,nNameLeft, temp - nNameLeft);
			//�ҵ��ֶα�־��Ϊ1
			*flag = 1;
			break;
		}
		//����ҵ���һ�����������˵��������һ��json��ȡ������������
		if((*strJson)[temp] == '{'){
			//����ҵ���һ�����飬��ôð�ź�[֮ǰ���붼����Ч�ַ�
			string strTemp = CStringManager::Mid(*strJson,nColon + 1, temp - nColon - 1);
			CStringManager::Replace(strTemp,"\t", "");
			CStringManager::Replace(strTemp,"\r\n", "");
			CStringManager::Replace(strTemp,"\n", "");
			CStringManager::Replace(strTemp," ", "");
			if (strTemp != "") mapError[CStringManager::Mid(*strJson,nColon + 1, temp - nColon - 1)] = "ð�ź�json���ж����ַ�";

			CStringManager manager = *strJson;
			int nszRight = manager.FindOther('{','}',temp);
			if(nszRight == -1) mapError[*strJson] = "{}��ƥ��";
			*strValue = CStringManager::Mid(*strJson,temp, nszRight - temp + 1);
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
			CStringManager::Delete(*strJson,nNameLeft, nszRight - nNameLeft + 1);
			//�ҵ�json��־��Ϊ3
			*flag = 3;
			break;
		}
	}
	return 1;
}

void CjsonA::LoadOneModule(string strName,string strValue,BOOL flag){
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
		map<string,string> mapJsonError = jsonTemp.LoadJson(strValue);
		mapdata[strName] = jsonTemp;

		if(mapJsonError.size() != 0){
			auto it = mapJsonError.begin();
			for(;it != mapJsonError.end();it++){
				mapError[it->first] = it->second;
			}
		}
	}
}

void CjsonA::OnlyLoadOneJson(string strJson){
	//��ȡ����һ�飬���д�����ȡ�ڶ�����д���ֱ������˳�ѭ��
	while(1){
		string strName = "";
		string strValue = "";
		BOOL flag = 0;
		//ȡ��һ��ģ�飬���ģ�������һ���ֶο�����һ�����飬flag0��ʾ�ֶΣ�1��ʾ���飬ȡ��strOneJson�У�ͬʱstrJson��ȥ��ȡ���Ĳ���
		BOOL nNext = GetOneModule(&strJson,&flag,&strName,&strValue);
		if(nNext == 0) break;
		//������ֶλ�������ص���Ա������
		LoadOneModule(strName,strValue,flag);
	}
}

void CjsonA::GetOneJson(string *strJson,string* strOneJson){
	int nLeft = CStringManager::Find(*strJson,'{');
	if(nLeft == -1) mapError[*strJson] = "�Ҳ���{";
	else{
		string strTemp = CStringManager::Mid(*strJson,0, nLeft);
		CStringManager::Replace(strTemp,"\t", "");
		CStringManager::Replace(strTemp,"\r\n", "");
		CStringManager::Replace(strTemp,"\n", "");
		CStringManager::Replace(strTemp," ", "");
		if(strTemp != "") mapError[*strJson] = "jsonǰ�ж����ַ�";
	}
	CStringManager manager = *strJson;
	int nRight = manager.FindOther('{','}',nLeft);
	if(nRight == -1) mapError[*strJson] = "{}��ƥ��";
	else{
		string strJsonNext = CStringManager::Mid(*strJson, nRight + 1, CStringManager::GetLength(*strJson) - nRight - 1);
		CStringManager::Replace(strJsonNext,"\t", "");
		CStringManager::Replace(strJsonNext,"\r\n", "");
		CStringManager::Replace(strJsonNext,"\n", "");
		CStringManager::Replace(strJsonNext," ", "");
		if(strJsonNext != "") mapError[*strJson] = "json���ж����ַ�";
	}
	*strOneJson = CStringManager::Mid(*strJson,nLeft, nRight - nLeft + 1);
	*strJson = CStringManager::Mid(*strJson, nRight + 1, CStringManager::GetLength(*strJson) - nRight);
}

map<string,string> CjsonA::LoadJson(string strJson){
	//�Ȱ��ڲ����
	mapdata.clear();
	mapError.clear();
	//��ȡ����һ��json��ͬʱȥ��ȡ���Ĳ���
	string strOneJson = "";
	GetOneJson(&strJson,&strOneJson);
	OnlyLoadOneJson(strOneJson);
	return mapError;
}

vector<string> CjsonA::GetField(){
	vector<string> vecField;
	auto it = mapdata.begin();
	for(;it != mapdata.end();it++){
		vecField.push_back(it->first.c_str());
	}
	return vecField;
}

int CjsonA::size(){
	return mapdata.size();
}

string CjsonA::tostring(string NewLineSign,string FormatSign,int FormatLength){
	string strResult = "{}";
	int nInsert = CStringManager::GetLength(strResult) - 1;
	int i = -1;
	auto it = mapdata.begin();
	for(;it != mapdata.end();it++){
		i++;
		string strFieldTemp = it->first.c_str();
		Cjson TypeValueTemp = it->second;
		strResult = AddTypeValue(strResult,&nInsert,!i,strFieldTemp,TypeValueTemp,NewLineSign,FormatSign,FormatLength);
	}
	string strt = "";
	int lengthtemp = FormatLength - 1;
	while(lengthtemp--!=0){
		strt = strt + FormatSign;
	}
	CStringManager::Insert(strResult, CStringManager::GetLength(strResult) - 1, NewLineSign + strt);
	return strResult;
}

string CjsonA::AddTypeValue(string strResult,int *nInsert,BOOL ifFirst,string strField,Cjson TypeValue,string NewLineSign,string FormatSign,int FormatLength){
	int length = FormatLength;
	string strFormatSign = "";
	while(length--!=0){
		strFormatSign = strFormatSign + FormatSign;
	}
	string strOne = strFormatSign + "\"" + strField + "\"";
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
		string strszValue = "";
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
				string strResultTemp = jsonTemp.tostring(NewLineSign,FormatSign,FormatLength + 1);
				strszValue = strszValue + strResultTemp;
			}
		}
		strOne = strOne + " : [" + strszValue + "]";//������
	}
	if(TypeValue.type == "class CjsonA"){
		CjsonA jsonTemp = TypeValue.toJson();
		string strResultTemp = jsonTemp.tostring(NewLineSign,FormatSign,FormatLength + 1);
		strOne = strOne + " : " + strResultTemp;
	}
	if(ifFirst == 1){
		strOne = NewLineSign + strOne;
	}
	else{
		strOne = "," + NewLineSign + strOne;
	}
	CStringManager::Insert(strResult,*nInsert,strOne);
	*nInsert = *nInsert + CStringManager::GetLength(strOne);
	return strResult;
}