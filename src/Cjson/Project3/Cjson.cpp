#include <SDKDDKVer.h>
#include "Cjson.h"
#include <map>
using namespace std;
#include "CStringManagerAPI.h"
#include "CstrValue.h"
#include "CszValue.h" 

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
		CTypeValue strTypeValueTemp;
		strTypeValueTemp.fill(strValueTemp);
		mapdata[strName] = strTypeValueTemp;
		strTypeValueTemp.free();
	}
	//����ҵ���һ������
	if(flag == 2){
		vecsz.push_back(strName);
		CszValue szValueTemp = strValue;
		mapsz[strName] = szValueTemp;
		CTypeValue szTypeValueTemp;
		szTypeValueTemp.fill(szValueTemp);
		mapdata[strName] = szTypeValueTemp;
		szTypeValueTemp.free();
	}
	//����ҵ���һ��json
	if(flag == 3){
		vecjson.push_back(strName);
		Cjson jsonTemp;
		jsonTemp.LoadJson(strValue);
		mapjson[strName] = jsonTemp;
		CTypeValue jsonTypeValueTemp;
		jsonTypeValueTemp.fill(jsonTemp);
		mapdata[strName] = jsonTypeValueTemp;
		jsonTypeValueTemp.free();
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

int main(){
	int x = atoi("  \t\t \r\n   1");
	CString str = "123456";
	
	while(1){
		Cjson json;
		json.LoadJson("{\"sieipaddr\" : \"192.168.1.1\" ,\"sieport\" : 9000,\"recordList\" : [{\"nodeid\" : 1,\"nodename\" : \"XXX����\",\"domaincode\" : \"��ID\",\"devicecode\" : \"�豸ID\",\"channlecode\" : \"ͨ��ID\",\"streamcode\" : \"����ID\"}]}");
	}
	/*
	auto it = json.mapdata.begin();
	it++;
	it++;
	it++;
	it++;
	auto key5it = ((Cjson *)it->second.pClass)->mapdata.begin();
	CString kkk = ((CstrValue *)key5it->second.pClass)->strValue;
	key5it++;
	CString hhh = ((CstrValue *)((CszValue *)key5it->second.pClass)->vecszValue.at(0).pClass)->strValue;
	int n99 = ((CstrValue *)((CszValue *)key5it->second.pClass)->vecszValue.at(1).pClass)->nValue;
	auto nameit = ((Cjson *)((CszValue *)key5it->second.pClass)->vecszValue.at(2).pClass)->mapdata.begin();
	CString zhangsan = ((CstrValue *)nameit->second.pClass)->strValue;
	*/
	/*
	int xx = ((CstrValue *)json.mapdata["key1"])->nValue;

	

	auto it = json.mapdata.begin();
	CString onefirst = it->first;
	int onesecond = ((CstrValue*)it->second)->nValue;

	it++;
	CString twofirst = it->first;
	CString twosecond = ((CstrValue*)it->second)->strValue;

	it++;
	CString thirdfirst = it->first;
	double thirdsecond = ((CstrValue*)it->second)->dValue;

	it++;
	CString forthfirst = it->first;
	//CString forthsecond = ((CszValue*)it->second);

	it++;
	CString fifthfirst = it->first;
	auto fifthsecondit = ((Cjson*)it->second)->mapdata.begin();

	CString fifthsecondOneFirst = fifthsecondit->first;
	CString fifthsecondOnesecond = ((CstrValue *)fifthsecondit->second)->strValue;

	fifthsecondit++;
	CString fifthsecondTwoFirst   = fifthsecondit->first;
	CString fifthsecondTwosecond0 = ((CszValue *)fifthsecondit->second)->vecszOneValue.at(0).strValue.strValue;
	int     fifthsecondTwosecond1 = ((CszValue *)fifthsecondit->second)->vecszOneValue.at(1).strValue.nValue;
	auto  fifthsecondTwosecond2it = ((CszValue *)fifthsecondit->second)->vecjson.at(0).mapdata.begin();

	CString fifthsecondTwosecond2OneFirst = fifthsecondTwosecond2it->first;
	CString fifthsecondTwosecond2OneSecond = ((CstrValue *)fifthsecondTwosecond2it->second)->strValue;*/
	/*
	CString strFirstJsonName = json.vecjson.at(0);
	Cjson strJson = json.mapjson.find(strFirstJsonName)->second;
	CString szName = strJson.vecsz.at(0);
	CszValue strszValue = strJson.mapsz.find(szName)->second;
	CString xxx = strszValue.vecszOneValue.at(0).strValue.strValue;
	int xx = json.mapjson.find(json.vecjson.at(0))->second.mapsz.find(json.mapjson.find(json.vecjson.at(0))->second.vecsz.at(0))->second.vecszOneValue.at(1).strValue.nValue;
	
	CString str2 = (++(json.mapstr.begin()))->first;
	auto it = json.mapstr.begin();
	it++;
	CString str3 = it->first;*/
	return 0;
}