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
};

//Cxml xml;
//xml["123"][0]["234"][1]["222"][0] = "aaa";//�޸ģ������
//xml["123"]["234"]["222"][1] = "bbb";//���
//xml["123"][0]["234"][1]["222"][0] = "delete";//ɾ��
//CString str = xml["123"][0]["234"][1]["222"][0].toValue();
//CString strAttri = xml["123"][0]["234"][1]["222"][0]("name");
//CString strNote = xml["123"][0]["234"][1]["222"][0].GetNote(0);//��ʾ��ȡ��ǰ�ڵ��²��׸�ע�ͣ�û�з���"-1"
//CString strNote = xml["123"][0]["234"][1]["222"][0].GetNote(-1);//��ʾ��ȡ��������ĵ�һ��ע�����ݣ�û�з���"-1"
//CString strNote = xml["123"][0]["234"][1]["222"][0].GetNote(1);//��ʾ��ȡ��������ĵ�һ��ע�����ݣ�û�з���"-1"
//CString strCDATA = xml["123"][0]["234"][1]["222"][0].GetCDATA(0);//��ע��һ��