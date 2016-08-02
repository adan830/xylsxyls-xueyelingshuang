#include <SDKDDKVer.h>
#include "Cjson.h"
#include <typeinfo>

#include "CFieldType.h"

map<CString,CString> Cjson::LoadJson(CString strJson){
	if(type == "class CjsonA") return pJsonA->LoadJson(strJson);
	else return map<CString,CString>();
}

vector<CString> Cjson::GetField(){
	if(type == "class CjsonA") return pJsonA->GetField();
	else return vector<CString>();
}

int Cjson::size(){
	//�Ȼ����ԭʼ��Cjson��ַ
	Cjson *TypeValueTemp = pJson->veCjson.at(0);
	int i = -1;
	while(i++ != pJson->vecField.size() - 1){
		//����û����������ֱ�ӷ���-1
		if(pJson->vecField.at(i).field == "" && pJson->vecField.at(i).num == -1) return -1;
		//������ֶ�
		if(pJson->vecField.at(i).field != "" && TypeValueTemp->type == "class CjsonA"){
			//���������ֶ��ٷ���
			auto it = ((CjsonA*)TypeValueTemp->pClass)->mapdata.begin();
			for(;it != ((CjsonA*)TypeValueTemp->pClass)->mapdata.end();it++){
				if(it->first == pJson->vecField.at(i).field){
					//pJsonֵ��[]����ʱ�Ѿ�����ȥ��
					TypeValueTemp =  &((CjsonA*)TypeValueTemp->pClass)->mapdata[pJson->vecField.at(i).field];
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

CString Cjson::toCString(CString NewLineSign,CString FormatSign,int FormatLength){
	if(type == "class CjsonA") return pJsonA->toCString(NewLineSign,FormatSign,FormatLength);
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
	pJsonA = new CjsonA;
	type = typeid(CjsonA).name();
	pClass = pJsonA;
	pJson = pJsonA;
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
	pJson = pNewClass;
}

Cjson::Cjson(const Cjson& x){
	if(type != "") AfxMessageBox("��������ʱԭtype��Ϊ�գ�type=" + type);
	type = x.type;

	this->strValueError.dValue = x.strValueError.dValue;
	this->strValueError.nValue = x.strValueError.nValue;
	this->strValueError.strValue = x.strValueError.strValue;
	this->strValueError.type = x.strValueError.type;

	if(type == ""){
		pClass = x.pClass;
	}
	if(type == "class CstrValue"){
		//pClass������newһ��
		CstrValue *pNewClass = new CstrValue;
		//vecp.push_back(pNewClass);
		*pNewClass = *((CstrValue *)(x.pClass));
		pClass = pNewClass;
	}
	else if(type == "class CszValue"){
		//pClass������newһ��
		CszValue *pNewClass = new CszValue();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CszValue *)(x.pClass));
		pClass = pNewClass;
	}
	else if(type == "class CjsonA"){
		//pClass������newһ��
		CjsonA *pNewClass = new CjsonA();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CjsonA *)(x.pClass));
		pClass = pNewClass;
	}
	else{
		AfxMessageBox("�������촫�����ͳ�������Ϊ��" + type);
	}
}

Cjson& Cjson::operator = (const Cjson& x){
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
		AfxMessageBox("���ص�����ԭ���ͳ���type=" + type);
	}
	type = x.type;

	this->strValueError.dValue = x.strValueError.dValue;
	this->strValueError.nValue = x.strValueError.nValue;
	this->strValueError.strValue = x.strValueError.strValue;
	this->strValueError.type = x.strValueError.type;

	if(type == ""){
		pClass = x.pClass;
	}
	else if(type == "class CstrValue"){
		//pClass������newһ��
		CstrValue *pNewClass = new CstrValue;
		//vecp.push_back(pNewClass);
		*pNewClass = *((CstrValue *)(x.pClass));
		pClass = pNewClass;
	}
	else if(type == "class CszValue"){
		//pClass������newһ��
		CszValue *pNewClass = new CszValue();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CszValue *)(x.pClass));
		pClass = pNewClass;
	}
	else if(type == "class CjsonA"){
		//pClass������newһ��
		CjsonA *pNewClass = new CjsonA();
		//vecp.push_back(pNewClass);
		*pNewClass = *((CjsonA *)(x.pClass));
		pClass = pNewClass;
	}
	else{
		AfxMessageBox("�������صȺŴ������ͳ�������Ϊ��" + type);
	}
	return *this;
}

