#include <SDKDDKVer.h>
#include "CCheckUSB.h"
#include <dbt.h>
#include <afxmt.h>

//���߳�
//�趨��DWORD dwThreadId = NULL;����ʵ��ΪDWORD WINAPI add1_fun(LPVOID lpParam)
//DWORD WINAPI add1_fun(LPVOID lpParam){},DWORD WINAPI���ɱ�
//����ֻ�ܶ���һ��������ж����Ҫ���
#define Create_Thread(FunName,ParameterName,ThreadID) CreateThread(NULL, 0, FunName, (LPVOID)ParameterName, 0, &ThreadID)

CCheckUSB *Son = NULL;
//��������ֻ��һ��CCheckUSB
BOOL ifInit = 0;
//1��ʾ����ѭ����0��ʾ�Ѿ��˳�ѭ��
BOOL stateIn = 1;
BOOL stateOut = 1;

CCheckUSB::CCheckUSB(){
	if(ifInit == 0){
		Son = this;
		ifInit = 1;
	}
	else AfxMessageBox("ֻ�������һ��CCheckUSB");

	h_CheckIn = 0;
	h_CheckOut = 0;
	ifCheckIn = 0;
	ifCheckOut = 0;
}

CCheckUSB::~CCheckUSB(){
	if(ifInit == 1){
		if(ifCheckIn == 1){
			//��Ϊ����1֮��Ϳ�ʼ�˳���Ϣ���ѭ��
			CMutex mutex;
			mutex.Lock();
			if(stateIn == 1) stateIn = 3;
			mutex.Unlock();
			//����ֱ���˳�ѭ��֮��ſ���ִ���ͷŶ���
			while(stateIn != 0);
			//��ʱ�ر�֮�������Ѿ���Ч�˲���Ҫ������
			CloseWindow(Son->h_CheckIn);
			if(IsWindow(Son->h_CheckIn) != 0) AfxMessageBox("δ�ɹ��ر�");
			//�ɹ��رմ���֮��Ϳ��Է�ע������
			BOOL nSucceed = UnregisterClass("USBIn",AfxGetInstanceHandle());
			if(nSucceed == 0) AfxMessageBox("��ע����ʧ��");
		}
		
		if(ifCheckOut == 1){
			//��Ϊ����1֮��Ϳ�ʼ�˳���Ϣ���ѭ��
			CMutex mutex;
			mutex.Lock();
			//�����ѭ��������������ѭ��
			if(stateOut == 1) stateOut = 3;
			mutex.Unlock();
			//����ֱ���˳�ѭ��֮��ſ���ִ���ͷŶ���
			while(stateOut != 0);
			//��ʱ�ر�֮�������Ѿ���Ч�˲���Ҫ������
			CloseWindow(Son->h_CheckOut);
			if(IsWindow(Son->h_CheckOut) != 0) AfxMessageBox("δ�ɹ��ر�");
			//�ɹ��رմ���֮��Ϳ��Է�ע������
			BOOL nSucceed = UnregisterClass("USBOut",AfxGetInstanceHandle());
			if(nSucceed == 0) AfxMessageBox("��ע����ʧ��");
		}
	}
	//������֮��Ϳ��Լ����ٲ���CCheckUSB�ˣ�����������Ҫ����Ϊ0
	ifInit = 0;
}

char FirstDriveFromMask(ULONG unitmask){
	char i;
	for(i = 0;i < 26;++i){
		if(unitmask & 0x1) break;
		unitmask = unitmask >> 1;
	}
	return(i + 'A');
}

LRESULT CALLBACK WndProcIn(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
	PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
	char driveName;
	CString diskpath = "";
	if(uMsg == WM_DEVICECHANGE){
		if(wParam == DBT_DEVICEARRIVAL){
			driveName = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			diskpath.Format("%c:\\",driveName);
			Son->USBIn(diskpath);
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI CheckIn(LPVOID lpParam){
	TCHAR szClassName[] = "USBIn";

	WNDCLASS wndclsIn = {0};
	wndclsIn.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclsIn.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wndclsIn.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
	wndclsIn.lpfnWndProc = WndProcIn;
	wndclsIn.lpszClassName = szClassName;
	
	if(RegisterClass(&wndclsIn) == 0){
		AfxMessageBox("RegisterClass Failed!\r\n");
		return 0;
	}
	
	if(Son->h_CheckIn != 0) AfxMessageBox("���д���");
	Son->h_CheckIn = CreateWindow(szClassName,szClassName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,NULL,NULL);
	if(NULL == Son->h_CheckIn){
		AfxMessageBox("CreateWindow Failed!\r\n");
		return 0;
	}
	ShowWindow(Son->h_CheckIn, SW_HIDE);
	UpdateWindow(Son->h_CheckIn);

	MSG msg;
	while(stateIn == 1){
		GetMessage(&msg, NULL, NULL, NULL);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CMutex mutex;
	mutex.Lock();
	stateIn = 0;
	mutex.Unlock();
	return 1;
}

void CCheckUSB::CheckUSBIn(){
	ifCheckIn = 1;
	//Ĭ����ѭ����
	stateIn = 1;
	DWORD ThreadID = 0;
	Create_Thread(CheckIn,0,ThreadID);
	return;
}

LRESULT CALLBACK WndProcOut(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
	PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
	char driveName;
	CString diskpath = "";

	if(uMsg == WM_DEVICECHANGE){
		if(wParam == DBT_DEVICEREMOVECOMPLETE){
			driveName = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			diskpath.Format("%c:\\",driveName);
			Son->USBOut(diskpath);
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI CheckOut(LPVOID lpParam){
	TCHAR szClassName[] = "USBOut";

	WNDCLASS wndclsOut = {0};
	wndclsOut.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclsOut.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wndclsOut.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
	wndclsOut.lpfnWndProc = WndProcIn;
	wndclsOut.lpszClassName = szClassName;

	if(RegisterClass(&wndclsOut) == 0){
		AfxMessageBox("RegisterClass Failed!\r\n");
		return 0;
	}

	if(Son->h_CheckOut != 0) AfxMessageBox("���д���");
	Son->h_CheckOut = CreateWindow(szClassName,szClassName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,NULL,NULL);
	if(NULL == Son->h_CheckOut){
		AfxMessageBox("CreateWindow Failed!\r\n");
		return 0;
	}
	ShowWindow(Son->h_CheckOut, SW_HIDE);
	UpdateWindow(Son->h_CheckOut);

	MSG msg;
	while(stateOut == 1){
		GetMessage(&msg, NULL, NULL, NULL);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CMutex mutex;
	mutex.Lock();
	stateOut = 0;
	mutex.Unlock();
	return 1;
}

void CCheckUSB::CheckUSBOut(){
	ifCheckOut = 1;
	//Ĭ������ѭ����
	stateOut = 1;
	DWORD ThreadID = 0;
	Create_Thread(CheckOut,0,ThreadID);
	return;
}