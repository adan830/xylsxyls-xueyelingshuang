#include "SpeakClass.h"
#include <typeinfo>

void SpeakClass::ReleaseClass(){
	stdmutex->lock();
	for (auto itlistRoom = listRoom.begin(); itlistRoom != listRoom.end();){
		string className = (*itlistRoom)->FindName(sonThis);
		//?����Ҳ����Լ�������˵���Ѿ��Ƴ��򷵻ؿ�
		if (className == "-1"){
			printf("�����Ѿ����Ƴ�");
			continue;
		}
		//?�����ҵ����Ƴ��������Ƴ���ָ��
		else{
			void* pClass = (*itlistRoom)->FindClass(className);
			if (pClass == NULL){
				printf("�����Ѿ����Ƴ�");
				continue;
			}
			//?�Ѿ��ҵ�����ȥ�����ü������ٷ���������ȥ���Լ�
			Room* room = *itlistRoom;
			auto itTemp = itlistRoom;
			itlistRoom++;
			RemoveRoom(*itTemp);
			room->FindClassAndErase(className);
			continue;
		}
		itlistRoom++;
	}
	stdmutex->unlock();
	//?ɾ���ڴ棬����ʱ��typeid���������this������ָ��
	delete this;
	return;
}

void SpeakClass::AddRoom(Room* room){
	listRoom.push_back(room);
}

void SpeakClass::RemoveRoom(Room* room){
	for (auto itlistRoom = listRoom.begin(); itlistRoom != listRoom.end(); itlistRoom++){
		if (*itlistRoom == room){
			listRoom.erase(itlistRoom);
			break;
		}
	}
}

Room::~Room(){
	if (vecClass.size() != 0) printf("�������г�Աδ�˳��������ڴ�й©");
}

void Room::AddClass(void* pClass,const string& className){
	vecClass.push_back(Class(pClass, className));
}

string Room::FindName(void* pClass)const{
	for (auto itvecClass = vecClass.begin(); itvecClass != vecClass.end(); itvecClass++){
		if (itvecClass->pClass == pClass){
			return itvecClass->name;
		}
	}
	return "-1";
}

void* Room::FindClass(const string& name)const{
	for (auto itvecClass = vecClass.begin(); itvecClass != vecClass.end(); itvecClass++){
		if (itvecClass->name == name){
			return itvecClass->pClass;
		}
	}
	return NULL;
}

void* Room::FindClassAndErase(const string& name){
	for (auto itvecClass = vecClass.begin(); itvecClass != vecClass.end(); itvecClass++){
		if (itvecClass->name == name){
			void* result = itvecClass->pClass;
			vecClass.erase(itvecClass);
			return result;
		}
	}
	return NULL;
}

int main(){ return 0; }