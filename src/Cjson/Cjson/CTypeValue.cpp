#include <SDKDDKVer.h>
#include "CTypeValue.h"
#include <typeinfo>

#include "CFieldType.h"

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

CTypeValue::CTypeValue(){
	type = "";
	pClass = NULL;
	pJson = NULL;
	this->strValueError.dValue = -1;
	this->strValueError.nValue = -1;
	this->strValueError.strValue = "-1";
	this->strValueError.type = -1;
}

CTypeValue::CTypeValue(const CstrValue& Class){
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

CTypeValue::CTypeValue(const CszValue& Class){
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
CTypeValue::CTypeValue(const Cjson& Class){
	type = typeid(Class).name();
	Cjson *pNewClass = new Cjson;
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

CTypeValue::CTypeValue(const CTypeValue& x){
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
	else if(type == "class Cjson"){
		//pClass������newһ��
		Cjson *pNewClass = new Cjson();
		//vecp.push_back(pNewClass);
		*pNewClass = *((Cjson *)(x.pClass));
		pClass = pNewClass;
	}
	else{
		AfxMessageBox("�������촫�����ͳ�������Ϊ��" + type);
	}
}

CTypeValue& CTypeValue::operator = (const CTypeValue& x){
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
	else if(type == "class Cjson"){
		//pClass������newһ��
		Cjson *pNewClass = new Cjson();
		//vecp.push_back(pNewClass);
		*pNewClass = *((Cjson *)(x.pClass));
		pClass = pNewClass;
	}
	else{
		AfxMessageBox("�������صȺŴ������ͳ�������Ϊ��" + type);
	}
	return *this;
}

CTypeValue& CTypeValue::operator[] (CString field){
	//���۵�ǰ��ʲô���Ͷ��Ȱ��ֶδ��ȥ����Ϊ���ʱ��֮ǰ��������û�������
	pJson->vecField.push_back(CFieldType(field,-1));
	//�ѱ���ĵ�ַ����pvec������ȥ���������ȡ֮ǰ�ĵ�ַ�����vector
	pJson->vecTypeValue.push_back(this);

	if(type == "class CstrValue"){
		
	}
	else if(type == "class CszValue"){
		
	}
	else if(type == "class Cjson"){
		//���������ֶ��ٷ���
		auto it = ((Cjson*)pClass)->mapdata.begin();
		for(;it != ((Cjson*)pClass)->mapdata.end();it++){
			if(it->first == field){
				//����֮ǰ�Ȱ�pJson��ֵ����ȥ����Ϊ������ֲ����ڵ������return *this�ܱ�֤pJson�϶���ֵ
				((Cjson*)pClass)->mapdata[field].pJson = this->pJson;
				return ((Cjson*)pClass)->mapdata[field];
			}
		}
	}
	else{
		AfxMessageBox("����[field]ʱ�������ͳ�������Ϊ��" + type);
	}
	return *this;
}

CTypeValue& CTypeValue::operator[] (int num){
	//������ʲô�����Ȱ����ִ��ȥ����Ϊ�ڴ��ʱ�������������Ͷ���Cjson
	pJson->vecField.push_back(CFieldType("",num));
	//�ѱ���ĵ�ַ����pvec������ȥ���������ȡ֮ǰ�ĵ�ַ�����vector
	pJson->vecTypeValue.push_back(this);

	if(type == "class CstrValue"){
		
	}
	else if(type == "class CszValue"){
		//�������������ô���ٷ���
		if(((CszValue*)pClass)->vecszValue.size() > (unsigned int)num){
			((CszValue*)pClass)->vecszValue.at(num).pJson = this->pJson;
			return ((CszValue*)pClass)->vecszValue.at(num);
		}
	}
	else if(type == "class Cjson"){
		
	}
	else{
		AfxMessageBox("����[num]ʱ�������ͳ�������Ϊ��" + type);
	}
	return *this;
}

void CTypeValue::TypeEqual(CString strTemp){
	//�Ѵ�������fieldѭ���鿴����������޸ģ����򴴽�
	int level = -1;
	CTypeValue *pTypeValueTemp = pJson->vecTypeValue.at(0);
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
				//�˻���һ����ӻ򸲸��ֶ�
				pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field] = (CstrValue)strTemp;
				break;
			}
			//�����ǰ���������json˵���û��ı��˵�ǰ������ʣ��Ҳ��������һ�㣬��Ϊ�����������������ѭ����
			if(pTypeValueTemp->type != "class Cjson"){
				//�����һ����field˵����Ҫ����һ��json���Ա�����ʹ��
				if(pJson->vecField.at(i + 1).field != ""){
					//���¸���һ�㸳ֵ�µĿ����飬�Ա�����ʹ��
					pJson->vecTypeValue.at(level - 1)->toJson().mapdata[pJson->vecField.at(i - 1).field] = Cjson();
				}
				//�����һ��������˵����Ҫ����һ�����飬�Ա�����ʹ��
				else{
					pJson->vecTypeValue.at(level - 1)->toJson().mapdata[pJson->vecField.at(i - 1).field] = CszValue();
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
					pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field] = Cjson();
				}
				//�����һ��������˵����Ҫ����һ������
				else{
					pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field] = CszValue();
				}
			}
			//���ҵ�����һ��CTypeValue����ָ��
			pTypeValueTemp = &(pTypeValueTemp->toJson().mapdata[pJson->vecField.at(i).field]);
		}
		//����������
		else{
			//�����ǰ������������������ȴ�������
			if(pTypeValueTemp->type != "class CszValue"){
				//map�ڸ����ݵ�ʱ�����ִ�����������������Բ��ùܽڵ��ڴ�й©
				//���¸���һ�㸳ֵ�µĿ����飬�Ա�����ʹ��
				pJson->vecTypeValue.at(level - 1)->toJson().mapdata[pJson->vecField.at(i - 1).field] = CszValue();
			}
			//���vec�е����ֱ�����ʵ�ʴ�С����׷����ĩβ
			if(pJson->vecField.at(i).num >= (int)pTypeValueTemp->tosz().vecszValue.size()){
				//������������һ����׷��һ���ֶ�
				if(i == pJson->vecField.size() - 1){
					pTypeValueTemp->tosz().vecszValue.push_back(CstrValue(strTemp));
					break;
				}
				//�����һ����field��׷��һ��json
				else if(pJson->vecField.at(i + 1).field != ""){
					pTypeValueTemp->tosz().vecszValue.push_back(Cjson());
				}
				//�����һ����������׷��һ������
				else{
					pTypeValueTemp->tosz().vecszValue.push_back(CszValue());
				}
				//дsize - 1��ԭ���ǵ��û���������ֹ���ʱҲ�������һ��
				pTypeValueTemp = &(pTypeValueTemp->tosz().vecszValue.at(pTypeValueTemp->tosz().vecszValue.size() - 1));
			}
			//������򸲸�
			else{
				//������������һ���򸲸��ֶ�
				if(i == pJson->vecField.size() - 1){
					pTypeValueTemp->tosz().vecszValue.at(pJson->vecField.at(i).num) = (CstrValue(strTemp));
					break;
				}
				//�����һ����field�򸲸�һ����json
				else if(pJson->vecField.at(i + 1).field != ""){
					pTypeValueTemp->tosz().vecszValue.at(pJson->vecField.at(i).num) = Cjson();
				}
				//�����һ���������򸲸�һ��������
				else{
					pTypeValueTemp->tosz().vecszValue.at(pJson->vecField.at(i).num) = CszValue();
				}
				//����һ��ָ��
				pTypeValueTemp = &(pTypeValueTemp->tosz().vecszValue.at(pJson->vecField.at(i).num));
			}
		}
	}

	rem:
	//ʹ�ù�һ�ξ����
	pJson->vecField.clear();
	pJson->vecTypeValue.clear();
	return;
}

