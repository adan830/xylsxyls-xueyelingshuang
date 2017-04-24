#pragma once
#include <afxwin.h>
#include "CGetPathMacro.h"
#include <vector>
using namespace std;

class CGetPathAPI CGetPath{
public:
	//����ocx����·������\����
	string GetRegOcxPath(string classid);
	//���ر���������·������\����
	string GetCurrentExePath();
	//ͨ�����ڻ�ȡ�ļ���·�������ܻ�ȡ�ļ�·������\���ţ�����MFC���
	string GetFolderFromWindow(HWND hWnd);
	//�������ѡȡ�ļ���ȡ�ļ�·�����ɹ����ؾ���·����ʧ�ܷ���CString�ַ���-1
	string GetFileFromWindow();
#ifdef WTL
    static std::string GetFileFromWindow(HWND hwnd);
#endif
	//FileStr���ļ������׺�������㣬�������ļ��У��õ��ľ���·���ŵ�vector���������ǵݹ麯��
	//strPath��������봫�ļ��У�Ѱ���ļ������£����������Ѱ�ҵ�ǰ·�������µ������ļ��У�������\\������
	//flag = 1��ʾ�����ļ���2��ʾ�����ļ���׺��
	vector<string> FindFilePath(string FileStr,string strPath = "",BOOL flag = 1);
	//��ȡ����pid�����������
	vector<int> GetProcessID(string strProcessName);
	//����pid��ȡ���ھ��
	HWND GetHwndByProcessId(DWORD dwProcessId);
};