#pragma once
#include <windows.h>
#include <string>
#include "CSystemMacro.h"
using namespace std;

class CSystemAPI CSystem{
public:
	//?ʵ��CPU��Ƶ
	static double GetCPUSpeedGHz();
	//?��ȡϵͳ���������δ�С
	static RECT GetTaskbarRect();
	//?��ȡ��Ļ�ֱ���
	static RECT GetWindowResolution();
	//?��ȡȥ����������������ʱ���������������Ļ�߶�
	static int GetVisibleHeight();
	//?��ƽ̨Sleep������
	static void Sleep(long long milliseconds);
	//?����UUID������1��ʾ��-����0��ʾ����
	static string uuid(int flag = 1);
    //?��ϵͳ�ļ���
    static void OpenFolder(const string& folder);
    //?��ϵͳ�ļ��в�ѡ���ļ�
    static void OpenFolderAndSelectFile(const string& file);
    //?�ⲿ���ļ�
    static void OpenFile(const string& file);
    //?�ⲿ����ҳ
    static void OpenWebPage(const string& webPage);
	//?�����ļ�
	static void CopyFileOver(const string& dstFile, const string& srcFile, bool over);
    //?��ȡ��ǰ����ϵͳλ��
    static int GetSystemBits();
    //?�����ض���
    static void ForbidRedir();
    //?�ָ��ض���
    static void RecoveryRedir();

public:
    static bool ifRedirFrobid;
    static PVOID oldValue;
};;