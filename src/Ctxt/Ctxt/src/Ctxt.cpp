#include <SDKDDKVer.h>
#include "Ctxt.h"
#include <string>
#include <fstream>
using namespace std;

vector<string> split(string src,string separate_character){
	vector<string> strs;

	int separate_characterLen = separate_character.size();//�ָ��ַ����ĳ���,�����Ϳ���֧���硰,,�����ַ����ķָ���
	int lastPosition = 0,index = -1;
	while (-1 != (index = src.find(separate_character,lastPosition))){
		strs.push_back(src.substr(lastPosition,index - lastPosition));   
		lastPosition = index + separate_characterLen;   
	}
	string lastString = src.substr(lastPosition);//��ȡ���һ���ָ����������   
	//if (!lastString.empty()) //������һ���ָ����������ݾ����
	strs.push_back(lastString);
	return strs;
}

void Ctxt::LoadTxt(CString strPath,BOOL flag,CString strSplit){
	ifstream myfile(strPath);
	string strLine = "";
	int iLine = -1;
	while(getline(myfile,strLine) != 0){
		iLine++;
		//ת����CString���崦��ÿһ��
		CString cstrLine = strLine.c_str();
		if(flag == 1){
			vector<string> vecPart = split(strSplit.GetBuffer(),","); strSplit.ReleaseBuffer();
			int iPart1 = -1;
			int size = vecPart.size();
			vector<CString> vecLine1;
			//�ֳ��õ���һ�Խ�ȡ�㣬��0���͵�2�������׺�β
			while(iPart1++ != size - 1){
				vector<string> vecPoint = split(vecPart.at(iPart1).c_str(),"-");
				if(vecPoint.size() >= 2){
					int begin = atoi(vecPoint.at(0).c_str());
					int end   = atoi(vecPoint.at(1).c_str());
					vecLine1.push_back(cstrLine.Mid(begin,end - begin));
				}
				//����Ǵ����˿��ַ����Ͱ�һ�в���
				else{
					vecLine1.push_back(cstrLine);
				}
			}
			vectxt.push_back(vecLine1);
		}
		if(flag == 2){
			vector<string> vecPart = split(strLine,strSplit.GetBuffer()); strSplit.ReleaseBuffer();
			int sizePart = vecPart.size();
			vector<CString> vecLine2;
			int iPart2 = -1;
			while(iPart2++ != sizePart - 1){
				vecLine2.push_back(vecPart.at(iPart2).c_str());
			}
			vectxt.push_back(vecLine2);
		}
	}
	return;
}