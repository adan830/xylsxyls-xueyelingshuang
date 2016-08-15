#pragma once
#include "CLocalIPPort.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Connector.h"
#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"
#include <afxmt.h>
#include "CAceTCPClientMacro.h"
#include <map>
using namespace std;
#include "Cjson/CjsonAPI.h"

#define MsgIDReq jsonReq["MsgID"].toValue().nValue
#define MsgIDRsp jsonRsp["MsgID"].toValue().nValue

#ifdef _DEBUG
#pragma comment(lib,"ACEd.lib")
#else
#pragma comment(lib,"ACE.lib")
#endif

class CAceTCPClientAPI CAceTCPClient{
	//�ڳ�ʼ��֮����Ѿ���һ���߳�����recv��
public:
	ACE_SOCK_Connector* pconnector;
	ACE_SOCK_Stream* ppeer;
	ACE_INET_Addr* paddr;
	ACE_Time_Value* ptimeout;
	CMutex mutex;
	//�Ƿ�ʹ��json�����ʹ�������ӼĴ�ģ�飬�ѼĴ�Կ�׺Ÿ���������һȦ��Ȼ�������map���üĴ���Ϣ
	BOOL ifUseJson;
	int CheckKeyClient;
	map<int,Cjson> mapCheck;

public:
	~CAceTCPClient();

public:
	//�ͷ��������ӳɹ��򷵻�1��ʧ�ܷ���0������֮�����һ���̺߳�̨���շ������������͵Ķ�����RecvMaxLengthΪ���ջ���������
	//�Ƿ�ʹ��json�����ʹ��json�����麯��ReceiveJson��Ĭ�ϲ�ʹ��
	BOOL init(CString strIP,int port,int ConnectWaitTime,int RecvMaxLength,int ReconnectTime,int ifUseJson = 0);
	//���������׵�ַ�����ݳ��ȣ����ʹ������ɹ��򲻼�������������ʵ�ʷ��ͳ�ȥ�ĳ���
	int send(char *pData,int length,int sendTimes = 3);
	//�����麯��
	virtual void receive(char *pData,int length) = 0;

	/////////////////////////ʹ��json//////////////////////
	//������麯���лظ���ʹ��Rsp��������ʹ��Req
	int SendJsonReq(Cjson jsonRsp,int MsgID,Cjson jsonCheckPackage = Cjson(),int sendTimes = 3);
	
	//�����麯��
	virtual Cjson ReceiveReqJson(Cjson jsonReq) = 0;
	virtual void ReceiveRspJson(Cjson jsonRsp,Cjson jsonCheckPackage) = 0;
	


	//���º����û�����ʹ��
	int SendJsonRsp(Cjson jsonRsp,int MsgID,int CheckKeyServer,int sendTimes = 3);
	void DeleteMap(int CheckKeyClient);
};