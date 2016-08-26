#include <SDKDDKVer.h>
#include "CAceTCPServer.h"
#include "CDeleteMapWatch.h"

typedef struct Threadpackage{
	CAceTCPServer* pThis;
	ACE_SOCK_Stream* ppeer;
	int RecvMaxLength;
	CMutex* pmutex;
	ACE_SOCK_Acceptor* pacceptor;
	vector<ACE_SOCK_Stream*>* pvecIPPeer;
	BOOL ifUseJson;
	char* pBuf;
	int nReceiveLength;
}Threadpackage;

CAceTCPServer::CAceTCPServer(){
	pacceptor = new ACE_SOCK_Acceptor;
	ifUseJson = 0;
	CheckKeyServer = 0;
}

CAceTCPServer::~CAceTCPServer(){
	delete pacceptor;
}

DWORD WINAPI ThreadClientHandling(LPVOID lpParam){
	Threadpackage ClientPackage = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;

	//�û�������麯������
	ClientPackage.pmutex->Lock();
	//��ʹ��jsonģʽ
	if(ClientPackage.ifUseJson == 0){
		ClientPackage.pThis->receive(ClientPackage.pBuf,ClientPackage.nReceiveLength,ClientPackage.ppeer);
	}
	//ʹ��jsonģʽ
	else if(ClientPackage.ifUseJson == 1){
		Cjson json;
		json.LoadJson(ClientPackage.pBuf);
		int MsgID = json["MsgID"].toValue().nValue;
		int CheckKeyClient = json["CheckKeyClient"].toValue().nValue;
		int CheckKeyServer = json["CheckKeyServer"].toValue().nValue;
		//����ǿͻ������������İ�����Ҫ����Ӧ
		if(CheckKeyClient >= 0 && CheckKeyServer == -1){
			//����˳�򣬷����÷���ͨ·
			vector<ACE_SOCK_Stream*> vecSendIPPeer;
			int i = -1;
			while(i++ != ClientPackage.pThis->vecIPPeer.size() - 1){
				if(ClientPackage.pThis->vecIPPeer.at(i) != ClientPackage.ppeer){
					vecSendIPPeer.push_back(ClientPackage.pThis->vecIPPeer.at(i));
				}
			}
			vecSendIPPeer.push_back(ClientPackage.ppeer);
			Cjson jsonReq = json;
			jsonReq["MsgID"] = "delete";
			jsonReq["CheckKeyClient"] = "delete";
			Cjson jsonRsp = ClientPackage.pThis->ReceiveReqJson(jsonReq,MsgID,&vecSendIPPeer);
			//����vector���ͨ·����
			i = -1;
			while(i++ != vecSendIPPeer.size() - 1){
				ClientPackage.pThis->SendRspJson(jsonRsp,MsgID,CheckKeyClient,vecSendIPPeer.at(i));
			}
		}
		//����ǿͻ�����Ӧ�����������İ�
		else if(CheckKeyClient == -1 && CheckKeyServer >= 0){
			Cjson jsonRsp = json;
			jsonRsp["MsgID"] = "delete";
			jsonRsp["CheckKeyClient"] = "delete";
			//����Ӧjson�ͼĴ�json�����麯��
			ClientPackage.pThis->ReceiveRspJson(jsonRsp,MsgID,ClientPackage.pThis->mapCheck[CheckKeyServer]);
			//ɾ��map�еļĴ����
			ClientPackage.pThis->DeleteMap(CheckKeyServer);
		}
		else{
			CString strError = "";
			strError.Format("Keyֵ����CheckKeyClient = %d��CheckKeyServer = %d",CheckKeyClient,CheckKeyServer);
			AfxMessageBox(strError);
		}
	}
	else{
		CString strError = "";
		strError.Format("�Ƿ�ʹ��jsonֵ����ֵΪ%d",ClientPackage.ifUseJson);
		AfxMessageBox(strError);
	}
	ClientPackage.pmutex->Unlock();
	return 0;
}

