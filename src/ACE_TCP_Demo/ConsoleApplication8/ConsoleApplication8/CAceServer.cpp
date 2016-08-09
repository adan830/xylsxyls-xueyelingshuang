#include <SDKDDKVer.h>
#include "CAceServer.h"
#include <afxmt.h>

CAceServer::~CAceServer(){
	delete pacceptor;
}

BOOL CAceServer::init(int port){
	ACE_INET_Addr port_to_listen(port); //�󶨵Ķ˿�
	
	pacceptor = new ACE_SOCK_Acceptor;
	if(pacceptor->open(port_to_listen,1) == -1){ //�󶨶˿�
		AfxMessageBox("�򿪶˿�ʧ��");
		return 0;
	}
	return 1;
}

#define Create_Thread(FunName,ParameterName,ThreadID) CreateThread(NULL, 0, FunName, (LPVOID)ParameterName, 0, &ThreadID);

typedef struct Threadpackage{
	CAceServer* pThis;
	ACE_SOCK_Stream* ppeer;
	int maxLength;
	BOOL ifSend;
	CMutex* pmutex;
}Threadpackage;

DWORD WINAPI ThreadConnect(LPVOID lpParam){
	Threadpackage package = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;
	int nReceiveLength = 0;
	char* pbuf = (char *)calloc(package.maxLength,1);
	//���տͻ��˷��͵����ݣ���������������һ���Ϳͻ��˶Ͽ�������ȡ����������0���������򷵻�-1
	while((nReceiveLength = package.ppeer->recv(pbuf,package.maxLength)) != -1){
		//���������һ���������򲻴����ڶ���ʱ�ᴫһ��������
		if(nReceiveLength != 0){
			//�û�������麯������
			package.pmutex->Lock();
			CMessage message = package.pThis->Receive(pbuf,nReceiveLength);
			package.pmutex->Unlock();
			//���麯��������pBuf����������֮����ѻ���������
			memset(pbuf,0,nReceiveLength);
			nReceiveLength = 0;
			if(package.ifSend == 1){
				//�Կͻ��˷�����
				package.ppeer->send(message.pBuf,message.length);
			}
		}
		//��������˿������������ͻ��˷���һ���������ݲ�����ͨ·֪���Ѿ���������-1�˳�ѭ��
		else package.ppeer->send("",1);
	}
	//һ���Ϳͻ��˶Ͽ����ͨ·��recvĬ�϶��᷵��-1�ˣ�����ֱ�ӹر�ͨ·
	package.ppeer->close();
	delete package.ppeer;
	return 0;
}

int CAceServer::recv(int maxLength,BOOL ifSend){
	//���һ�������û�������麯������Ҫ������������ͻ������ӵ�ʱ�򣬱����ȴ�����һ���ͻ��˵����ݲ��ܴ���ڶ���
	CMutex *pmutex = new CMutex;
	while(1){
		//�Ͳ�ͬ�ͻ���������Ҫ��ͬ��ͨ·
		ACE_SOCK_Stream* ppeer = new ACE_SOCK_Stream;
		//��������������һ���Ϳͻ�����������ȥ�������̣߳�֮������д������߳������У����̵߳ȴ���һ��������
		if(pacceptor->accept(*ppeer) != -1){
			//��Ҫ�����̲߳���Ҫ������
			Threadpackage* ppackage = new Threadpackage;
			ppackage->pThis = this;
			ppackage->ppeer = ppeer;
			ppackage->maxLength = maxLength;
			ppackage->ifSend = ifSend;
			ppackage->pmutex = pmutex;
			DWORD ThreadID = NULL;
			Create_Thread(ThreadConnect,ppackage,ThreadID);
		}
	}
	delete pmutex;
	return 0;
}

CLocalIPPort CAceServer::GetLocalIPPort(){
	CLocalIPPort local;
	ACE_SOCK_Stream peer;
	ACE_INET_Addr raddr;  
	peer.get_local_addr(raddr);  
	local.IP = raddr.get_host_addr();
	local.port = raddr.get_port_number();
	return local;
}