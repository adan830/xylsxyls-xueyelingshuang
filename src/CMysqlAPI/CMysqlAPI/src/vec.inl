#pragma once
#include <vector>
using namespace std;

template<typename T>void FreeVec(vector<T> *pVec){
	unsigned int i = 0;
	//�������е�ÿ��ָ���ͷţ����Ȳ�Ϊ0��ɾ����һ��Ԫ��
	while(pVec->size() != 0){
		//��ɾ����Ӧ���ʱ������������������ж�Ӧ�ͷŸ�Ԫ�صĺ������������ﲻ��Ҫ�ٴ��ͷ���
		delete pVec->at(0);
		//�������ֻ����䣬Ӧ�÷����ڴ�й©������������û�У���������Ϊmysql�ײ�����ڴ����
		//VecErase(pVec,pVec->at(0));
	}
	return;
}

template<typename T>void VecErase(vector<T> *pVec,T p){
	vector<T>::iterator it = pVec->begin();
	for(it = pVec->begin();it <= pVec->end();it++){
		if(*it == p){
			pVec->erase(it);
			break;
		}
	}
}