DWORD WINAPI ThreadClient(LPVOID lpParam){
	Threadpackage ClientPackage = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;
	int nReceiveLength = 0;
	char* pbuf = (char *)calloc(ClientPackage.RecvMaxLength,1);
	//���տͻ��˷��͵����ݣ���������������һ���Ϳͻ��˶Ͽ�������ȡ����������0���������򷵻�-1
	while((nReceiveLength = ClientPackage.ppeer->recv(pbuf,ClientPackage.RecvMaxLength)) != -1){
		//���������һ���������򲻴����ڶ���ʱ�ᴫһ��������
		if(nReceiveLength > 0){
			pbuf[nReceiveLength] = 0;
			//һ�����յ�����������߳��д�����ֹ��Ϊ�麯���Ĵ������ݿ�����ȴ�
			Threadpackage* pClientPackage = new Threadpackage;
			ClientPackage.pBuf = (char *)calloc(nReceiveLength + 1,1);
			memcpy(ClientPackage.pBuf,pbuf,nReceiveLength);
			ClientPackage.nReceiveLength = nReceiveLength;
			*pClientPackage = ClientPackage;
			DWORD ThreadID = 0;
			Create_Thread(ThreadClientHandling,pClientPackage,ThreadID);
		}
		//��������˿������������ͻ��˷���һ���������ݲ�����ͨ·֪���Ѿ���������-1�˳�ѭ��
		else ClientPackage.ppeer->send("",1);
	}
	//һ���Ϳͻ��˶Ͽ����ͨ·��recvĬ�϶��᷵��-1�ˣ�����ֱ�ӹر�ͨ·
	ClientPackage.ppeer->close();
	//���������б���ͨ·��vector��ɾ���ϵ���ͨ·
	ClientPackage.pmutex->Lock();
	int i = -1;
	while(i++ != ClientPackage.pvecIPPeer->size() - 1){
		if(ClientPackage.pvecIPPeer->at(i) == ClientPackage.ppeer) break;
	}
	if((unsigned int)i < ClientPackage.pvecIPPeer->size()){
		ClientPackage.pvecIPPeer->erase(ClientPackage.pvecIPPeer->begin() + i);
	}
	else AfxMessageBox("ͨ·�ѱ��ͷ�");
	ClientPackage.pmutex->Unlock();
	free(pbuf);
	delete ClientPackage.ppeer;
	return 0;
}

DWORD WINAPI ThreadRecv(LPVOID lpParam){
	Threadpackage package = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;
	while(1){
		//�Ͳ�ͬ�ͻ���������Ҫ��ͬ��ͨ·
		ACE_SOCK_Stream* ppeer = new ACE_SOCK_Stream;
		//��������������һ���Ϳͻ�����������ȥ�������̣߳�֮������д������߳������У����̵߳ȴ���һ��������
		if(package.pacceptor->accept(*ppeer) != -1){
			//����֮�����ڿ����ж���ͻ���������Ҫ����̣߳��Ȱ�ͨ·����vec
			package.pmutex->Lock();
			package.pvecIPPeer->push_back(ppeer);
			package.pmutex->Unlock();
			//��Ҫ�����̲߳���Ҫ������
			Threadpackage* pClientPackage = new Threadpackage;
			pClientPackage->pThis = package.pThis;
			pClientPackage->ppeer = ppeer;
			pClientPackage->RecvMaxLength = package.RecvMaxLength;
			pClientPackage->pmutex = package.pmutex;
			pClientPackage->pvecIPPeer = package.pvecIPPeer;
			pClientPackage->ifUseJson = package.ifUseJson;
			DWORD ThreadID = 0;
			Create_Thread(ThreadClient,pClientPackage,ThreadID);
		}
	}
}

BOOL CAceTCPServer::init(int port,int RecvMaxLength,int ifUseJson){
	ACE_INET_Addr port_to_listen(port); //�󶨵Ķ˿�
	
	if(pacceptor->open(port_to_listen,1) == -1){ //�󶨶˿�
		AfxMessageBox("�򿪶˿�ʧ��");
		return 0;
	}
	this->ifUseJson = ifUseJson;

	//��һ���߳�������������
	//���һ�������û�������麯������Ҫ������������ͻ������ӵ�ʱ�򣬱����ȴ�����һ���ͻ��˵����ݲ��ܴ���ڶ���
	Threadpackage* pThreadRecvPac = new Threadpackage;
	pThreadRecvPac->pmutex = &mutex;
	pThreadRecvPac->RecvMaxLength = RecvMaxLength;
	pThreadRecvPac->pThis = this;
	pThreadRecvPac->pacceptor = pacceptor;
	pThreadRecvPac->pvecIPPeer = &vecIPPeer;
	pThreadRecvPac->ifUseJson = ifUseJson;
	//���߳�
	DWORD ThreadID = 0;
	Create_Thread(ThreadRecv,pThreadRecvPac,ThreadID);

	return 1;
}

