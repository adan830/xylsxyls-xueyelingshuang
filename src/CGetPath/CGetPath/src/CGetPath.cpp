#include <SDKDDKVer.h>
#include "CGetPath.h"
#include <shlobj.h>
#include <Tlhelp32.h>
#include "CStringManager/CStringManagerAPI.h"
#include <afxdlgs.h>

string CGetPath::GetRegOcxPath(string classid){
	string strSubKey;
	HKEY hKey;
	LPBYTE lpData;
	CStringManager::Format(strSubKey,_T("CLSID\\{%s}\\InprocServer32"), classid);
	RegOpenKeyEx(HKEY_CLASSES_ROOT,strSubKey.c_str(),0,KEY_READ,&hKey);
	DWORD dwType = REG_SZ;
	lpData = new BYTE[1024];
	memset(lpData,0,1024);
	DWORD cbData = 1024;
	RegQueryValueEx(hKey,_T(""),NULL,&dwType,lpData,&cbData);
	string temp = "";
	temp = (char*)lpData;
	string result = temp.substr(temp.find_last_of('\\') + 1);
	return result;
}

string CGetPath::GetCurrentExePath(){
	string temp = "",result = "";
	TCHAR szFilePath[MAX_PATH + 1] = {};
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	temp = szFilePath;
	result = temp.substr(temp.find_last_of('\\') + 1);
	return result;
}

string CGetPath::GetFolderFromWindow(HWND hWnd){
	string cstrSelectPath;
	BROWSEINFO stBrowseInfo;
	memset(&stBrowseInfo, 0, sizeof(stBrowseInfo));
	stBrowseInfo.hwndOwner = hWnd;
	stBrowseInfo.lpszTitle = _T("��ѡ���ļ���");
	stBrowseInfo.ulFlags = BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST pidl = SHBrowseForFolder(&stBrowseInfo);
	if(pidl){
		TCHAR szfolderPath[MAX_PATH] = {};
		SHGetPathFromIDList(pidl, szfolderPath);
		CStringManager::Format(cstrSelectPath, _T("%s"), szfolderPath);
		LPMALLOC lpMalloc;
		if(SUCCEEDED(SHGetMalloc(&lpMalloc))){
			lpMalloc->Free(pidl);
			lpMalloc->Release();
		}
	}
	if (cstrSelectPath != "") cstrSelectPath = cstrSelectPath + "\\";
	return cstrSelectPath;
}

string CGetPath::GetFileFromWindow(){
	CFileDialog dlg(1,NULL,NULL,OFN_HIDEREADONLY ,"All Files(*.*)|*.*||");
	int x = dlg.DoModal();
	if(x != IDOK) return "-1";
	return (LPSTR)(LPCTSTR)dlg.GetPathName();
}

void RecursionFindFile(string strPath,string FileStr,vector<string> *pPathVector,BOOL flag){
	CFileFind finder;
	BOOL IsVisit = finder.FindFile((strPath + "\\*.*").c_str()); //_T()��������ʹϵͳ֧��Unicode����
	//ϵͳ����Щ�ļ��޷����ʣ���ʹfinder���0����ô�����������ѭ��ʱ�ͻᱨ������֮���ϲ��finder������ֵ�ģ�����ֱ�ӷ��ؾ���
	if(IsVisit == 0) return;

	string          TempFileName   = ""; //��ǰѰ�ҵ����ļ����ļ�����
	BOOL            IfNeedKeepFind = 1 ; //�ж��Ƿ�ѵ�ǰ·��ȫ�����꣬��Ȼ�˳�while

	while(IfNeedKeepFind){
		//�����0˵���Ѿ�ȫ�����꣬����GetFileName();�᷵�ص����ڶ����ҵ����ļ�����֮������õ����һ��������FindNextFile();��һֱ����0��
		IfNeedKeepFind = finder.FindNextFile();
		TempFileName = finder.GetFileName();
		if(TempFileName == "" || TempFileName == "." || TempFileName == "..") continue;
		//if��Ϊ�ж��Ƿ�Ϊ�ļ���
		if(FILE_ATTRIBUTE_DIRECTORY == (GetFileAttributes(finder.GetFilePath()) & FILE_ATTRIBUTE_DIRECTORY)){
			//���ȷʵΪ�ļ�������ļ��о���·������Ҫ�ҵ��ļ�������ȥ
			RecursionFindFile((LPSTR)(LPCTSTR)finder.GetFilePath(),FileStr,pPathVector,flag);
			//�ݹ����֮��Ӧ��ֱ�ӽ�����һ�β�ѯ
			continue;
		}
		//ֻ����ȷ�������ļ���֮��ſ����ж��Ƿ�Ϊ��ҪѰ�ҵ��ļ��������ļ����ļ�������
		//1��ʾ���ļ�ȫ��
		if(flag == 1){
			if(TempFileName == FileStr){
				pPathVector->push_back((LPSTR)(LPCTSTR)finder.GetFilePath());
			}
		}
		//2��ʾ���ļ���׺��
		else if(flag == 2){
			if(TempFileName.substr(TempFileName.find_last_of('.') + 1,TempFileName.length() - TempFileName.find_last_of('.') - 1) == FileStr) pPathVector->push_back((LPSTR)(LPCTSTR)finder.GetFilePath());
		}
	}
	return;
}

vector<string> CGetPath::FindFilePath(string FileStr,string strPath,BOOL flag){
	if(strPath == ""){
		char szPath[MAX_PATH] = {};
		GetModuleFileName(NULL,szPath,MAX_PATH);//����õ����ǽ���Ŀ¼��ĩβ��exe
		char *temp = _tcsrchr(szPath,'\\'); //������������һ�γ���ָ��'\\'��ָ��
		memset(temp,0,50);
		strPath = szPath;
	}
	vector<string> VecPath;
	RecursionFindFile(strPath,FileStr,&VecPath,flag); //strPathΪ��ǰ����·�����ϲ�Ŀ¼
	return VecPath;
}

vector<int> CGetPath::GetProcessID(string strProcessName){
	HANDLE myhProcess;
	PROCESSENTRY32 mype;
	mype.dwSize = sizeof(PROCESSENTRY32); 
	BOOL mybRet;
	//���н��̿���
	myhProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); //TH32CS_SNAPPROCESS�������н���
	//��ʼ���̲���
	mybRet = Process32First(myhProcess,&mype);
	vector<int> vec;
	//ѭ���Ƚϣ��ó�ProcessID
	while(mybRet){
		if(strProcessName == mype.szExeFile) vec.push_back(mype.th32ProcessID);
		mybRet = Process32Next(myhProcess,&mype);
	}
	return vec;
}

typedef struct{
	HWND  hWnd ;
	DWORD dwPid;
}WNDINFO;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam){   
	WNDINFO* pInfo = (WNDINFO*)lParam;
	DWORD dwProcessId = 0;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	if(dwProcessId == pInfo->dwPid){
		pInfo->hWnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND CGetPath::GetHwndByProcessId(DWORD dwProcessId){
	WNDINFO info = {0};
	info.hWnd = NULL;
	info.dwPid = dwProcessId;
	EnumWindows(EnumWindowsProc,(LPARAM)&info);
	return info.hWnd;
}