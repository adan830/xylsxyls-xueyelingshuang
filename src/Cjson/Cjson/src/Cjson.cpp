#include "Cjson.h"
#include <typeinfo>
#include "CStringManager/CStringManagerAPI.h"
#include "CFieldType.h"

map<string,string> Cjson::LoadJson(string strJson){
	FreeCJson();
	//��ʼ��
	pJsonA = new CjsonA;
	type = typeid(CjsonA).name();
	pClass = pJsonA;
	pJson = pJsonA;
	return pJsonA->LoadJson(strJson);
}

vector<string> Cjson::GetField(){
	if(type == "class CjsonA") return pJsonA->GetField();
	else return vector<string>();
}

int Cjson::size(){
	//�Ȼ����ԭʼ��Cjson��ַ
	Cjson *TypeValueTemp = pJson->vecCjson.at(0);
	int i = -1;
	while(i++ != pJson->vecField.size() - 1){
		//����û����������ֱ�ӷ���-1
		if(pJson->vecField.at(i).field == "" && pJson->vecField.at(i).num == -1) return -1;
		//������ֶ�
		if(pJson->vecField.at(i).field != "" && TypeValueTemp->type == "class CjsonA"){
			//���������ֶ��ٷ���
			auto it = ((CjsonA*)TypeValueTemp->pClass)->mapdata.begin();
			for(;it != ((CjsonA*)TypeValueTemp->pClass)->mapdata.end();it++){
				if(it->first.c_str() == pJson->vecField.at(i).field){
					//pJsonֵ��[]����ʱ�Ѿ�����ȥ��
					TypeValueTemp =  &((CjsonA*)TypeValueTemp->pClass)->mapdata[(pJson->vecField.at(i).field)];
					goto rem;
				}
			}
			//���ѭ����Ȼ�˳����ʾû�ҵ�����-1
			return -1;
			rem:;
		}
		else if(pJson->vecField.at(i).num != -1 && TypeValueTemp->type == "class CszValue"){
			//�������������ô���ٷ���
			if(((CszValue*)TypeValueTemp->pClass)->vecszValue.size() > (unsigned int)pJson->vecField.at(i).num){
				//pJson�Ѿ���[]����ʱ����ȥ��
				TypeValueTemp = &((CszValue*)TypeValueTemp->pClass)->vecszValue.at(pJson->vecField.at(i).num);
			}
			else return -1;
		}
		else return -1;
	}
	if(type == "class CjsonA") return TypeValueTemp->toJson().size();
	else if(type == "class CszValue") return TypeValueTemp->tosz().size();
	else return -1;
}

string Cjson::tostring(string NewLineSign,string FormatSign,int FormatLength){
	//����Ǹ��յ�CTypeValue����ô��Ҫ�ȳ�ʼ�����ж�ʱ������pJson���жϣ���Ϊֻ��pJson��͸����
	if(pJson == NULL){
		//˵����δ��ʼ��
		LoadJson("{}");
	}
	if(type == "class CjsonA") return pJsonA->tostring(NewLineSign,FormatSign,FormatLength);
	else return "";
}

vector<void *> vecp;
void freevec(void* freep){
	auto it = vecp.begin();
	for(;it != vecp.end();it++){
		if(*it == freep){
			vecp.erase(it);
			break;
		}
	}
}

Cjson::Cjson(){
	pJsonA = NULL;
	type = "";
	pClass = NULL;
	pJson = NULL;
	this->strValueError.dValue = -1;
	this->strValueError.nValue = -1;
	this->strValueError.strValue = "-1";
	this->strValueError.type = -1;
}

Cjson::Cjson(const CstrValue& Class){
	type = typeid(Class).name();
	CstrValue *pNewClass = new CstrValue;
	//vecp.push_back(pNewClass);
	*pNewClass = Class;
	pClass = pNewClass;

	pJsonA = NULL;
	pJson = NULL;

	this->strValueError.dValue = -1;
	this->strValueError.nValue = -1;
	this->strValueError.strValue = "-1";
	this->strValueError.type = -1;
}

