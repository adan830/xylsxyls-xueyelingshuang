#pragma once
#include "CHttpString.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Connector.h"
#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"
#include <afxmt.h>
#include "CDeleteMapWatch.h"
#include <map>
using namespace std;
#include "CAceHttpClientMacro.h"
#include "Cjson/CjsonAPI.h"

#ifdef _DEBUG
#pragma comment(lib,"ACEd.lib")
#else
#pragma comment(lib,"ACE.lib")
#endif

class CAceHttpClientAPI CAceHttpClient{
public:
	ACE_SOCK_Connector* pconnector;
	ACE_SOCK_Stream* ppeer;
	ACE_INET_Addr* paddr;
	ACE_Time_Value* ptimeout;
	CMutex mutex;
	CMutex mutexDeleteMap;
	int CheckKeyClient;
	map<int,Cjson> mapCheck;
	CString strIP;
	int port;
	int RecvMaxLength;
	int ReconnectTime;
	int DataStyle;
	int ifPeerExist;
	CDeleteMapWatch Watch;
	int nCharset;

public:
	~CAceHttpClient();

public:
	//1��ʾʹ��json��1��ʾʹ��ANSI
	void init(CString strIP,int port,int ConnectWaitTime,int RecvMaxLength,int DataStyle = 1,int nCharset = 1);
	//����json����nDeleteTimeΪɾ��map��ͨ·ʱ�䣬���д0�Ļ����ʾ��һ���յ�����ɾһ��������ͬʱ���ڶ���ͨ·
	int SendJsonReq(Cjson jsonReq,CString strProtocol,Cjson jsonCheckPackage = Cjson(),int nDeleteTime = 10,int sendTimes = 3);
	//���շ���json
	virtual void ReceiveRspJson(Cjson jsonRsp,CString strProtocol,Cjson jsonCheckPackage,CHttpString str) = 0;
	//ɾ��map
	void DeleteMap(int CheckKeyClient);
};