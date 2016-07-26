#include <SDKDDKVer.h>
#include "Cjson.h"
#include <map>
using namespace std;
#include "CStringManagerAPI.h"
#include "CstrValue.h"
#include "CszValue.h" 

Cjson::Cjson(){

}

Cjson::~Cjson(){

}

BOOL GetOneModule(CString* strJson,BOOL* flag,CString* strName,CString *strValue){

	int nNameLeft = strJson->Find('\"');
	//����Ҳ�������˵������һ���յ�json���򷵻�0
	if(nNameLeft == -1) return 0;
	int nNameRight = strJson->Find('\"',nNameLeft + 1);
	//��õ�һ��˫�����������
	*strName = strJson->Mid(nNameLeft + 1,nNameRight - nNameLeft - 1);
	//Ѱ��˫����֮���ð��
	int nColon = strJson->Find(':',nNameRight + 1);
	int temp = nColon;
	while(1){
		temp++;
		//�����һ�����ֶ��Ż��ߴ�����˵������ҵ�����һ���ֶ�
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
			CStringManager manager = *strJson;
			int nszRight = manager.FindOther('[',']',temp);
			*strValue = strJson->Mid(temp + 1,nszRight - temp - 1);
			//���ҵ�����Ķ���Ȼ����ɾ���������}˵��ģ���������ȡ}֮ǰ��λ��
			while(1){
				nszRight++;
				if((*strJson)[nszRight] == '}'){
					nszRight--;
					break;
				}
				if((*strJson)[nszRight] == ',') break;
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
			CStringManager manager = *strJson;
			int nszRight = manager.FindOther('{','}',temp);
			*strValue = strJson->Mid(temp,nszRight - temp + 1);
			//���ҵ�����Ķ���Ȼ����ɾ���������}˵��ģ���������ȡ}֮ǰ��λ��
			while(1){
				nszRight++;
				if((*strJson)[nszRight] == '}'){
					nszRight--;
					break;
				}
				if((*strJson)[nszRight] == ',') break;
			}
			strJson->Delete(nNameLeft,nszRight - nNameLeft + 1);
			//�ҵ�json��־��Ϊ3
			*flag = 3;
			break;
		}
	}
	return 1;
}

void Cjson::LoadOneModule(CString strName,CString strValue,BOOL flag){
	//����ҵ���һ���ֶ�
	if(flag == 1){
		vecstr.push_back(strName);
		CstrValue strValueTemp = strValue;
		mapstr[strName] = strValueTemp;
		CTypeValue strTypeValueTemp = strValueTemp;
		mapdata[strName] = strTypeValueTemp;
	}
	//����ҵ���һ������
	if(flag == 2){
		vecsz.push_back(strName);
		CszValue szValueTemp = strValue;
		mapsz[strName] = szValueTemp;
		CTypeValue szTypeValueTemp = szValueTemp;
		mapdata[strName] = szTypeValueTemp;
	}
	//����ҵ���һ��json
	if(flag == 3){
		vecjson.push_back(strName);
		Cjson jsonTemp;
		jsonTemp.LoadJson(strValue);
		mapjson[strName] = jsonTemp;
		CTypeValue jsonTypeValueTemp = jsonTemp;
		mapdata[strName] = jsonTypeValueTemp;
	}
}

void Cjson::OnlyLoadOneJson(CString strJson){
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

BOOL GetOneJson(CString *strJson,CString* strOneJson){
	int nLeft = strJson->Find('{');
	if(nLeft == -1) return 0;
	CStringManager manager = *strJson;
	int nRight = manager.FindOther('{','}',nLeft);
	*strOneJson = strJson->Mid(nLeft,nRight - nLeft + 1);
	*strJson = strJson->Mid(nRight + 1,strJson->GetLength() - nRight);
	return 1;
}

void Cjson::LoadJson(CString strJson){
	//�Ȱ��ڲ����
	vecstr.clear();
	vecsz.clear();
	vecjson.clear();
	mapdata.clear();
	mapjson.clear();
	mapstr.clear();
	mapsz.clear();
	//��ȡ����һ��json��ͬʱȥ��ȡ���Ĳ���
	while(1){
		CString strOneJson = "";
		BOOL nNext = GetOneJson(&strJson,&strOneJson);
		if(nNext == 0) break;
		OnlyLoadOneJson(strOneJson);
	}
	return;
}

vector<CString> Cjson::GetField(){
	vector<CString> vecField;
	auto it = mapdata.begin();
	for(;it != mapdata.end();it++){
		vecField.push_back(it->first);
	}
	return vecField;
}

int Cjson::size(){
	return mapdata.size();
}

CString Cjson::toCString(CString NewLineSign,CString FormatSign,int FormatLength){
	CString strResult = "{}";
	int nInsert = strResult.GetLength() - 1;
	int i = -1;
	auto it = mapdata.begin();
	for(;it != mapdata.end();it++){
		i++;
		CString strFieldTemp = it->first;
		CTypeValue TypeValueTemp = it->second;
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

CString Cjson::AddTypeValue(CString strResult,int *nInsert,BOOL ifFirst,CString strField,CTypeValue TypeValue,CString NewLineSign,CString FormatSign,int FormatLength){
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
			CTypeValue TypeValueTemp = szValue.vecszValue.at(i);
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
			if(TypeValueTemp.type == "class Cjson"){
				Cjson jsonTemp = TypeValueTemp.toJson();
				CString strResultTemp = jsonTemp.toCString(NewLineSign,FormatSign,FormatLength + 1);
				strszValue = strszValue + strResultTemp;
			}
		}
		strOne = strOne + " : [" + strszValue + "]";
	}
	if(TypeValue.type == "class Cjson"){
		Cjson jsonTemp = TypeValue.toJson();
		CString strResultTemp = jsonTemp.toCString(NewLineSign,FormatSign,FormatLength + 1);
		strOne = strOne + strResultTemp;
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

int main(){
	
	Cjson json;
	while(1){
		
		static int x = 0;
		x++;
		//if(x > 500) break;
		json.LoadJson("{\"sieipaddr\" : \"192.168.1.1\" ,\"sieport\" : 9000,\"recordList\" : [{\"nodeid\" : 1,\"nodename\" : \"XXX����\",\"domaincode\" : \"��ID\",\"devicecode\" : \"�豸ID\",\"channlecode\" : \"ͨ��ID\",\"streamcode\" : \"����ID\"},{\"nodeid\" : 1,\"nodename\" : \"XXX����\",\"domaincode\" : \"��ID\",\"devicecode\" : \"�豸ID\",\"channlecode\" : \"ͨ��ID\",\"streamcode\" : \"����ID\"}]}");
		json.toCString("\r\n","\t");
		//AfxMessageBox(json.toCString("\r\n","\t"));
		CTypeValue xxxx = json;
		CString zhangsan = xxxx["key5"]["key52"][2]["name"].toValue().strValue;
	}
	CTypeValue xxxx = json;
	int x1 = xxxx["key4"][2].toValue().nValue;
	return 0;
}