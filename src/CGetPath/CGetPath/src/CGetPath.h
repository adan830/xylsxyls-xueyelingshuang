#pragma once
#include <afxwin.h>
#include "CGetPathMacro.h"
#include <vector>
using namespace std;

class CGetPathAPI CGetPath{
public:
	//����ocx����·������\����
	CString GetRegOcxPath(CString classid);
	//���ر���������·������\����
	CString GetCurrentExePath();
	//ͨ�����ڻ�ȡ�ļ���·�������ܻ�ȡ�ļ�·��
	CString GetFolderFromWindow(HWND hWnd);
	//�������ѡȡ�ļ���ȡ�ļ�·�����ɹ����ؾ���·����ʧ�ܷ���CString�ַ���-1
	CString GetFileFromWindow();
	//FileStr���ļ������׺�������㣬�������ļ��У��õ��ľ���·���ŵ�vector���������ǵݹ麯��
	//strPath��������봫�ļ��У�Ѱ���ļ������£����������Ѱ�ҵ�ǰ·�������µ������ļ���
	//flag = 1��ʾ�����ļ���2��ʾ�����ļ���׺��
	vector<CString> FindFilePath(CString FileStr,CString strPath = "",BOOL flag = 1);
};