#pragma once
#include <afxwin.h>
#include <list>
#include <map>
using namespace std;

class Cxml{
public:
	enum{
		NOTE,
		CDATA,
		NULLVALUE,
		XML
	};
public:
	map<CString,CString> Load(CString strXml);

	//���ע��
	list<CString> listNote;
	//���CDATA
	list<CString> listCDATA;
	//��ŵ����ڵ�
	CString strOneXmlName;
	CString strOneXmlValue;
	list<Cxml> listXml;

	//����
	map<CString,CString> mapError;
	//�ϲ�����map
	void AddErrorMap(map<CString,CString> mapChildError);

	
	//��ȡһ��ģ��
	bool GetOneModule(CString* pstrXml,CString* strXmlOneModule,int* flag);
	//����һ��ģ��
	void LoadOneModule(CString strXmlOneModule,int flag);
};

//Cxml xml;
//xml["123"](0)["234"](1)["222"](0) = "aaa";//�޸ģ������
//xml["123"](0)["234"](1)["222"](0)[1] = "bbb";//���
//xml["123"](0)["234"](1)["222"](0) = "delete";//ɾ��
//CString str = xml["123"](0)["234"](1)["222"](0).toValue();
//CString strAttri = xml["123"](0)["234"](1)["222"](0).GetAttri("name");
//CString strNote = xml["123"](0)["234"](1)["222"](0).GetNote(0);//��ʾ��ȡ��ǰ�ڵ��²�ע�ͣ�û�з��ؿ�
//CString strNote = xml["123"](0)["234"](1)["222"](0).GetNote(-1);//��ʾ��ȡ��������ĵ�һ��ע�����ݣ�û�з��ؿ�
//CString strCDATA = xml["123"](0)["234"](1)["222"](0).GetCDATA(0);//��ע��һ��