Cjson& Cjson::operator[] (CString field){
	//���۵�ǰ��ʲô���Ͷ��Ȱ��ֶδ��ȥ����Ϊ���ʱ��֮ǰ��������û�������
	pJson->vecField.push_back(CFieldType(field,-1));
	//�ѱ���ĵ�ַ����pvec������ȥ���������ȡ֮ǰ�ĵ�ַ�����vector
	pJson->veCjson.push_back(this);

	if(type == "class CstrValue"){
		
	}
	else if(type == "class CszValue"){
		
	}
	else if(type == "class CjsonA"){
		//���������ֶ��ٷ���
		auto it = ((CjsonA*)pClass)->mapdata.begin();
		for(;it != ((CjsonA*)pClass)->mapdata.end();it++){
			if(it->first == field){
				//����֮ǰ�Ȱ�pJson��ֵ����ȥ����Ϊ������ֲ����ڵ������return *this�ܱ�֤pJson�϶���ֵ
				((CjsonA*)pClass)->mapdata[field].pJson = this->pJson;
				return ((CjsonA*)pClass)->mapdata[field];
			}
		}
	}
	else{
		AfxMessageBox("����[field]ʱ�������ͳ�������Ϊ��" + type);
	}
	return *this;
}

Cjson& Cjson::operator[] (int num){
	//������ʲô�����Ȱ����ִ��ȥ����Ϊ�ڴ��ʱ�������������Ͷ���CjsonA
	pJson->vecField.push_back(CFieldType("",num));
	//�ѱ���ĵ�ַ����pvec������ȥ���������ȡ֮ǰ�ĵ�ַ�����vector
	pJson->veCjson.push_back(this);

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
		AfxMessageBox("����[num]ʱ�������ͳ�������Ϊ��" + type);
	}
	return *this;
}

