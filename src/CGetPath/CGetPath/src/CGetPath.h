#pragma once
#include <afxwin.h>
#include "CGetPathMacro.h"
#include <vector>
using namespace std;

class CGetPathAPI CGetPath{
public:
	//����ocx����·������\����
	static string GetRegOcxPath(string classid);
	//���ر���������·������\����
    static string GetCurrentExePath();
	//ͨ�����ڻ�ȡ�ļ���·�������ܻ�ȡ�ļ�·������\���ţ�����MFC���
    static string GetFolderFromWindow(HWND hWnd);
	//�������ѡȡ�ļ���ȡ�ļ�·�����ɹ����ؾ���·����ʧ�ܷ���CString�ַ���-1
	static string GetFileFromWindow(HWND hwnd);
#ifdef WTL
    static std::string GetFileFromWindow(HWND hwnd);
#endif
	//FileStr���ļ������׺�������㣬�������ļ��У��õ��ľ���·���ŵ�vector���������ǵݹ麯��
	//strPath��������봫�ļ��У�Ѱ���ļ������£����������Ѱ�ҵ�ǰ·�������µ������ļ��У�������\\������
	//flag = 1��ʾ�����ļ���2��ʾ�����ļ���׺����3��ʾ���������ļ���FileStr��������
    static vector<string> FindFilePath(string FileStr, string strPath = "", BOOL flag = 1);
	//��ȡ����pid�����������
    static vector<int> GetProcessID(string strProcessName);
	//����pid��ȡ���ھ��
    static HWND GetHwndByProcessId(DWORD dwProcessId);
    //��ȡ�ļ������Ϣ��flag1��ʾ��ȡ�ļ�ȫ����flag2��ʾ��ȡ�ļ���׺����flag3��ʾ��ȡ�ļ�����flag4��ʾ��ȡǰ���·����\\����
    static string GetName(const string& path, int flag);
};