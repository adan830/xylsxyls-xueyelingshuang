#include <SDKDDKVer.h>
#include "CszValue.h"
#include "CStringManagerAPI.h"
#include "CTypeValue.h"
#include "CstrValue.h"
#include "Cjson.h"

CszValue::CszValue(){

}

CszValue::CszValue(CString strValue){
	int num = 0;
	int begin = 0;
	int i = -1;
	while(1){
		i++;
		//�������ĩβ��ȡ�����һ�����˳�
		if(strValue[i] == 0){
			//������������ֻ�����json��ֵ������jsonʱ���������ѭ��������0�˳�����������ֻҪ�����������ŵ����
			CString strTemp = strValue.Mid(begin,i - begin);
			CstrValue strValueTemp = strTemp;
			if(strValueTemp.type == -1){
				//����ǿ����飬��ô���������ַ���Ϊ��Ч�ַ�
				strTemp.Replace("\t","");
				strTemp.Replace("\r\n","");
				strTemp.Replace("\n","");
				strTemp.Replace(" ","");
				//˵���ǿ�����
				if(strTemp == "") break;
				else mapszError[strTemp] = "����ʶ�������ֵ";
			}
			vecszValue.push_back(strValueTemp);
			break;
		}
		//������ҵ��˶���˵��������һ���ֶ�ֵ
		if(strValue[i] == ','){
			CstrValue strValueTemp = strValue.Mid(begin,i - begin);
			if(strValueTemp.type == -1){
				mapszError[strValue.Mid(begin,i - begin)] = "����ʶ�������ֵ";
			}
			vecszValue.push_back(strValueTemp);
			num++;
			//ȡ���ź��λ����Ϊ��ʼ����Ϊi����ѭ����ʼ��++�����Բ���Ҫ��
			begin = i + 1;
		}
		//����ҵ���һ��{˵���ҵ���һ��json
		if(strValue[i] == '{'){
			CString strValueTemp = strValue.Mid(0,i);
			int nPre = strValueTemp.ReverseFind(',');
			strValueTemp = strValueTemp.Mid(nPre + 1,i - nPre - 1);
			strValueTemp.Replace("\t","");
			strValueTemp.Replace("\r\n","");
			strValueTemp.Replace("\n","");
			strValueTemp.Replace(" ","");
			if(strValueTemp != "") mapszError[strValue.Mid(nPre + 1,i - nPre - 1)] = "��������jsonԪ��ǰ�ж����ַ�";

			CStringManager manager = strValue;
			int nRight = manager.FindOther('{','}',i);
			if(nRight == -1) mapszError[strValue] = "{}��ƥ��";
			Cjson json;
			map<CString,CString> mapJsonError = json.LoadJson(strValue.Mid(i,nRight - i + 1));

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