Cjson::Cjson(const CszValue& Class){
	type = typeid(Class).name();
	CszValue *pNewClass = new CszValue;
	//vecp.push_back(pNewClass);
	*pNewClass = Class;
	pClass = pNewClass;

	pJsonA = NULL;
	pJson = NULL;

	this->strValueError.dValue = -1;
	this->strValueError.nValue = -1;
	this->strValueError.strValue = "-1";
	this->strValueError.type = -1;
}
Cjson::Cjson(const CjsonA& Class){
	type = typeid(Class).name();
	CjsonA *pNewClass = new CjsonA;
	//vecp.push_back(pNewClass);
	*pNewClass = Class;
	pClass = pNewClass;

	this->strValueError.dValue = -1;
	this->strValueError.nValue = -1;
	this->strValueError.strValue = "-1";
	this->strValueError.type = -1;

	//pJson��ȡ�ֶ����ķ�ʽ��ʹ��ǳ����
	//pJson = pNewClass;
	//pJsonA = pNewClass;
	pJson = NULL;
	pJsonA = NULL;
}

Cjson::Cjson(const Cjson& x){
	if (type != ""){
		;//AfxMessageBox("��������ʱԭtype��Ϊ�գ�type=" + type);
	}
	type = x.type;

	this->strValueError.dValue = x.strValueError.dValue;
	this->strValueError.nValue = x.strValueError.nValue;
	this->strValueError.strValue = x.strValueError.strValue;
	this->strValueError.type = x.strValueError.type;
	//this->vecHwnd = x.vecHwnd;

	if(type == ""){
		pClass = x.pClass;
		//pJsonA�ǲ�͸���ģ����ڴ������壬����Ӧ�ø�ֵ��pJson��͸���ģ������ֵ�ᵼ�������pJson��ʧ
		pJsonA = x.pJsonA;
		//�ڹ��캯����ȫ��������
		pJson = x.pJson;
	}
	else if(type == "class CstrValue"){
		//pClass������newһ��
		CstrValue *pNewClass = new CstrValue;
		//vecp.push_back(pNewClass);
		*pNewClass = *((CstrValue *)(x.pClass));
		pClass = pNewClass;
		pJsonA = x.pJsonA;
		pJson = x.pJson;
	}
	else if(type == "class CszValue"){
		//pClass������newһ��
		CszValue *pNewClass = new CszValue();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CszValue *)(x.pClass));
		pClass = pNewClass;
		pJsonA = x.pJsonA;
		pJson = x.pJson;
	}
	else if(type == "class CjsonA"){
		//pClass������newһ��
		CjsonA *pNewClass = new CjsonA();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CjsonA *)(x.pClass));
		pClass = pNewClass;
		pJsonA = (CjsonA*)pClass;
		pJson = pJsonA;
	}
	else{
		;//AfxMessageBox("�������촫�����ͳ�������Ϊ��" + type);
	}

	strValueError = x.strValueError;
	szValueError = x.szValueError;
	jsonError = x.jsonError;
}

