#include <SDKDDKVer.h>
#include "CGetPath.h"
#include <shlobj.h>
#include <afxdlgs.h>

CString CGetPath::GetRegOcxPath(CString classid){
	CString strSubKey;
	HKEY hKey;
	LPBYTE lpData;
	strSubKey.Format(_T("CLSID\\{%s}\\InprocServer32"),classid);
	RegOpenKeyEx(HKEY_CLASSES_ROOT,strSubKey,0,KEY_READ,&hKey);
	DWORD dwType = REG_SZ;
	lpData = new BYTE[1024];
	memset(lpData,0,1024);
	DWORD cbData = 1024;
	RegQueryValueEx(hKey,_T(""),NULL,&dwType,lpData,&cbData);
	CString temp = "";
	temp = lpData;
	CString result = temp.Left(temp.ReverseFind('\\') + 1);
	return result;
}

CString CGetPath::GetCurrentExePath(){
	CString temp = "",result = "";
	TCHAR szFilePath[MAX_PATH + 1] = {};
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	temp = szFilePath;
	result = temp.Left(temp.ReverseFind('\\') + 1);
	return result;
}

CString CGetPath::GetFolderFromWindow(HWND hWnd){
	CString cstrSelectPath;
	BROWSEINFO stBrowseInfo;
	memset(&stBrowseInfo, 0, sizeof(stBrowseInfo));
	stBrowseInfo.hwndOwner = hWnd;
	stBrowseInfo.lpszTitle = _T("��ѡ���ļ���");
	stBrowseInfo.ulFlags = BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST pidl = SHBrowseForFolder(&stBrowseInfo);
	if(pidl){
		TCHAR szfolderPath[MAX_PATH] = {};
		SHGetPathFromIDList(pidl, szfolderPath);
		cstrSelectPath.Format(_T("%s"), szfolderPath);
		LPMALLOC lpMalloc;
		if(SUCCEEDED(SHGetMalloc(&lpMalloc))){
			lpMalloc->Free(pidl);
			lpMalloc->Release();
		}
	}
	return cstrSelectPath;
}

CString CGetPath::GetFileFromWindow(){
	CFileDialog dlg(1,NULL,NULL,OFN_HIDEREADONLY ,"All Files(*.*)|*.*||");
	int x = dlg.DoModal();
	if(x != IDOK) return "-1";
	return dlg.GetPathName();
}

void RecursionFindFile(CString strPath,CString FileStr,vector<CString> *pPathVector,BOOL flag){
	CFileFind finder;
	BOOL IsVisit = finder.FindFile(strPath + _T("\\*.*")) ; //_T()��������ʹϵͳ֧��Unicode����
	//ϵͳ����Щ�ļ��޷����ʣ���ʹfinder���0����ô�����������ѭ��ʱ�ͻᱨ������֮���ϲ��finder������ֵ�ģ�����ֱ�ӷ��ؾ���
	if(IsVisit == 0) return;

	CString         TempFileName   = ""; //��ǰѰ�ҵ����ļ����ļ�����
	BOOL            IfNeedKeepFind = 1 ; //�ж��Ƿ�ѵ�ǰ·��ȫ�����꣬��Ȼ�˳�while

	while(IfNeedKeepFind){
		//�����0˵���Ѿ�ȫ�����꣬����GetFileName();�᷵�ص����ڶ����ҵ����ļ�����֮������õ����һ��������FindNextFile();��һֱ����0��
		IfNeedKeepFind = finder.FindNextFile();
		TempFileName = finder.GetFileName();
		if(TempFileName == "" || TempFileName == "." || TempFileName == "..") continue;
		//if��Ϊ�ж��Ƿ�Ϊ�ļ���
		if(FILE_ATTRIBUTE_DIRECTORY == (GetFileAttributes(finder.GetFilePath()) & FILE_ATTRIBUTE_DIRECTORY)){
			//���ȷʵΪ�ļ�������ļ��о���·������Ҫ�ҵ��ļ�������ȥ
			RecursionFindFile(finder.GetFilePath(),FileStr,pPathVector,flag);
			//�ݹ����֮��Ӧ��ֱ�ӽ�����һ�β�ѯ
			continue;
		}
		//ֻ����ȷ�������ļ���֮��ſ����ж��Ƿ�Ϊ��ҪѰ�ҵ��ļ��������ļ����ļ�������
		//1��ʾ���ļ�ȫ��
		if(flag == 1){
			if(TempFileName == FileStr){
				pPathVector->push_back(finder.GetFilePath());
			}
		}
		//2��ʾ���ļ���׺��
		else if(flag == 2){
			if(TempFileName.Mid(TempFileName.ReverseFind('.') + 1) == FileStr) pPathVector->push_back(finder.GetFilePath());
		}
	}
	return;
}

vector<CString> CGetPath::FindFilePath(CString FileStr,CString strPath,BOOL flag){
	if(strPath == ""){
		char szPath[MAX_PATH] = {};
		GetModuleFileName(NULL,szPath,MAX_PATH);//����õ����ǽ���Ŀ¼��ĩβ��exe
		char *temp = _tcsrchr(szPath,'\\'); //������������һ�γ���ָ��'\\'��ָ��
		memset(temp,0,50);
		strPath = szPath;
	}
	vector<CString> VecPath;
	RecursionFindFile(strPath,FileStr,&VecPath,flag); //strPathΪ��ǰ����·�����ϲ�Ŀ¼
	return VecPath;
}