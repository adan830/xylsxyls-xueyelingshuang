#include <SDKDDKVer.h>
#include "CStringManager.h"
#include <vector>
using namespace std;
#include <time.h>

#include <shlobj.h>

CStringManager::CStringManager(string str){
	this->strInside = str;
}

CStringManager CStringManager::operator = (string str){
	this->strInside = str;
	return *this;
}

int CStringManager::FindOther(char cLeft,char cRight,int nSelect){
	vector<int> vecn;
	int nSelectSize = 0;
	int n = 0;
	while(strInside[n]){
		if(strInside[n] == cLeft){
			vecn.push_back(n);
			//nSelect���󣬼������ڵ�nSelectSize
			if(nSelect == n) nSelectSize = vecn.size();
		}
		if(strInside[n] == cRight){
			if(nSelect == n){
				if(vecn.size() > 0) return vecn.at(vecn.size() - 1);
				else return -1;
			}
			//�������֮ǰ����size��С����֮ǰ��¼�ģ�˵���ҵ��˶�Ӧ���Ҳ�
			if(vecn.size() == nSelectSize && nSelectSize > 0){
				return n;
			}
			if(vecn.size() > 0) vecn.pop_back();
		}
		n++;
	}
	return -1;
}

vector<string> CStringManager::split(string separate_character){
	string strTemp = strInside;
	vector<string> strs;

	int separate_characterLen = separate_character.length();//�ָ��ַ����ĳ���,�����Ϳ���֧���硰,,�����ַ����ķָ���
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

string CStringManager::RandomString(int nMin,int nMax,vector<char> vecCharacter){
	if(nMin < 0 || nMax < 0 || nMax - nMin < 0) return "";

	if(vecCharacter == vector<char>()){
		char i = -128;
		while(i++ != 127){
			if(i == 0) continue;
			vecCharacter.push_back(i);
		}
		vecCharacter.push_back(-128);
	}

	srand((unsigned int)time(0));
	int nLength = rand() % (nMax - nMin + 1) + nMin;
	int nSize = vecCharacter.size();
	string strResult = "";
	while(strResult.length() < (unsigned int)nLength){
		char sz[2] = {};
		sz[0] = vecCharacter.at(rand() % nSize);
		strResult = strResult.append(sz);
	}
	return strResult;
}

string CStringManager::ReplaceAll(const string& old_value,const string& new_value){
	while(true){
		string::size_type pos(0);
		if((pos = strInside.find(old_value)) != string::npos) strInside.replace(pos,old_value.length(),new_value);
		else break;
	}
	return strInside;
}

string CStringManager::ReplaceEvery(const string& old_value,const string& new_value){
	for(string::size_type pos(0);pos != string::npos;pos += new_value.length()){
		if((pos = strInside.find(old_value,pos)) != string::npos) strInside.replace(pos,old_value.length(),new_value);   
		else break;
	}
	return strInside;
}

void CStringManager::Format(LPCTSTR szFormat,...){
	va_list argptr = NULL;
	va_start(argptr,szFormat);
	int bufsize = _vscprintf(szFormat,argptr) + 2;
	TCHAR* buf = (TCHAR*)calloc(bufsize,sizeof(TCHAR));
	vsprintf_s(buf,bufsize,szFormat,argptr);
	this->strInside = buf;
	free(buf);
	va_end(argptr);
	return;
}

void CStringManager::Left(){
	return ;
}