Cjson Cjson::operator = (const Cjson& x){
	if(type == ""){

	}
	else if(type == "class CstrValue"){
		delete (CstrValue *)pClass;
	}
	else if(type == "class CszValue"){
		delete (CszValue *)pClass;
	}
	else if(type == "class CjsonA"){
		delete (CjsonA *)pClass;
	}
	else{
		;//AfxMessageBox("���ص�����ԭ���ͳ���type=" + type);
	}
	type = x.type;

	this->strValueError.dValue = x.strValueError.dValue;
	this->strValueError.nValue = x.strValueError.nValue;
	this->strValueError.strValue = x.strValueError.strValue;
	this->strValueError.type = x.strValueError.type;
	//this->vecHwnd = x.vecHwnd;

	if(type == ""){
		pClass = x.pClass;
		pJsonA = x.pJsonA;
		//ֻ�ж����������ʱ��ſ��԰�pJson��ֵ�������������ֶ���pJsonA��pJson��Ϊ�յ����
		//��ֵpJson��������������һ������json����ӽڵ�ʱ��ֵ��һ���ǰ�CstrValue�����ഫ��һ����Cjson����
		if(x.pJsonA != NULL) pJson = x.pJson;
	}
	else if(type == "class CstrValue"){
		//pClass������newһ��
		CstrValue *pNewClass = new CstrValue;
		//vecp.push_back(pNewClass);
		*pNewClass = *((CstrValue *)(x.pClass));
		pClass = pNewClass;
		pJsonA = x.pJsonA;
		if(x.pJsonA != NULL) pJson = x.pJson;
	}
	else if(type == "class CszValue"){
		//pClass������newһ��
		CszValue *pNewClass = new CszValue();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CszValue *)(x.pClass));
		pClass = pNewClass;
		pJsonA = x.pJsonA;
		if(x.pJsonA != NULL) pJson = x.pJson;
	}
	else if(type == "class CjsonA"){
		//pClass������newһ��
		CjsonA *pNewClass = new CjsonA();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CjsonA *)(x.pClass));
		pClass = pNewClass;
		pJsonA = (CjsonA*)pClass;
		pJson = pJsonA;
	}
	else{
		;//AfxMessageBox("�������صȺŴ������ͳ�������Ϊ��" + type);
	}

	strValueError = x.strValueError;
	szValueError = x.szValueError;
	jsonError = x.jsonError;
	return *this;
}

Cjson& Cjson::operator[] (string field){
	//����Ǹ��յ�CTypeValue����ô��Ҫ�ȳ�ʼ�����ж�ʱ������pJson���жϣ���Ϊֻ��pJson��͸����
	if(pJson == NULL){
		//˵����δ��ʼ��
		LoadJson("{}");
	}
	//���۵�ǰ��ʲô���Ͷ��Ȱ��ֶδ��ȥ����Ϊ���ʱ��֮ǰ��������û�������
	pJson->vecField.push_back(CFieldType(field,-1));
	//�ѱ���ĵ�ַ����pvec������ȥ���������ȡ֮ǰ�ĵ�ַ�����vector
	pJson->vecCjson.push_back(this);
	

	if(type == "class CstrValue"){
		
	}
	else if(type == "class CszValue"){
		
	}
	else if(type == "class CjsonA"){
		//���������ֶ��ٷ���
		auto it = ((CjsonA*)pClass)->mapdata.begin();
		for(;it != ((CjsonA*)pClass)->mapdata.end();it++){
			if(it->first.c_str() == field){
				//����֮ǰ�Ȱ�pJson��ֵ����ȥ����Ϊ������ֲ����ڵ������return *this�ܱ�֤pJson�϶���ֵ
				((CjsonA*)pClass)->mapdata[field].pJson = this->pJson;
				return ((CjsonA*)pClass)->mapdata[field];
			}
		}
	}
	else{
		;//AfxMessageBox("����[field]ʱ�������ͳ�������Ϊ��" + type);
	}
	return *this;
}

Cjson& Cjson::operator[] (int num){
	//����Ǹ��յ�CTypeValue����ô��Ҫ�ȳ�ʼ�����ж�ʱ������pJson���жϣ���Ϊֻ��pJson��͸����
	if(pJson == NULL){
		//˵����δ��ʼ��
		LoadJson("{}");
	}
	//������ʲô�����Ȱ����ִ��ȥ����Ϊ�ڴ��ʱ�������������Ͷ���CjsonA
	pJson->vecField.push_back(CFieldType("",num));
	//�ѱ���ĵ�ַ����pvec������ȥ���������ȡ֮ǰ�ĵ�ַ�����vector
	pJson->vecCjson.push_back(this);

	if(type == "class CstrValue"){
		
	}
	else if(type == "class CszValue"){
		//�������������ô���ٷ���
		if(((CszValue*)pClass)->vecszValue.size() > (unsigned int)num){
			((CszValue*)pClass)->vecszValue.at(num).pJson = this->pJson;
			return ((CszValue*)pClass)->vecszValue.at(num);
		}
	}
	else if(type == "class CjsonA"){
		
	}
	else{
		;//AfxMessageBox("����[num]ʱ�������ͳ�������Ϊ��" + type);
	}
	return *this;
}

