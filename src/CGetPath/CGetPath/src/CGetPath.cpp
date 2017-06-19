#include <SDKDDKVer.h>
#include "CGetPath.h"
#include <shlobj.h>
#include <Tlhelp32.h>
#include "CStringManager/CStringManagerAPI.h"
#include <afxdlgs.h>
#include <afxdisp.h>

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
	char szFilePath[MAX_PATH + 1] = {};
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	temp = szFilePath;
	result = temp.substr(0, temp.find_last_of("/\\") + 1);
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

#define NDEBUG

string CGetPath::GetFileFromWindow(HWND hwnd)
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = _T("�����ļ�(*.*)*.*");//"Exe�ļ�(*.exe)*.exe�����ļ�(*.*)*.*"
	ofn.lpstrInitialDir = _T("");//Ĭ�ϵ��ļ�·�� 
	ofn.lpstrFile = szBuffer;//����ļ��Ļ����� 
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//��־����Ƕ�ѡҪ����OFN_ALLOWMULTISELECT
	BOOL bSel = GetOpenFileName(&ofn);
	return string(szBuffer);
}

#ifdef WTL
std::string RCGetPath::GetFileFromWindow(HWND hwnd){
    wchar_t* filter = L"image files (*.png)\0*.png\0All Files (*.*)\0*.*\0\0";
    CFileDialog dlg(true, 0, 0, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, filter, hwnd);
    if (dlg.DoModal() == IDOK){
        std::wstring ss = dlg.m_szFileName;
        UnicodeToAnsi(ss);
        return UnicodeToAnsi(ss);
    }
    else return "";
}
#endif

void RecursionFindFile(string strPath,string FileStr,vector<string> *pPathVector,BOOL flag){
	CFileFind finder;
    //_T()��������ʹϵͳ֧��Unicode����
	BOOL IsVisit = finder.FindFile((strPath + "\\*.*").c_str());
	//ϵͳ����Щ�ļ��޷����ʣ���ʹfinder���0����ô�����������ѭ��ʱ�ͻᱨ������֮���ϲ��finder������ֵ�ģ�����ֱ�ӷ��ؾ���
	if(IsVisit == 0) return;

    //��ǰѰ�ҵ����ļ����ļ�����
	string TempFileName   = "";
    //�ж��Ƿ�ѵ�ǰ·��ȫ�����꣬��Ȼ�˳�while
	BOOL   IfNeedKeepFind = 1 ;

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
        //3��ʾ���������ļ�����������ȫ����ӽ���
        else if (flag == 3)
        {
            pPathVector->push_back((LPSTR)(LPCTSTR)finder.GetFilePath());
        }
	}
	return;
}

vector<string> CGetPath::FindFilePath(string FileStr,string strPath,BOOL flag){
	if(strPath == ""){
		char szPath[MAX_PATH] = {};
        //����õ����ǽ���Ŀ¼��ĩβ��exe
		GetModuleFileName(NULL,szPath,MAX_PATH);
        //������������һ�γ���ָ��'\\'��ָ��
		char *temp = _tcsrchr(szPath,'\\');
		memset(temp,0,50);
		strPath = szPath;
	}
	vector<string> VecPath;
    //strPathΪ��ǰ����·�����ϲ�Ŀ¼
	RecursionFindFile(strPath,FileStr,&VecPath,flag);
	return VecPath;
}

vector<int> CGetPath::GetProcessID(string strProcessName){
	HANDLE myhProcess;
	PROCESSENTRY32 mype;
	mype.dwSize = sizeof(PROCESSENTRY32); 
	BOOL mybRet;
	//���н��̿���
    //TH32CS_SNAPPROCESS�������н���
	myhProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
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