CTypeValue& CTypeValue::operator = (int nNum){
	CString strTemp = "";
	strTemp.Format("%d",nNum);

	TypeEqual(strTemp);
	
	return *this;
}

CTypeValue& CTypeValue::operator = (double dNum){
	CString strTemp = "";
	strTemp.Format("%lf",dNum);

	TypeEqual(strTemp);

	return *this;
}

CTypeValue& CTypeValue::operator = (CString str){
	CString strTemp = "";
	strTemp.Format("\"%s\"",str);

	TypeEqual(strTemp);
	
	return *this;
}

CstrValue& CTypeValue::toValue(){
	if(type == "class CstrValue"){
		return *((CstrValue *)pClass);
	}
	//���Ҫ���ʵ����Ͳ��Ǳ����������ֱ�ӷ��ش���
	return strValueError;
}

CszValue& CTypeValue::tosz(){
	if(type == "class CszValue"){
		return *((CszValue *)pClass);
	}
	//���Ҫ���ʵ����Ͳ��Ǳ����������ֱ�ӷ��ؿ�
	return szValueError;
}

Cjson& CTypeValue::toJson(){
	if(type == "class Cjson"){
		return *((Cjson *)pClass);
	}
	//���Ҫ���ʵ����Ͳ��Ǳ����������ֱ�ӷ��ؿ�
	return jsonError;
}

CTypeValue::~CTypeValue(){
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
	else if(type == "class Cjson"){
		//freevec(pClass);
		delete (Cjson *)pClass;
	}
	else{
		AfxMessageBox("�ͷ����ͳ�������Ϊ��" + type);
	}
}