Cjson* Cjson::TypeEqual(string strTemp){
	//�Ѵ�������fieldѭ���鿴����������޸ģ����򴴽�
	int level = -1;
	Cjson* pTypeValueReturn = pJson->vecCjson.at(0);
	Cjson* pTypeValueTemp = pJson->vecCjson.at(0);
	int i = -1;
	while(i++ != pTypeValueReturn->pJson->vecField.size() - 1){
		//��ʾ��ǰ����
		level++;
		//���field�ǿղ�������С��0˵���û����
		if(pTypeValueReturn->pJson->vecField.at(i).field == "" && pTypeValueReturn->pJson->vecField.at(i).num < 0){
			//������β
			goto rem;
		}
		//���field���ǿ�˵���˴����ֶ�
		if(pTypeValueReturn->pJson->vecField.at(i).field != ""){
			//�����ǰ�������һ����˵������Ӧ�ô����򸲸��ֶ�
			if(i == pTypeValueReturn->pJson->vecField.size() - 1){
				//���������"\"delete\""��ѵ�ǰ�ֶ�ɾ��
				if(strTemp == "\"delete\""){
					auto it = pTypeValueTemp->toJson().mapdata.begin();
					for(;it!=pTypeValueTemp->toJson().mapdata.end();it++){
						if(it->first.c_str() == pTypeValueReturn->pJson->vecField.at(i).field){
							//���ͷ�֮��pJsonֵ�ᶪʧ����Ϊ�ͷŵ��Ǳ���Cjson������pJson�ᱻ���ã�������ȡ����
							//CjsonA *pJsonTemp = pJson;
							pTypeValueTemp->toJson().mapdata.erase(it);
							goto rem;
							//����ʹ��pJsonTemp�����
							//pJsonTemp->vecField.clear();
							//pJsonTemp->vecCjson.clear();
							//return pTypeValueReturn;
						}
					}
				}
				else{
					//��Ϊ���������һ���ʱ��ֻ����ͨ��json��map�ҵ�һ�������json������
					//����ҵ���һ�����鵫���û�ָ����ǰ��Ϊ�ֶεĻ�˵���û�Ҫ�������Ϊjson��Ӧ���ȵ���һ�㴴��һ��json��Ȼ���ٻ�ô�����map���и�ֵ
					if(pTypeValueTemp->type == "class CszValue"){
						//���¸���һ�㸳ֵ�µ�json���Ա�����ʹ��
						pTypeValueReturn->pJson->vecCjson.at(level - 1)->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i - 1).field)] = CjsonA();
						pTypeValueTemp = &(pTypeValueReturn->pJson->vecCjson.at(level - 1)->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i - 1).field)]);
					}
					//�˻���һ����ӻ򸲸��ֶ�
					pTypeValueTemp->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i).field)] = (Cjson)(CstrValue)strTemp;
				}
				break;
			}
			//�����ǰ���������json˵���û��ı��˵�ǰ������ʣ��Ҳ��������һ�㣬��Ϊ�����������������ѭ����
			if(pTypeValueTemp->type != "class CjsonA"){
				//�����һ����field˵����Ҫ����һ��json���Ա�����ʹ��
				if(pTypeValueReturn->pJson->vecField.at(i + 1).field != ""){
					//���¸���һ�㸳ֵ�µ�json���Ա�����ʹ��
					pTypeValueReturn->pJson->vecCjson.at(level - 1)->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i - 1).field)] = CjsonA();
				}
				//�����һ��������˵����Ҫ����һ�����飬�Ա�����ʹ��
				else{
					pTypeValueReturn->pJson->vecCjson.at(level - 1)->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i - 1).field)] = CszValue();
				}
			}
			//�����ǰ�����ҵ�
			auto it = pTypeValueTemp->toJson().mapdata.begin();
			for(;it != pTypeValueTemp->toJson().mapdata.end();it++){
				//������ҵ���ֱ����������Ϊֻ��ȡ��һ��ָ�����Դ˴�����Ҫ����
				if(it->first.c_str() == pTypeValueReturn->pJson->vecField.at(i).field) break;
			}
			if(it == pTypeValueTemp->toJson().mapdata.end()){
				//�����һ����field˵����Ҫ����һ��json
				if(pTypeValueReturn->pJson->vecField.at(i + 1).field != ""){
					pTypeValueTemp->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i).field)] = CjsonA();
				}
				//�����һ��������˵����Ҫ����һ������
				else{
					pTypeValueTemp->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i).field)] = CszValue();
				}
			}
			//���ҵ�����һ��Cjson����ָ��
			pTypeValueTemp = &(pTypeValueTemp->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i).field)]);
		}
		//����������
		else{
			//�����ǰ������������������ȴ�������
			if(pTypeValueTemp->type != "class CszValue"){
				//map�ڸ����ݵ�ʱ�����ִ�����������������Բ��ùܽڵ��ڴ�й©
				//���¸���һ�㸳ֵ�µĿ����飬�Ա�����ʹ��
				pTypeValueReturn->pJson->vecCjson.at(level - 1)->toJson().mapdata[(pTypeValueReturn->pJson->vecField.at(i - 1).field)] = CszValue();
			}
			//���vec�е����ֱ�����ʵ�ʴ�С����׷����ĩβ
			if(pTypeValueReturn->pJson->vecField.at(i).num >= (int)pTypeValueTemp->tosz().vecszValue.size()){
				//������������һ����׷��һ���ֶ�
				if(i == pTypeValueReturn->pJson->vecField.size() - 1){
					//�����"\"delete\""
					if(strTemp == "\"delete\""){
						if(pTypeValueTemp->tosz().vecszValue.size() >= 1) pTypeValueTemp->tosz().vecszValue.pop_back();
					}
					//�����"\"insert\""
					else if(strTemp == "\"insert\""){
						//���ﲻ����Ӱ�죬��Ϊ��������ֵ����ʱ�Ͳ���ȡ����һ�㣬��һ�㻹����pJsonֵ��
						pTypeValueTemp->tosz().vecszValue.push_back(CstrValue(strTemp));
					}
					else{
						pTypeValueTemp->tosz().vecszValue.push_back(CstrValue(strTemp));
					}
					break;
				}
				//�����һ����field��׷��һ��json
				else if(pTypeValueReturn->pJson->vecField.at(i + 1).field != ""){
					pTypeValueTemp->tosz().vecszValue.push_back(CjsonA());
				}
				//�����һ��������˵���û������Ϊ�������ǲ�����ֱ����������
				else{
					goto rem;
				}
				//дsize - 1��ԭ���ǵ��û���������ֹ���ʱҲ�������һ��
				pTypeValueTemp = &(pTypeValueTemp->tosz().vecszValue.at(pTypeValueTemp->tosz().vecszValue.size() - 1));
			}
			//������򸲸�
			else{
				//������������һ���򸲸��ֶ�
				if(i == pTypeValueReturn->pJson->vecField.size() - 1){
					//�����"\"delete\""
					if(strTemp == "\"delete\""){
						pTypeValueTemp->tosz().vecszValue.erase(pTypeValueTemp->tosz().vecszValue.begin() + pTypeValueReturn->pJson->vecField.at(i).num);
					}
					//�����"\"insert\""
					else if(strTemp == "\"insert\""){
						//��Ϊinsert�����Ķ������Ǳ�����ָ��CTypeValue�����Իᵼ��pJsonΪ��
						//CjsonA* pJsonTemp = pJson;
						Cjson temp = CstrValue(strTemp);
						auto num = pTypeValueTemp->tosz().vecszValue.begin() + pTypeValueReturn->pJson->vecField.at(i).num;
						pTypeValueTemp->tosz().vecszValue.insert(num,temp);
						//pJson = pJsonTemp;
					}
					else{
						Cjson temp = (CstrValue(strTemp));
						int num = pTypeValueReturn->pJson->vecField.at(i).num;
						pTypeValueTemp->tosz().vecszValue.at(num) = temp;
					}
					break;
				}
				//�����һ����field�򸲸�һ����json
				else if(pTypeValueReturn->pJson->vecField.at(i + 1).field != ""){
					pTypeValueTemp->tosz().vecszValue.at(pTypeValueReturn->pJson->vecField.at(i).num) = CjsonA();
				}
				//�����һ��������˵���û������Ϊ�������ǲ�����ֱ����������
				else{
					goto rem;
				}
				//����һ��ָ��
				pTypeValueTemp = &(pTypeValueTemp->tosz().vecszValue.at(pTypeValueReturn->pJson->vecField.at(i).num));
			}
		}
	}

	rem:
	//ʹ�ù�һ�ξ����
	pTypeValueReturn->pJson->vecField.clear();
	pTypeValueReturn->pJson->vecCjson.clear();
	return pTypeValueReturn;
}

