#pragma once

//#include <windows.h>
#include <afxwin.h>

class CSerial
{
public:
	CSerial(void);
	~CSerial(void);

	//�򿪴���
	BOOL OpenSerialPort(TCHAR* port,UINT baud_rate,BYTE date_bits,BYTE stop_bit,BYTE parity=0);

	//��������
	BOOL SendData(char* data,int len);

	//����
	BOOL Send(char* data);

	//��ʼ��
	BOOL init();
	//����
	BOOL Send(int in,int out);
public:
	HANDLE m_hComm;
};