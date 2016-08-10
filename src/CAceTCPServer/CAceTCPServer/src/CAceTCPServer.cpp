#include <SDKDDKVer.h>
#include "CAceTCPServer.h"

#define Create_Thread(FunName,ParameterName,ThreadID) CreateThread(NULL, 0, FunName, (LPVOID)ParameterName, 0, &ThreadID);

typedef struct Threadpackage{
	CAceTCPServer* pThis;
	ACE_SOCK_Stream* ppeer;
	int RecvMaxLength;
	CMutex* pmutex;
	ACE_SOCK_Acceptor* pacceptor;
	vector<ACE_SOCK_Stream*>* pvecIPPeer;
}Threadpackage;

CAceTCPServer::CAceTCPServer(){
	pacceptor = new ACE_SOCK_Acceptor;
}

CAceTCPServer::~CAceTCPServer(){
	delete pacceptor;
}

DWORD WINAPI ThreadClient(LPVOID lpParam){
	Threadpackage* pClientPackage = new Threadpackage;
	Threadpackage ClientPackage = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;
	int nReceiveLength = 0;
	char* pbuf = (char *)calloc(ClientPackage.RecvMaxLength,1);
	//���տͻ��˷��͵����ݣ���������������һ���Ϳͻ��˶Ͽ�������ȡ����������0���������򷵻�-1
	while((nReceiveLength = ClientPackage.ppeer->recv(pbuf,ClientPackage.RecvMaxLength)) != -1){
		//���������һ���������򲻴����ڶ���ʱ�ᴫһ��������
		if(nReceiveLength != 0){
			//�û�������麯������
			ClientPackage.pmutex->Lock();
			ClientPackage.pThis->Receive(pbuf,nReceiveLength);
			ClientPackage.pmutex->Unlock();
			//���麯��������pBuf����������֮����ѻ���������
			memset(pbuf,0,nReceiveLength);
			nReceiveLength = 0;
		}
		//��������˿������������ͻ��˷���һ���������ݲ�����ͨ·֪���Ѿ���������-1�˳�ѭ��
		else ClientPackage.ppeer->send("",1);
	}
	//һ���Ϳͻ��˶Ͽ����ͨ·��recvĬ�϶��᷵��-1�ˣ�����ֱ�ӹر�ͨ·
	ClientPackage.ppeer->close();
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
			DWORD ThreadID = 0;
			Create_Thread(ThreadClient,pClientPackage,ThreadID);
		}
	}
}

BOOL CAceTCPServer::init(int port,int RecvMaxLength){
	ACE_INET_Addr port_to_listen(port); //�󶨵Ķ˿�
	
	if(pacceptor->open(port_to_listen,1) == -1){ //�󶨶˿�
		AfxMessageBox("�򿪶˿�ʧ��");
		return 0;
	}
	//��һ���߳�������������
	//���һ�������û�������麯������Ҫ������������ͻ������ӵ�ʱ�򣬱����ȴ�����һ���ͻ��˵����ݲ��ܴ���ڶ���
	Threadpackage* pThreadRecvPac = new Threadpackage;
	pThreadRecvPac->pmutex = &mutex;
	pThreadRecvPac->RecvMaxLength = RecvMaxLength;
	pThreadRecvPac->pThis = this;
	pThreadRecvPac->pacceptor = pacceptor;
	pThreadRecvPac->pvecIPPeer = &vecIPPeer;
	//���߳�
	DWORD ThreadID = 0;
	Create_Thread(ThreadRecv,pThreadRecvPac,ThreadID);

	return 1;
}

int CAceTCPServer::Send(char* pData,int length,ACE_SOCK_Stream* ppeer){
	return ppeer->send(pData,length);
}

CLocalIPPort CAceTCPServer::GetLocalIPPort(ACE_SOCK_Stream* ppeer){
	CLocalIPPort local;
	ACE_INET_Addr raddr;  
	ppeer->get_local_addr(raddr);  
	local.IP = raddr.get_host_addr();
	local.port = raddr.get_port_number();
	return local;
}