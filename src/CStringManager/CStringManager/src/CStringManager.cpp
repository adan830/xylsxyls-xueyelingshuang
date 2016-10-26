#include <SDKDDKVer.h>
#include "CStringManager.h"
#include <vector>
using namespace std;

CStringManager::CStringManager(CString str){
	this->str = str;
}

CStringManager CStringManager::operator = (CString str){
	this->str = str;
	return *this;
}

int CStringManager::FindOther(char cLeft,char cRight,int nSelect){
	vector<int> vecn;
	int nSelectSize = 0;
	int n = 0;
	while(str[n]){
		if(str[n] == cLeft){
			vecn.push_back(n);
			//nSelect���󣬼������ڵ�nSelectSize
			if(nSelect == n) nSelectSize = vecn.size();
		}
		if(str[n] == cRight){
			if(nSelect == n){
				return vecn.at(vecn.size() - 1);
			}
			//�������֮ǰ����size��С����֮ǰ��¼�ģ�˵���ҵ��˶�Ӧ���Ҳ�
			if(vecn.size() == nSelectSize){
				return n;
			}
			vecn.pop_back();
		}
		n++;
	}
	return -1;
}

vector<CString> CStringManager::split(CString separate_character){
	string strTemp = str;
	vector<CString> strs;

	int separate_characterLen = separate_character.GetLength();//�ָ��ַ����ĳ���,�����Ϳ���֧���硰,,�����ַ����ķָ���
	int lastPosition = 0,index = -1;
	while (-1 != (index = strTemp.find(separate_character,lastPosition))){
		strs.push_back(strTemp.substr(lastPosition,index - lastPosition).c_str());   
		lastPosition = index + separate_characterLen;   
	}
	string lastString = strTemp.substr(lastPosition);//��ȡ���һ���ָ����������   
	//if (!lastString.empty()) //������һ���ָ����������ݾ����
	strs.push_back(lastString.c_str());
	return strs;
}