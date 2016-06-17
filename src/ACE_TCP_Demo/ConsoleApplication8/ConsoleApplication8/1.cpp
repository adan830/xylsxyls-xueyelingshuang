#include "ace/SOCK_Acceptor.h"  
#include "ace/SOCK_Stream.h"  
#include "ace/INET_Addr.h"  
#include "ace/Time_Value.h"  

#include <string>  
#include <iostream>  
using namespace std;  

int main(int argc, char *argv[])   
{  
	ACE_INET_Addr port_to_listen(3000);        //�󶨵Ķ˿�  
	ACE_SOCK_Acceptor acceptor;  
	if (acceptor.open (port_to_listen, 1) == -1)     //�󶨶˿�  
	{  
		cout<<endl<<"bind port fail"<<endl;  
		return -1;  
	}  

	while(true)  
	{  
		ACE_SOCK_Stream peer;        //�Ϳͻ��˵�����ͨ·  
		ACE_Time_Value timeout (10, 0);  

		if (acceptor.accept (peer) != -1)    //�����Ϳͻ��˵�����  
		{  
			cout<<endl<<endl<<"client connect. "<<endl;  
			char buffer[1024];  
			ssize_t bytes_received;  

			ACE_INET_Addr raddr;  
			peer.get_local_addr(raddr);  
			cout<<endl<<"local port\t"<<raddr.get_host_name()<<"\t"<<raddr.get_port_number()<<endl;  

			while ((bytes_received = peer.recv (buffer, sizeof(buffer))) != -1)    //��ȡ�ͻ��˷��͵�����  
			{  
				//if(bytes_received == 0) break;
				peer.send(buffer, bytes_received);    //�Կͻ��˷�����  
			}  
			peer.close ();  
		}  
	}  

	return 0;   
}