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
			//������������ֻ�����json�����֣�����jsonʱ���������ѭ��������0�˳�����������ֻҪ�����������ŵ����
			CString strTemp = strValue.Mid(begin,i - begin);
			int j = -1;
			while(j++ != strTemp.GetLength() - 1){
				if(strTemp[j] >= '0' && strTemp[j] <= '9') break;
			}
			//���������������ֳ��֣�Ĭ�ϵ����ִ���������˵��û�����ֳ��֣����ڿ��ַ��������ַ���������
			if(j != strTemp.GetLength()){
				vecszValue.push_back((CstrValue)strTemp);
			}
			break;
		}
		//������ҵ��˶���˵��������һ���ֶ�ֵ
		if(strValue[i] == ','){
			vecszValue.push_back((CstrValue)strValue.Mid(begin,i - begin));
			num++;
			//ȡ���ź��λ����Ϊ��ʼ����Ϊi����ѭ����ʼ��++�����Բ���Ҫ��
			begin = i + 1;
		}
		//����ҵ���һ��{˵���ҵ���һ��json
		if(strValue[i] == '{'){
			CStringManager manager = strValue;
			int nRight = manager.FindOther('{','}',i);
			Cjson json;
			json.LoadJson(strValue.Mid(i,nRight - i + 1));
			vecszValue.push_back(json);
			num++;
			//ȡ���ź��λ����Ϊ��ʼ
			while(1){
				//��ֹ�ڽ���ʱ����Ϊû�ҵ����ŵ���i����ԭ�������ŵ�λ�ã��Ȱ�i�ŵ������ŵ�λ�ã�ѭ����ʼ��ʱ�����++��Ѱ����һλ
				i = nRight;
				nRight++;
				if(strValue[nRight] == 0) return;
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

CszValue::~CszValue(){

}

int CszValue::size(){
	return vecszValue.size();
}