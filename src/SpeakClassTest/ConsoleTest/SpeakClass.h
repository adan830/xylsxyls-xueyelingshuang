#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <list>
using namespace std;

class Class{
public:
	Class(void* pClass, const string& type){
		this->pClass = pClass;
		this->name = type;
	}
	void* pClass;
	string name;
};

class Room{
public:
	~Room();
public:
	vector<Class> vecClass;

	//?���ܳ��ֿյ�ַ���������
	void AddClass(void* pClass, const string& className);
	string FindName(void* pClass)const;
	void* FindClass(const string& name)const;
	void* FindClassAndErase(const string& name);
};

class SpeakClass{
public:
	std::mutex* stdmutex;
	list<Room*> listRoom;
public:
	template<typename T>
	static T* CreateClass(Room* room, std::mutex* stdmutex, string className = ""){
		T* pClass = new T;
		pClass->stdmutex = stdmutex;
		if (className == "") className = typeid(T).name();
		bool ifAddSuccess = pClass->AddSpeakClass<T>(room, className, pClass);
		if (ifAddSuccess == true) return pClass;
		else{
			delete pClass;
			return false;
		}
	}

	template<typename T>
	void SendToOtherClass(Room* room, const int& dataType, void* data, string otherClassName = ""){
		//?���жϸ�ָ���Ƿ����
		stdmutex->lock();
		string name = room->FindName(this);
		if (name == "-1") goto RETURN;
		//?�ж������Ƿ�Ϊ��
		if (otherClassName == "") otherClassName = typeid(T).name();
		void* pClass = room->FindClass(otherClassName);
		if (pClass != NULL) ((T*)pClass)->ReceiveFromOtherClass(room, dataType, data, room->FindName(this));
		RETURN:
		stdmutex->unlock();
	}
	virtual void ReceiveFromOtherClass(Room* room, const int& dataType, void* data, const string& otherClassName) = 0;
	//?�����������������Ϊtypeid���㣬���������ַ���ַΪ�������ַ
	template<typename T>
	bool AddSpeakClass(Room* room, string className = "", void* pClass = NULL){
		//?�е�ַû���ֲ�����
		if (pClass != NULL && className == "") goto FALSE;
		//?û��ַû����
		else if (pClass == NULL && className == ""){
			pClass = this;
			className = typeid(*this).name();
		}
		//?û��ַ��������˵����ַΪ�������ַ
		else if (pClass == NULL && className != ""){
			pClass = this;
		}
		//?���ж��Ƿ�����
		stdmutex->lock();
		void* pClassTemp = room->FindClass(className);
		//?���������
		if (pClassTemp != NULL) goto FALSE;
		//?������˵������ȷ���������
		//?�����Ӹ�������ü��������ڷ������������
		((T*)pClass)->AddRoom(room);
		room->AddClass(pClass, className);
		goto TRUE;
		TRUE:
		stdmutex->unlock();
		return true;
		FALSE:
		stdmutex->unlock();
		return false;
	}
	//?�Ƴ�ʧ���򷵻ؿգ�˵����ǰ״̬���Ѿ�û�и�����
	template<typename T>
	void* RemoveClass(Room* room, string className = ""){
		//?���û��˵��Ҫ�Ƴ��Լ����ȸ���ָ���ҵ��Լ�������
		void* voidResult = NULL;
		stdmutex->lock();
		if (className == "") className = room->FindName(this);
		//?����Ҳ����Լ�������˵���Ѿ��Ƴ��򷵻ؿ�
		if (className == "-1") goto RETURN;
		//?�����ҵ����Ƴ��������Ƴ���ָ��
		else{
			void* pClass = room->FindClass(className);
			if (pClass == NULL) goto RETURN;
			//?�Ѿ��ҵ�����ȥ�����ü������ٷ���������ȥ���Լ�
			((T*)pClass)->RemoveRoom(room);
			voidResult = room->FindClassAndErase(className);
			goto RETURN;
		}
		RETURN:
		stdmutex->unlock();
		return voidResult;
	}

	//?Ĭ��ɾ���Լ�����ɾ��֮����Ȼ����ʹ�ø�ָ���������������
	void ReleaseClass();

	void AddRoom(Room* room);
	void RemoveRoom(Room* room);
};