// ConsoleApplication15.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <WINSOCK2.H>
#include <stdio.h> 
#pragma comment(lib,"ws2_32.lib")
void main() 
{ 
	//�����׽��� 
	WORD myVersionRequest;
	WSADATA wsaData; 
	myVersionRequest=MAKEWORD(1,1);
	int err; 
	err=WSAStartup(myVersionRequest,&wsaData);
	if (!err) { 
		printf("�Ѵ��׽���\n"); 
	} 
	else {
		//��һ�����׽��� 
		printf("Ƕ����δ��!"); 
		return; 
	} 
	SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//�����˿�ʶ���׽���
	//��Ҫ�󶨵Ĳ��� 
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//ip��ַ
	addr.sin_port=htons(6000);
	//�󶨶˿� 
	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));
	//����� 
	listen(serSocket,5);//���еڶ������������ܹ����յ�����������
	////////////////////////////////////////////////////////////////////////// //��ʼ���м��� ////////////////////////////////////////////////////////////////////////// 
	SOCKADDR_IN clientsocket; 
	int len=sizeof(SOCKADDR); 
	int serConn = -1;
	while (1) { 
		serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);
		//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ��� 
		
		char receiveBuf[100] = {};
		//���� 
		recv(serConn,receiveBuf,101,0); 
		printf("���գ�%s\n",receiveBuf); 
		char sendBuf[100] = {}; 
		sprintf(sendBuf,"welcome %s to bejing",inet_ntoa(clientsocket.sin_addr));
		//�ҶԶ�Ӧ��IP���ҽ������ִ�ӡ������ 
		send(serConn,sendBuf,strlen(sendBuf)+1,0);
	}
	//�ͷ���Դ�Ĳ���
	closesocket(serConn);
	//�ر�
	WSACleanup();
} 
