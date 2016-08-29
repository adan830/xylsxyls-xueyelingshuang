#pragma once
#include "Cjson/CjsonAPI.h"
#include <afxwin.h>
#include "CAceHttpServerMacro.h"

//Ĭ�ϱ�ͷ��������Content-Type��Content-Length
class Cjson;
class CAceHttpServerAPI CHttpString{
public:
	CString str;

public:
	//"application/json;charset=UTF-8"
	//1��ʾjson��1��ʾANSI�ַ�����2��ʾUTF-8�ַ���
	void InitClient(CString strIP,int port,int DataStyle,int nCharset);
	//1��ʾ�ɹ�������200OK
	void InitServer(int flag,int DataStyle,int nCharset);
	//��ӱ�ͷ
	void AddMessage(CString strHead,CString strValue);
	//1��ʾpost����
	void ProtocolStyle(CString strProtocol,int flag);
	//��ȡURI
	CString GetProtocol();
	//��ȡ������
	CString GetStyle();
	//�������
	void SetData(CString strData);
	//��ӳ���
	void SetLength(int length);
	//��ȡ����
	Cjson GetJsonData();
	//��ȡ����
	CString GetContentType();
	//��ȡ����
	int GetContentLength();
	//��ȡ���ݣ�����ʵ�ʽ��ճ���
	CString GetData();
	//��ȡ�ַ���
	int GetCharset();
};