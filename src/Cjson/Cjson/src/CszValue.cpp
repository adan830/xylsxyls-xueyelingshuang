#include "CszValue.h"
#include "CStringManager/CStringManagerAPI.h"
#include "Cjson.h"
#include "CstrValue.h"
#include "CjsonA.h"

CszValue::CszValue(){

}

CszValue::CszValue(string strValue){
	int num = 0;
	int begin = 0;
	int i = -1;
	while(1){
		i++;
		//�������ĩβ��ȡ�����һ�����˳�
		if(strValue[i] == 0){
			//������������ֻ�����json��ֵ������jsonʱ���������ѭ��������0�˳�����������ֻҪ�����������ŵ����
			string strTemp = CStringManager::Mid(strValue,begin,i - begin);
			string strEmpty = strTemp;
			CStringManager::Replace(strEmpty,"\t", "");
			CStringManager::Replace(strEmpty,"\r\n", "");
			CStringManager::Replace(strEmpty,"\n", "");
			CStringManager::Replace(strEmpty," ", "");
			//˵���ǿ�����
			if(strEmpty == "") break;
			//������ǿ�������ʼ����CstrValue����
			CstrValue strValueTemp = strTemp;
			if(strValueTemp.type == -1){
				mapszError[strTemp] = "����ʶ�������ֵ";
			}
			vecszValue.push_back(strValueTemp);
			break;
		}
		//������ҵ��˶���˵��������һ���ֶ�ֵ
		if(strValue[i] == ','){
			CstrValue strValueTemp = CStringManager::Mid(strValue,begin, i - begin);
			if(strValueTemp.type == -1){
				mapszError[CStringManager::Mid(strValue,begin, i - begin)] = "����ʶ�������ֵ";
			}
			vecszValue.push_back(strValueTemp);
			num++;
			//ȡ���ź��λ����Ϊ��ʼ����Ϊi����ѭ����ʼ��++�����Բ���Ҫ��
			begin = i + 1;
		}
		//����ҵ���һ��{˵���ҵ���һ��json
		if(strValue[i] == '{'){
			string strValueTemp = CStringManager::Mid(strValue,0, i);
			int nPre = CStringManager::ReserveFind(strValueTemp,',');
			strValueTemp = CStringManager::Mid(strValueTemp,nPre + 1, i - nPre - 1);
			CStringManager::Replace(strValueTemp,"\t", "");
			CStringManager::Replace(strValueTemp,"\r\n", "");
			CStringManager::Replace(strValueTemp,"\n", "");
			CStringManager::Replace(strValueTemp," ", "");
			if (strValueTemp != "") mapszError[CStringManager::Mid(strValue,nPre + 1, i - nPre - 1)] = "��������jsonԪ��ǰ�ж����ַ�";

			int nRight = CStringManager::FindOther(strValue, '{', '}', i);
			if(nRight == -1) mapszError[strValue] = "{}��ƥ��";
			CjsonA json;
			map<string, string> mapJsonError = json.LoadJson(CStringManager::Mid(strValue,i, nRight - i + 1));

			if(mapJsonError.size() != 0){
				auto it = mapJsonError.begin();
				for(;it != mapJsonError.end();it++){
					mapszError[it->first] = it->second;
				}
			}

			vecszValue.push_back(json);
			num++;
			//ȡ���ź��λ����Ϊ��ʼ
			while(1){
				//��ֹ�ڽ���ʱ����Ϊû�ҵ����ŵ���i����ԭ�������ŵ�λ�ã��Ȱ�i�ŵ������ŵ�λ�ã�ѭ����ʼ��ʱ�����++��Ѱ����һλ
				i = nRight;
				nRight++;
				if(strValue[nRight] == 0) return;
				if(strValue[nRight] == '\t' || (strValue[nRight] == '\r' && strValue[nRight + 1] == '\n') || strValue[nRight] == '\n' || strValue[nRight] == ' ') continue;
				else if(strValue[nRight] == ','){
					begin = nRight + 1;
					//i����ȡ���ŵ�λ�ã�ѭ����ʼ��ʱ�������++
					i = nRight;
					break;
				}
				else mapszError[strValue] = "�����е�json���ж����ַ�";
			}
		}
	}
}

CszValue::~CszValue(){

}

int CszValue::size(){
	return vecszValue.size();
}