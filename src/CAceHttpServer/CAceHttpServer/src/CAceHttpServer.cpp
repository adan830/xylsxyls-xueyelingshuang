#include <SDKDDKVer.h>
#include "CAceHttpServer.h"
#include "CCharset/CCharsetAPI.h"

typedef struct Threadpackage{
	CAceHttpServer* pThis;
	ACE_SOCK_Stream* ppeer;
	int RecvMaxLength;
	CMutex* pmutex;
	ACE_SOCK_Acceptor* pacceptor;
	int DataStyle;
	char* pBuf;
}Threadpackage;

CAceHttpServer::CAceHttpServer(){
	pacceptor = new ACE_SOCK_Acceptor;
	DataStyle = 0;
}

CAceHttpServer::~CAceHttpServer(){
	delete pacceptor;
}

DWORD WINAPI ThreadClientHandling(LPVOID lpParam){
	Threadpackage ClientPackage = *((Threadpackage *)lpParam);
	delete (Threadpackage *)lpParam;

	//�û�������麯��������������Ϊһ����һ����ΪSleep�ȿ�ס�����еĶ�����ס
	//ClientPackage.pmutex->Lock();
	//ʹ��jsonģʽ
	if(ClientPackage.DataStyle == 1){
		CHttpString str;
		str.str = ClientPackage.pBuf;
		int nCharset = str.GetCharset();
		if(nCharset == 1);
		else if(nCharset == 2) str.str = CCharset::Utf8ToAnsi((LPSTR)(LPCTSTR)str.str).c_str();
		else AfxMessageBox("�ַ�������" + str.str);
		Cjson jsonRsp = ClientPackage.pThis->ReceiveReqJson(str.GetJsonData(),str.GetProtocol(),str);
		ClientPackage.pThis->SendRspJson(jsonRsp,str.GetProtocol(),ClientPackage.ppeer);
	}
	else{
		CString strError = "";
		strError.Format("ģʽֵ����ֵΪ%d",ClientPackage.DataStyle);
		AfxMessageBox(strError);
	}
	//ClientPackage.pmutex->Unlock();
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
			*pClientPackage = ClientPackage;
			DWORD ThreadID = 0;
			Create_Thread(ThreadClientHandling,pClientPackage,ThreadID);
		}
		//��������˿������������ͻ��˷���һ���������ݲ�����ͨ·֪���Ѿ���������-1�˳�ѭ��
		else ClientPackage.ppeer->send("",1);
	}
	//һ���Ϳͻ��˶Ͽ����ͨ·��recvĬ�϶��᷵��-1�ˣ�����ֱ�ӹر�ͨ·
	ClientPackage.ppeer->close();
	delete ClientPackage.ppeer;

	free(pbuf);
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
			//��Ҫ�����̲߳���Ҫ������
			Threadpackage* pClientPackage = new Threadpackage;
			pClientPackage->pThis = package.pThis;
			pClientPackage->ppeer = ppeer;
			pClientPackage->RecvMaxLength = package.RecvMaxLength;
			pClientPackage->pmutex = package.pmutex;
			pClientPackage->DataStyle = package.DataStyle;
			DWORD ThreadID = 0;
			Create_Thread(ThreadClient,pClientPackage,ThreadID);
		}
	}
}

BOOL CAceHttpServer::init(int port,int RecvMaxLength,int DataStyle,int nCharset){
	ACE_INET_Addr port_to_listen(port); //�󶨵Ķ˿�

	if(pacceptor->open(port_to_listen,1) == -1){ //�󶨶˿�
		AfxMessageBox("�򿪶˿�ʧ��");
		return 0;
	}
	this->DataStyle = DataStyle;
	this->nCharset  = nCharset ;

	//��һ���߳�������������
	//���һ�������û�������麯������Ҫ������������ͻ������ӵ�ʱ�򣬱����ȴ�����һ���ͻ��˵����ݲ��ܴ���ڶ���
	Threadpackage* pThreadRecvPac = new Threadpackage;
	pThreadRecvPac->pmutex = &mutex;
	pThreadRecvPac->RecvMaxLength = RecvMaxLength;
	pThreadRecvPac->pThis = this;
	pThreadRecvPac->pacceptor = pacceptor;
	pThreadRecvPac->DataStyle = DataStyle;
	//���߳�
	DWORD ThreadID = 0;
	Create_Thread(ThreadRecv,pThreadRecvPac,ThreadID);

	return 1;
}

int CAceHttpServer::SendRspJson(Cjson jsonRsp,CString strProtocol,ACE_SOCK_Stream* ppeer,int sendTimes){
	if(DataStyle == 1){
		//���ͻظ���
		CHttpString strSendString;
		strSendString.InitServer(1,DataStyle,nCharset);
		if(nCharset == 1) strSendString.SetData(jsonRsp.toCString("",""));
		else if(nCharset == 2) strSendString.SetData(CCharset::AnsiToUtf8((LPSTR)(LPCTSTR)jsonRsp.toCString("","")).c_str());
		return ppeer->send((LPSTR)(LPCTSTR)strSendString.str,strSendString.str.GetLength()); //��������
	}
	return -1;
}