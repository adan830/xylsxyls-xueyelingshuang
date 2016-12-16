#pragma once
#include <afxwin.h>
#include <list>
#include <map>
using namespace std;
#include "CNoteData.h"

class Cxml{
public:
	enum{
		NOTE,
		CDATA,
		NULLVALUE,
		XML
	};
public:
	double version;
	CString charset;
	CString standalone;
	//���ע��
	list<CNoteData> listNote;
	//���CDATA
	list<CNoteData> listCDATA;
	//��ŵ����ڵ�
	CString strOneXmlName;
	CString strOneXmlValue;
	//��Žڵ�����
	map<CString,CString> mapAttri;
	list<Cxml> listXml;

	//�ϲ�ָ��
	//Cxml* pPreXml;

	//����
	map<CString,CString> mapError;

	Cxml();
	map<CString,CString> Load(CString strXml);
	//����Լ�д��Ҫinit��1.0����UTF-8��GBK����YES
	void init(double version,CString charset,CString standalone);
	//�����ļ�ͷ
	void LoadHead(CString* strXml);
	//��ȡһ��ģ��
	bool GetOneModule(CString* pstrXml,int* flag,CString* strXmlName,CString* strXmlAttri,CString* strXmlText);
	//����һ��ģ��
	void LoadOneModule(int flag,CString strXmlName,CString strXmlAttri,CString strXmlText);
	//�ϲ�����map
	void AddErrorMap(map<CString,CString> mapChildError);
	//�������Լ�
	map<CString,CString> LoadAttri(CString strXmlAttri);

	//ת�����ַ���
	CString toCString(CString NewLineSign = "\r\n",CString FormatSign = "\t",int FormatLength = 0);
	CString AttriToCString(map<CString,CString> mapAttri);
	//���һ����xml����nInsert���ȥ
	void AddXml(CString* strXmlResult,int* nInsert,CString NewLineSign,CString FormatSign,int FormatLength);

	//һ��ʼ��Ϊ�ɷ��ʣ������ʴ�������������Ϊ0���ڽ���toValue��=֮�������Ϊ1
	bool bVisit;
	list<int> listVisit;
	list<CString> listCStringStorage;
	list<int> listintStorage;

	//��ɾ�Ĳ�
	Cxml& operator[](CString strNode);//1
	Cxml& operator()(int n);//2
	Cxml& operator()(CString strAttriName);//3
	Cxml& operator()(CString strAttriName,CString strAttriValue);//4
	Cxml& operator()(CString strNOTECDATA,int nFlag);//5
	Cxml operator=(CString strValue);
	Cxml operator=(int nValue);
	Cxml operator=(double dValue);
	CString toValue();
	Cxml* FindPrepXmlFromXml(Cxml* pxml,list<Cxml>* plistXml);
	Cxml* FindPrepXml(list<Cxml>* plistXml);
	Cxml* FindPrepXmlFromXml(Cxml* pxml,Cxml* pFindXml);
	Cxml* FindPrepXml(Cxml* pFindXml);
	

};

//С���ű�ʾ���嶨λ�����綨λ���ڼ�������λ���ԣ���λע��CDATA
//�����Ŷ�λ�ڵ�
//toValueȡ���ݣ���дtoValueֱ�Ӹ�ֵ���ݣ���ֵʧ�ܲ�Ӱ��ԭ�ļ�
//���Σ�С�����ַ�������ת�����ַ���¼�룬����ȡ��ʱһ��ȡ���ַ���
//�����λ����ʧ�����޸ģ������λ�ĸ����������������һ������������˸������޸�
//����¼����¼�뵽���һ�����������������ʧ��
//��·���ڲ�ֱ��д�����ڵ�����Ϊ������Ӷ������޸ģ����Զ�λʱ��֧��ֱ���޸�
//���ʱ·���г����Ҳ��������Ե���ֱ�Ӱ�����������������Ǹ�����ֱ�Ӷ�λ�����������������Զ�λ
//Cxml xml;
//xml["123"](0)["234"](1)["222"](0) = "aaa";//�޸ģ������
//xml["123"]["234"]["222"](1) = "bbb";//���
//xml["123"](0)["234"](1)["222"](0) = "delete";//ɾ��
//CString str = xml["123"](0)["234"](1)["222"](0).toValue();
//CString str = xml["123"](0)["234"](1)["222"](0)("name","aa").toValue();
//CString strAttri = xml["123"](0)["234"](1)["222"](0)("name").toValue();
//xml["123"](0)["234"](1)["222"](0)("name","3") = 5;
//CString strNote = xml["123"](0)["234"](1)["222"](0)("NOTE",0).toValue();//��ʾ��ȡ��ǰ�ڵ��²��׸�ע�ͣ�û�з���"-1"
//CString strNote = xml["123"](0)["234"](1)["222"](0)("NOTE",-1).toValue();//��ʾ��ȡ��������ĵ�һ��ע�����ݣ�û�з���"-1"
//CString strNote = xml["123"](0)["234"](1)["222"](0)("NOTE",1).toValue();//��ʾ��ȡ��������ĵ�һ��ע�����ݣ�û�з���"-1"
//CString strCDATA = xml["123"](0)["234"](1)["222"](0)("CDATA",0).toValue();//��ע��һ��
