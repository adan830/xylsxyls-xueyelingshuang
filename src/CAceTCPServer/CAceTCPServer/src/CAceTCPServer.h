#pragma once
#include "CLocalIPPort.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"
#include <afxmt.h>
#include <vector>
#include <map>
using namespace std;
#include "CAceTCPServerMacro.h"
#include "Cjson/CjsonAPI.h"

#define MsgIDReq jsonReq["MsgID"].toValue().nValue
#define MsgIDRsp jsonRsp["MsgID"].toValue().nValue

#ifdef _DEBUG
#pragma comment(lib,"ACEd.lib")
#else
#pragma comment(lib,"ACE.lib")
#endif

class CLocalIPPort;
class CAceTCPServerAPI CAceTCPServer{
	//�������ȿ�����init֮���Ѿ���һ���߳�������recv��
public:
	ACE_SOCK_Acceptor* pacceptor;
	vector<ACE_SOCK_Stream*> vecIPPeer;
	CMutex mutex;
	//���ʹ��json�����ӼĴ�ģ�飬����map
	BOOL ifUseJson;
	int CheckKeyServer;
	int CheckKeyReqTemp;
	map<int,Cjson> mapCheck;

public:
	CAceTCPServer();
	~CAceTCPServer();

public:
	//�򿪶˿ڳɹ�֮�����һ���̺߳�̨�ȴ��ͻ�������
	//һ���пͻ����������������߳��п����߳����ڴ����͵���Ϣ����֤һֱ��һ���̵߳ȴ�����
	BOOL init(int port,int RecvMaxLength,int ifUseJson = 0);
	//���������׵�ַ�����ͳ��ȣ�ͨ·��ַͨ��vecIPPeer��ȡ������ʵ�ʷ��ͳ�ȥ�ĳ���
	int send(char* pData,int length,ACE_SOCK_Stream* ppeer,int sendTimes = 3);
	//���һ���ǵ�ǰ������Ϣ�Ŀͻ���ͨ·��ַ
	virtual void receive(char* pData,int length,ACE_SOCK_Stream* ppeer) = 0;
	
	int SendReqJson(Cjson jsonReq,int MsgID,ACE_SOCK_Stream* ppeer,Cjson jsonCheckPackage = Cjson(),int sendTimes = 3);
	int SendRspJson(Cjson jsonRsp,int MsgID,int CheckKeyClient,ACE_SOCK_Stream* ppeer,int sendTimes = 3);
	//�麯�������е�ͨ·��Ϣ���룬�������Ϊ����Ĭ��Ϊ�ظ�
	virtual Cjson ReceiveReqJson(Cjson jsonReq,vector<ACE_SOCK_Stream*>* pvecSendIPPeer) = 0;
	virtual void ReceiveRspJson(Cjson jsonRsp,Cjson jsonCheckPackage) = 0;
	
	CLocalIPPort GetLocalIPPort(ACE_SOCK_Stream* ppeer);


	void DeleteMap(int CheckKeyServer);
};