int CAceTCPServer::send(char* pData,int length,ACE_SOCK_Stream* ppeer,int sendTimes){
	if(ifUseJson == 1){
		AfxMessageBox("jsonģʽ������ʹ�ô˺���");
		return 0;
	}
	return ppeer->send(pData,length);
}

int CAceTCPServer::SendReqJson(Cjson jsonReq,int MsgID,ACE_SOCK_Stream* ppeer,Cjson jsonCheckPackage,int nDeleteTime,int sendTimes){
	if(ifUseJson == 0){
		AfxMessageBox("δ����ʹ��jsonģʽ");
		return 0;
	}
	//������Ϣ��
	jsonReq["MsgID"] = MsgID;
	//��������������������ϼĴ�Կ��
	jsonReq["CheckKeyServer"] = ++CheckKeyServer;
	//����Կ�װѰ�������map��
	mapCheck[CheckKeyServer] = jsonCheckPackage;
	//��ʱ������һ��ʱ��֮��Ѷ�Ӧ�İ���ɾ������ֹ������Ϊ���粻�ö��治����Ϣ�����
	CDeleteMapWatch* pWatch = new CDeleteMapWatch;
	WatchPac* ppackage = new WatchPac;
	ppackage->CheckKeyServer = CheckKeyServer;
	ppackage->pThis = this;
	pWatch->CountDown(nDeleteTime * 1000,ppackage);
	//����
	CString strSendJson = jsonReq.toCString("","");
	return ppeer->send((LPSTR)(LPCTSTR)strSendJson,strSendJson.GetLength()); //��������
}

int CAceTCPServer::SendRspJson(Cjson jsonRsp,int MsgID,int CheckKeyClient,ACE_SOCK_Stream* ppeer,int sendTimes){
	if(ifUseJson == 0){
		AfxMessageBox("δ����ʹ��jsonģʽ");
		return 0;
	}
	//������Ϣ��
	jsonRsp["MsgID"] = MsgID;
	//����ͻ��˻ظ�����
	jsonRsp["CheckKeyClient"] = CheckKeyClient;
	//���ͻظ���
	CString strSendJson = jsonRsp.toCString("","");
	return ppeer->send((LPSTR)(LPCTSTR)strSendJson,strSendJson.GetLength()); //��������
}

ACE_SOCK_Stream* CAceTCPServer::GetReqPeer(vector<ACE_SOCK_Stream*>* pvecSendIPPeer){
	return pvecSendIPPeer->at(pvecSendIPPeer->size() - 1);
}

void CAceTCPServer::OnlyRspToReq(vector<ACE_SOCK_Stream*>* pvecSendIPPeer){
	ACE_SOCK_Stream* ppeer = GetReqPeer(pvecSendIPPeer);
	pvecSendIPPeer->clear();
	pvecSendIPPeer->push_back(ppeer);
	return;
}

CLocalIPPort CAceTCPServer::GetLocalIPPort(ACE_SOCK_Stream* ppeer){
	CLocalIPPort local;
	ACE_INET_Addr raddr;  
	ppeer->get_local_addr(raddr);  
	local.IP = raddr.get_host_addr();
	local.port = raddr.get_port_number();
	return local;
}

void CAceTCPServer::DeleteMap(int CheckKeyServer){
	mutexDeleteMap.Lock();
	auto it = mapCheck.begin();
	for(;it != mapCheck.end();++it){
		if(it->first == CheckKeyServer){
			mapCheck.erase(it);
			return;
		}
	}
	mutexDeleteMap.Unlock();
	return;
}