void Cjson::TypeEqual(CString strTemp){
	//�Ѵ�������fieldѭ���鿴����������޸ģ����򴴽�
	int level = -1;
	Cjson *pTypeValueTemp = pJson->veCjson.at(0);
	int i = -1;
	while(i++ != pJson->vecField.size() - 1){
		//��ʾ��ǰ����
		level++;
		//���field�ǿղ�������С��0˵���û����
		if(pJson->vecField.at(i).field == "" && pJson->vecField.at(i).num < 0){
			//������β
			goto rem;
		}
		//���field���ǿ�˵���˴����ֶ�
		if(pJson->vecField.at(i).field != ""){
			//�����ǰ�������һ����˵������Ӧ�ô����򸲸��ֶ�
			if(i == pJson->vecField.size() - 1){
				//���������"\"delete\""��ѵ�ǰ�ֶ�ɾ��
				if(strTemp == "\"delete\""){
					auto it = pTypeValueTemp->toJson().mapdata.begin();
					for(;it!=pTypeValueTemp->toJson().mapdata.end();it++){
						if(it->first == pJson->vecField.at(i).field){
							//���ͷ�֮��pJsonֵ�ᶪʧ����Ϊ�ͷŵ��Ǳ���Cjson������pJson�ᱻ���ã�������ȡ����
							CjsonA *pJsonTemp = pJson;
							pTypeValueTemp->toJson().mapdata.erase(it);
							//����ʹ��pJsonTemp�����
							pJsonTemp->vecField.clear();
							pJsonTemp->veCjson.clear();
							return;
						}
					}
				}
				else{
					//�˻���һ����ӻ򸲸��ֶ�
					pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field] = (CstrValue)strTemp;
				}
				break;
			}
			//�����ǰ���������json˵���û��ı��˵�ǰ������ʣ��Ҳ��������һ�㣬��Ϊ�����������������ѭ����
			if(pTypeValueTemp->type != "class CjsonA"){
				//�����һ����field˵����Ҫ����һ��json���Ա�����ʹ��
				if(pJson->vecField.at(i + 1).field != ""){
					//���¸���һ�㸳ֵ�µĿ����飬�Ա�����ʹ��
					pJson->veCjson.at(level - 1)->toJson().mapdata[pJson->vecField.at(i - 1).field] = CjsonA();
				}
				//�����һ��������˵����Ҫ����һ�����飬�Ա�����ʹ��
				else{
					pJson->veCjson.at(level - 1)->toJson().mapdata[pJson->vecField.at(i - 1).field] = CszValue();
				}
			}
			//�����ǰ�����ҵ�
			auto it = pTypeValueTemp->toJson().mapdata.begin();
			for(;it != pTypeValueTemp->toJson().mapdata.end();it++){
				//������ҵ���ֱ����������Ϊֻ��ȡ��һ��ָ�����Դ˴�����Ҫ����
				if(it->first == pJson->vecField.at(i).field) break;
			}
			if(it == pTypeValueTemp->toJson().mapdata.end()){
				//�����һ����field˵����Ҫ����һ��json
				if(pJson->vecField.at(i + 1).field != ""){
					pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field] = CjsonA();
				}
				//�����һ��������˵����Ҫ����һ������
				else{
					pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field] = CszValue();
				}
			}
			//���ҵ�����һ��Cjson����ָ��
			pTypeValueTemp = &(pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field]);
		}
		//����������
		else{
			//�����ǰ������������������ȴ�������
			if(pTypeValueTemp->type != "class CszValue"){
				//map�ڸ����ݵ�ʱ�����ִ�����������������Բ��ùܽڵ��ڴ�й©
				//���¸���һ�㸳ֵ�µĿ����飬�Ա�����ʹ��
				pJson->veCjson.at(level - 1)->toJson().mapdata[pJson->vecField.at(i - 1).field] = CszValue();
			}
			//���vec�е����ֱ�����ʵ�ʴ�С����׷����ĩβ
			if(pJson->vecField.at(i).num >= (int)pTypeValueTemp->tosz().vecszValue.size()){
				//������������һ����׷��һ���ֶ�
				if(i == pJson->vecField.size() - 1){
					//�����"\"delete\""
					if(strTemp == "\"delete\""){
						pTypeValueTemp->tosz().vecszValue.pop_back();
					}
					//�����"\"insert\""
					else if(strTemp == "\"insert\""){
						pTypeValueTemp->tosz().vecszValue.push_back(CstrValue(strTemp));
					}
					else{
						pTypeValueTemp->tosz().vecszValue.push_back(CstrValue(strTemp));
					}
					break;
				}
				//�����һ����field��׷��һ��json
				else if(pJson->vecField.at(i + 1).field != ""){
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
				if(i == pJson->vecField.size() - 1){
					//�����"\"delete\""
					if(strTemp == "\"delete\""){
						pTypeValueTemp->tosz().vecszValue.erase(pTypeValueTemp->tosz().vecszValue.begin() + pJson->vecField.at(i).num);
					}
					//�����"\"insert\""
					else if(strTemp == "\"insert\""){
						pTypeValueTemp->tosz().vecszValue.insert(pTypeValueTemp->tosz().vecszValue.begin() + pJson->vecField.at(i).num,CstrValue(strTemp));
					}
					else{
						pTypeValueTemp->tosz().vecszValue.at(pJson->vecField.at(i).num) = (CstrValue(strTemp));
					}
					break;
				}
				//�����һ����field�򸲸�һ����json
				else if(pJson->vecField.at(i + 1).field != ""){
					pTypeValueTemp->tosz().vecszValue.at(pJson->vecField.at(i).num) = CjsonA();
				}
				//�����һ��������˵���û������Ϊ�������ǲ�����ֱ����������
				else{
					goto rem;
				}
				//����һ��ָ��
				pTypeValueTemp = &(pTypeValueTemp->tosz().vecszValue.at(pJson->vecField.at(i).num));
			}
		}
	}

	rem:
	//ʹ�ù�һ�ξ����
	pJson->vecField.clear();
	pJson->veCjson.clear();
	return;
}

Cjson& Cjson::operator = (int nNum){
	CString strTemp = "";
	strTemp.Format("%d",nNum);

	TypeEqual(strTemp);
	
	return *this;
}

Cjson& Cjson::operator = (double dNum){
	CString strTemp = "";
	strTemp.Format("%lf",dNum);

	TypeEqual(strTemp);

	return *this;
}

Cjson& Cjson::operator = (CString str){
	CString strTemp = "";
	strTemp.Format("\"%s\"",str);

	TypeEqual(strTemp);
	
	return *this;
}

CstrValue& Cjson::toValue(){
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

Cjson::~Cjson(){
	if(type == ""){
		if(pClass != NULL){
			AfxMessageBox("����");
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
		AfxMessageBox("�ͷ����ͳ�������Ϊ��" + type);
	}
}