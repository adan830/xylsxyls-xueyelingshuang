#pragma once
#include "Cjson/CjsonAPI.h"
#include <afxwin.h>

//Ĭ�ϱ�ͷ��������Content-Type��Content-Length
class Cjson;
class CHttpString{
public:
	CString str;

public:
	void init(CString strIP,int port,CString ContentType = "application/json;charset=UTF-8");
	//��ӱ�ͷ
	void AddMessage(CString strHead,CString strValue);
	//1��ʾpost����
	void ProtocolStyle(CString strProtocol,int flag);
	//�������
	void SetJson(Cjson json);
	//��ȡ����
	Cjson GetJsonData();
	//��ȡ����
	CString GetContentType();
	//��ȡ����
	int GetContentLength();
	//��ȡ���ݣ�����ʵ�ʽ��ճ���
	CString GetData();
};