Cjson Cjson::operator = (int nNum){
	string strTemp = "";
	CStringManager::Format(strTemp,"%d",nNum);

	return *(TypeEqual(strTemp));
}

Cjson Cjson::operator = (double dNum){
	string strTemp = "";
	CStringManager::Format(strTemp,"%lf", dNum);

	return *(TypeEqual(strTemp));
}

Cjson Cjson::operator = (string str){
	string strTemp = "";
	CStringManager::Format(strTemp,"\"%s\"", str);

	return *(TypeEqual(strTemp));
}

CstrValue& Cjson::toValue(){
	//ʹ�ù�һ�ξ���գ������Ϊ��˵�����û�ʹ��
	if(pJson != NULL) pJson->vecField.clear();
	if(pJson != NULL) pJson->vecCjson.clear();
	if(type == "class CstrValue"){
		return *((CstrValue *)pClass);
	}
	//���Ҫ���ʵ����Ͳ��Ǳ����������ֱ�ӷ��ش���
	return strValueError;
}

CszValue& Cjson::tosz(){
	if(type == "class CszValue"){
		return *((CszValue *)pClass);
	}
	//���Ҫ���ʵ����Ͳ��Ǳ����������ֱ�ӷ��ؿ�
	return szValueError;
}

CjsonA& Cjson::toJson(){
	if(type == "class CjsonA"){
		return *((CjsonA *)pClass);
	}
	//���Ҫ���ʵ����Ͳ��Ǳ����������ֱ�ӷ��ؿ�
	return jsonError;
}

/*
void Cjson::ClearHwnd(){
	vecHwnd.clear();
	return;
}

void Cjson::SaveHwnd(HWND hwnd){
	vecHwnd.push_back(hwnd);
	return;
}

HWND Cjson::GetHwnd(int num){
	if(vecHwnd.size() < (unsigned int)num) return 0;
	return vecHwnd.at(num - 1);
}
*/
void Cjson::FreeCJson(){
	if(type == ""){
		if(pClass != NULL){
			;//AfxMessageBox("����");
		}
	}
	else if(type == "class CstrValue"){
		//freevec(pClass);
		delete (CstrValue *)pClass;
	}
	else if(type == "class CszValue"){
		//freevec(pClass);
		delete (CszValue *)pClass;
	}
	else if(type == "class CjsonA"){
		//freevec(pClass);
		delete (CjsonA *)pClass;
	}
	else{
		;//AfxMessageBox("�ͷ����ͳ�������Ϊ��" + type);
	}
}

Cjson::~Cjson(){
	FreeCJson();
}