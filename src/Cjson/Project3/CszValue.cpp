#include <SDKDDKVer.h>
#include "CszValue.h"
#include "CStringManagerAPI.h"

CszValue::CszValue(){

}

CszValue::CszValue(CString strValue){
	int num = 0;
	int begin = 0;
	int i = -1;
	while(1){
		i++;
		//�������ĩβ���˳�
		if(strValue[i] == 0) break;
		//������ҵ��˶���˵��������һ���ֶ�ֵ
		if(strValue[i] == ','){
			CstrValue strValueTemp = strValue.Mid(begin,i - begin);
			CszOneValue szOneValueTemp(num,strValueTemp);
			vecszOneValue.push_back(szOneValueTemp);
			//
			//CstrValue strValueTemp = new CstrValue(strValue.Mid(begin,i - begin));
			CTypeValue strTypeValue;
			strTypeValue.fill(strValueTemp);
			vecszValue.push_back(strTypeValue);
			strTypeValue.free();
			num++;
			//ȡ���ź��λ����Ϊ��ʼ����Ϊi����ѭ����ʼ��++�����Բ���Ҫ��
			begin = i + 1;
		}
		//����ҵ���һ��{˵���ҵ���һ��json
		if(strValue[i] == '{'){
			CStringManager manager = strValue;
			int nRight = manager.FindOther('{','}',i);
			CString strJsonTemp = strValue.Mid(i,nRight - i + 1);
			Cjson json;
			json.LoadJson(strJsonTemp);
			vecjson.push_back(json);
			//
			CTypeValue jsonTypeValue;
			jsonTypeValue.fill(json);
			vecszValue.push_back(jsonTypeValue);
			jsonTypeValue.free();
			num++;
			//ȡ���ź��λ����Ϊ��ʼ
			while(1){
				//��ֹ�ڽ���ʱ����Ϊû�ҵ����ŵ���i����ԭ�������ŵ�λ�ã��Ȱ�i�ŵ������ŵ�λ�ã�ѭ����ʼ��ʱ�����++��Ѱ����һλ
				i = nRight;
				nRight++;
				if(strValue[nRight] == 0) break;
				if(strValue[nRight] == ','){
					begin = nRight + 1;
					//i����ȡ���ŵ�λ�ã�ѭ����ʼ��ʱ�������++
					i = nRight;
					break;
				}
			}
		}
	}
}