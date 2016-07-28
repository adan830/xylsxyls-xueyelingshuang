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
		strOne = strOne + " : [" + strszValue + "]";//������
	}
	if(TypeValue.type == "class Cjson"){
		Cjson jsonTemp = TypeValue.toJson();
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

int main(){
	
	map<int,int> map;
	map[0] = 1;

	
	Cjson json;
	json.LoadJson("{\"layout\":1,\"videoList\":[{\"wid\":0,\"isAudioValid\":1,\"fileList\":[{\"fileName\":\"F:\\1111\\(2015)�������ֵ�00596��\\(2015)�������ֵ�00596��_���ϳɡ�2016-04-13 16.33.53\\A00_218_1.mp4\",\"startTime\":0,\"stopTime\":3200},{\"fileName\":\"F:\\1111\\(2015)�������ֵ�00596��\\(2015)�������ֵ�00596��_���ϳɡ�2016-04-13 16.33.53\\A00_218_1_1.mp4\",\"startTime\":3200,\"stopTime\":6201},{\"fileName\":\"F:\\1111\\(2015)�������ֵ�00596��\\(2015)�������ֵ�00596��_���ϳɡ�2016-04-13 16.33.53\\A00_218_2.mp4\",\"startTime\":6231,\"stopTime\":6889}]}]}");
	int x = 0;
	Sleep(15000);
	while(1){
		x++;
		if(x >200000){
			break;
		}
		//"{   \"videoList\":[   {\"fileList\":[  {},{}  ]}   ]   }"
		json.LoadJson("{\"layout\":1,\"videoList\":[{\"wid\":0,\"isAudioValid\":1,\"fileList\":[{\"fileName\":\"F:\\1111\\(2015)�������ֵ�00596��\\(2015)�������ֵ�00596��_���ϳɡ�2016-04-13 16.33.53\\A00_218_1.mp4\",\"startTime\":0,\"stopTime\":3200},{\"fileName\":\"F:\\1111\\(2015)�������ֵ�00596��\\(2015)�������ֵ�00596��_���ϳɡ�2016-04-13 16.33.53\\A00_218_1_1.mp4\",\"startTime\":3200,\"stopTime\":6201},{\"fileName\":\"F:\\1111\\(2015)�������ֵ�00596��\\(2015)�������ֵ�00596��_���ϳɡ�2016-04-13 16.33.53\\A00_218_2.mp4\",\"startTime\":6231,\"stopTime\":6889}]}]}");
		//json.toCString("\r\n","    ");
		//AfxMessageBox(json.toCString("\r\n","    "));
		//CTypeValue xxxxx;
		//CTypeValue xxxx = json;
		//CString zhangsan = xxxx["key8"]["key52"][2]["name"].toValue().strValue;
		//CTypeValue ssss = xxxx.toJson().mapdata["key10"];
		//xxxx.toJson().mapdata["key10"] = CstrValue("124");
		//xxxx.toJson().mapdata["key11"] = CszValue("124,\"456\"");
		//xxxx[""] = 1.1;
		//xxxx["layout1"][0]["123"]["1"] = 1.2;
		//AfxMessageBox(json.toCString());
		//xxxx = json;
		//xxxx["key33"][0] = "delete";
		//CszValue szValue = xxxx.toJson().mapdata["key9"].tosz();
		//CString strrrrrr = szValue.vecszValue.at(0).toValue().strValue;
		//xxxx.toJson().mapdata["key9"].tosz().vecszValue.push_back(CstrValue("123456"));
		//CTypeValue strrr = xxxx.toJson().mapdata["key10"];
		//AfxMessageBox(xxxx.toJson().toCString());
	}
	while(1){

	}
	CTypeValue xxxx = json;
	
	int x1 = xxxx["key4"][2].toValue().nValue;
	return 0;
}