#pragma once
#include <map>
#include "boost/any.hpp"
#include <string>
#include <unordered_map>
#include <afxwin.h>
#include "CStorageMacro.h"

using namespace std;
using namespace boost;

class CStorageAPI CStorage{
public:
	CStorage();
	bool changeString;
	string strCurrentKey;
	unordered_map<string, any> mapData;
	bool changeInt;
	int nCurrentKey;
	unordered_map<int, any> mapDataInt;

	CStorage& operator[](int key);
	CStorage& operator[](CString key);
	CStorage operator=(any anyValue);

	template<typename T>
	T toValue(){
		if (changeString == true){
			changeString = false;
			auto it = mapData.find(strCurrentKey);
			any anyValue;
			CString strError;
			try{
				if (it != mapData.end()){
					anyValue = it->second;
					return any_cast<T>(anyValue);
				}
				strError.Format("keyֵ��%s��������", strCurrentKey.c_str());
				AfxMessageBox(strError);
				return T();
			}
			catch (boost::bad_any_cast &e){
				strError.Format("��������Ϊ:%s��\nboost���ͣ�%s", it->second.type().name(), e.what());
				AfxMessageBox(strError);
				return T();
			}
		}
		else if (changeInt == true){
			changeInt = false;
			auto it = mapDataInt.find(nCurrentKey);
			any anyValue;
			CString strError;
			try{
				if (it != mapDataInt.end()){
					anyValue = it->second;
					return any_cast<T>(anyValue);
				}
				strError.Format("keyֵ��%d��������", nCurrentKey);
				AfxMessageBox(strError);
				return T();
			}
			catch (boost::bad_any_cast &e){
				strError.Format("��������Ϊ:%s��\nboost���ͣ�%s", it->second.type().name(), e.what());
				AfxMessageBox(strError);
				return T();
			}
		}
		else return T();
	}
};