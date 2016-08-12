#include <SDKDDKVer.h>
#include "CAceTCPClient.h"

#define Create_Thread(FunName,ParameterName,ThreadID) CreateThread(NULL, 0, FunName, (LPVOID)ParameterName, 0, &ThreadID);

typedef struct Threadpackage{
	CAceTCPClient* pThis;
	ACE_SOCK_Stream* ppeer;
	int RecvMaxLength;
	CMutex* pmutex;
	BOOL ifUseJson;
}Threadpackage;

CAceTCPClient::~CAceTCPClient(){
	ppeer->close();
	delete pconnector;
	delete ppeer;
}

DWORD WINAPI ThreadRecv(LPVOID lpParam){
	Threadpackage package = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;

	char* pbuf = (char *)calloc(package.RecvMaxLength,1);
	while(1){
		int RecvLength = package.ppeer->recv(pbuf,package.RecvMaxLength); //��������
		//�����ڽ�����ʱ�����һ�����ַ���������
		if(RecvLength >= 0){
			pbuf[RecvLength] = 0;
			package.pmutex->Lock();
			//�ж��Ƿ�ʹ��json
			if(package.ifUseJson == 1){
				//���յ��Ƿ�����������������ݣ��������������һ���ǻظ���һ������������
				Cjson json;
				json.LoadJson(pbuf);
				int CheckKeyClient = json["CheckKeyClient"].toValue().nValue;
				int CheckKeyServer = json["CheckKeyServer"].toValue().nValue;
				//����ǻظ��ͻ��ˣ��õ���Ӧ������Ҫ����Send
				if(CheckKeyClient >= 0 && CheckKeyServer == -1){
					//����Ӧjson�ͼĴ�json�����麯��
					package.pThis->ReceiveRspJson(json,package.pThis->mapCheck[CheckKeyClient]);
					//ɾ��map�еļĴ����
					package.pThis->DeleteMap(CheckKeyClient);
				}
				//����Ƿ�����������ͣ�����Ҫ����Ӧ
				else if(CheckKeyClient == -1 && CheckKeyServer >= 0){
					package.pThis->SendJsonRsp(package.pThis->ReceiveReqJson(json),json["MsgID"].toValue().nValue,CheckKeyServer,3);
				}
				else{
					CString strError = "";
					strError.Format("keyֵ����CheckKeyClient = %d��CheckKeyServer = %d",CheckKeyClient,CheckKeyServer);
					AfxMessageBox(strError);
				}
			}
			else package.pThis->receive(pbuf,RecvLength);
			package.pmutex->Unlock();
		}
		//�����������ͻ��˶���recv����ȡ����������-1
		else break;
	}
	free(pbuf);
	return 0;
}

BOOL CAceTCPClient::init(CString strIP,int port,int ConnectWaitTime,int RecvMaxLength,int ifUseJson){

	ACE_INET_Addr addr(port,strIP);
	pconnector = new ACE_SOCK_Connector;
	ACE_Time_Value timeout(ConnectWaitTime,0);
	ppeer = new ACE_SOCK_Stream;
	this->ifUseJson = ifUseJson;
	CheckKeyClient = 0;

	int nResult = pconnector->connect(*ppeer,addr,&timeout);
	if(nResult != 0){
		AfxMessageBox("����ʧ��");
		return 0;
	}
	//�̲߳���
	Threadpackage *ppackage = new Threadpackage;
	ppackage->pmutex = &mutex;
	ppackage->ppeer = ppeer;
	ppackage->pThis = this;
	ppackage->RecvMaxLength = RecvMaxLength;
	ppackage->ifUseJson = ifUseJson;
	//�����̣߳����ں�̨���շ���������������
	DWORD ThreadID = 0;
	Create_Thread(ThreadRecv,ppackage,ThreadID);

	return 1;
}

int CAceTCPClient::send(char *pData,int length,int sendTimes){
	if(ifUseJson == 1){
		AfxMessageBox("jsonģʽ������ʹ�ô˺���");
		return 0;
	}
	return ppeer->send(pData,length); //��������
}

int CAceTCPClient::SendJsonReq(Cjson jsonReq,int MsgID,Cjson jsonCheckPackage,int sendTimes){
	if(ifUseJson == 0){
		AfxMessageBox("δ����ʹ��jsonģʽ");
		return 0;
	}
	//������Ϣ��
	jsonReq["MsgID"] = MsgID;
	//����ͻ���������������ϼĴ�Կ��
	jsonReq["CheckKeyClient"] = ++CheckKeyClient;
	//����Կ�װѰ�������map��
	mapCheck[CheckKeyClient] = jsonCheckPackage;
	//����
	CString strSendJson = jsonReq.toCString("","");
	return ppeer->send((LPSTR)(LPCTSTR)strSendJson,strSendJson.GetLength()); //��������
}

int CAceTCPClient::SendJsonRsp(Cjson jsonRsp,int MsgID,int CheckKeyServer,int sendTimes){
	if(ifUseJson == 0){
		AfxMessageBox("δ����ʹ��jsonģʽ");
		return 0;
	}
	//������Ϣ��
	jsonRsp["MsgID"] = MsgID;
	//����ͻ��˻ظ�����
	jsonRsp["CheckKeyServer"] = CheckKeyServer;
	//���ͻظ���
	CString strSendJson = jsonRsp.toCString("","");
	return ppeer->send((LPSTR)(LPCTSTR)strSendJson,strSendJson.GetLength()); //��������
}

void CAceTCPClient::DeleteMap(int CheckKeyClient){
	auto it = mapCheck.begin();
	for(;it != mapCheck.end();++it){
		if(it->first == CheckKeyClient){
			mapCheck.erase(it);
			return;
		}
	}
	AfxMessageBox("��map���Ҳ�����Ӧ�İ���Կ��");
	return;
}