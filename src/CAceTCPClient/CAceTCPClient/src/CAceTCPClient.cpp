#include <SDKDDKVer.h>
#include "CAceTCPClient.h"
#include "CDeleteMapWatch.h"

typedef struct Threadpackage{
	CAceTCPClient* pThis;
	ACE_SOCK_Stream* ppeer;
	int RecvMaxLength;
	int ReconnectTime;
	CMutex* pmutex;
	BOOL ifUseJson;
	ACE_INET_Addr* paddr;
	ACE_Time_Value* ptimeout;
	char* pBuf;
	int RecvLength;
}Threadpackage;

CAceTCPClient::~CAceTCPClient(){
	ppeer->close();
	delete pconnector;
	delete ppeer;
	delete ptimeout;
	delete paddr;
}

DWORD WINAPI ThreadRecvHandling(LPVOID lpParam){
	Threadpackage package = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;

	package.pmutex->Lock();
	//�ж��Ƿ�ʹ��json
	if(package.ifUseJson == 1){
		//���յ��Ƿ�����������������ݣ��������������һ���ǻظ���һ������������
		Cjson json;
		json.LoadJson(package.pBuf);
		int MsgID = json["MsgID"].toValue().nValue;
		int CheckKeyClient = json["CheckKeyClient"].toValue().nValue;
		int CheckKeyServer = json["CheckKeyServer"].toValue().nValue;
		//����ǻظ��ͻ��ˣ��õ���Ӧ������Ҫ����Send
		if(CheckKeyClient >= 0 && CheckKeyServer == -1){
			Cjson jsonRsp = json;
			jsonRsp["MsgID"] = "delete";
			jsonRsp["CheckKeyClient"] = "delete";
			//����Ӧjson�ͼĴ�json�����麯��
			package.pThis->ReceiveRspJson(jsonRsp,MsgID,package.pThis->mapCheck[CheckKeyClient]);
			//ɾ��map�еļĴ����
			package.pThis->DeleteMap(CheckKeyClient);
		}
		//����Ƿ�����������ͣ�����Ҫ����Ӧ
		else if(CheckKeyClient == -1 && CheckKeyServer >= 0){
			Cjson jsonReq = json;
			jsonReq["MsgID"] = "delete";
			jsonReq["CheckKeyServer"] = "delete";
			package.pThis->SendJsonRsp(package.pThis->ReceiveReqJson(jsonReq,MsgID),MsgID,CheckKeyServer,3);
		}
		else{
			CString strError = "";
			strError.Format("keyֵ����CheckKeyClient = %d��CheckKeyServer = %d",CheckKeyClient,CheckKeyServer);
			AfxMessageBox(strError);
		}
	}
	else package.pThis->receive(package.pBuf,package.RecvLength);
	package.pmutex->Unlock();
	free(package.pBuf);
	return 0;
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
			//һ�����ܵ���Ϣ֮��Ӧ���ô������߳���ִ�У����߳���Ȼ�ȴ����գ��߳��ڼ���
			//�ô�������麯�����еȴ������Ȳ���ʱ����Ӱ��������Ϣ�Ľ���
			DWORD ThreadID = 0;
			char* pBuf = (char *)calloc(RecvLength + 1,1);
			memcpy(pBuf,pbuf,RecvLength);
			package.pBuf = pBuf;
			package.RecvLength = RecvLength;
			Threadpackage *ppackage = new Threadpackage;
			*ppackage = package;
			Create_Thread(ThreadRecvHandling,ppackage,ThreadID);
		}
		//�����������ͻ��˶���recv����ȡ����������-1
		else{
			Sleep(package.ReconnectTime * 1000);
			//���������ѭ������������һ������ppeer���ɸ��ã���Ҫ��������
			package.pmutex->Lock();
			delete package.pThis->ppeer;
			package.pThis->ppeer = new ACE_SOCK_Stream;
			package.ppeer = package.pThis->ppeer;
			package.pThis->pconnector->connect(*(package.ppeer),*(package.paddr),package.ptimeout);
			package.pmutex->Unlock();
		}
	}
	free(pbuf);
	return 0;
}

BOOL CAceTCPClient::init(CString strIP,int port,int ConnectWaitTime,int RecvMaxLength,int ReconnectTime,int ifUseJson){

	paddr = new ACE_INET_Addr(port,strIP);
	pconnector = new ACE_SOCK_Connector;
	ptimeout = new ACE_Time_Value(ConnectWaitTime,0);
	ppeer = new ACE_SOCK_Stream;
	this->ifUseJson = ifUseJson;
	CheckKeyClient = 0;

	int nResult = pconnector->connect(*ppeer,*paddr,ptimeout);
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
	ppackage->paddr = paddr;
	ppackage->ptimeout = ptimeout;
	ppackage->ReconnectTime = ReconnectTime;
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

int CAceTCPClient::SendJsonReq(Cjson jsonReq,int MsgID,Cjson jsonCheckPackage,int nDeleteTime,int sendTimes){
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
	//��ʱ������һ��ʱ��֮��Ѷ�Ӧ�İ���ɾ������ֹ������Ϊ���粻�ö��治����Ϣ�����
	CDeleteMapWatch* pWatch = new CDeleteMapWatch;
	WatchPac* ppackage = new WatchPac;
	ppackage->CheckKeyClient = CheckKeyClient;
	ppackage->pThis = this;
	pWatch->CountDown(nDeleteTime * 1000,ppackage);
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
	mutexDeleteMap.Lock();
	auto it = mapCheck.begin();
	for(;it != mapCheck.end();++it){
		if(it->first == CheckKeyClient){
			mapCheck.erase(it);
			return;
		}
	}
	mutexDeleteMap.Unlock();
	//���ܻ�����Ҳ�����������������˻ظ����Ⱥ���Ļ�
	return;
}