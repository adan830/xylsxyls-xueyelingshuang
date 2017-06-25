#include <SDKDDKVer.h>
#include "Manager.h"
#include "Collect.h"
#include "ErrorInfo.h"
#include <afxwin.h>
#include "Storage.h"
#include "CCharset/CCharsetAPI.h"

int Manager::Check(HWND hwnd, Person* person){
    return Collect::GetPersonInfo(person, hwnd);
}

int Manager::Query(HWND hwnd, Person* person){
    return Collect::GetQueryInfo(person, hwnd);
}

void Manager::ShowError(int error){
	if (error != 0)
	{
		AfxMessageBox(CCharset::AnsiToUnicode(GetError(error, string)).c_str());
	}
}

void Manager::ShowPerson(HWND hwnd, Person* person){
    Storage::GetFromtxt(person);
	if (person->name == "-1")
	{
		AfxMessageBox(_T("���޴���"));
	}
	else
	{
		Collect::ShowPerson(person, hwnd);
	}
}

void Manager::SavePerson(Person* person){
    Storage::SaveTotxt(person);
	AfxMessageBox(_T("�洢�ɹ�"));
	Manager::SendToQueryRefresh();
}

void Manager::DeletePerson(const Person& person)
{
	Storage::DeleteIntxt(person);
	AfxMessageBox(_T("�����ѱ�ɾ��"));
	Manager::SendToQueryRefresh();
}

void Manager::SendToQueryRefresh()
{
	HWND receiveWindow = ::FindWindow(NULL, _T("��ѯ1.0"));
	if (receiveWindow == NULL)
	{
		return;
	}
	::SendMessage(receiveWindow, WM_COPYDATA, (WPARAM)NULL/*m_hWnd*/, (LPARAM)&COPYDATASTRUCT());
}