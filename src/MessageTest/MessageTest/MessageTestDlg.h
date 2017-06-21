
// MessageTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <mutex>
//#include "Controller/ControllerAPI.h"
using namespace std;

typedef struct tagList
{
    tagList* next;
    string str;
}tagList;

class CListMessage
{
public:
    void push_back(string str)
    {
        tagList* ptagList = new tagList;
        ptagList->next = 0;
        ptagList->str = str;
        int last = m_last;
        if (last == 0)
        {
            m_first = (int)ptagList;
            m_last = (int)ptagList;
        }
        else
        {
            ((tagList*)last)->next = ptagList;
            m_last = (int)ptagList;
            if (m_first == 0)
            {
                m_first = (int)m_last;
            }
        }
        ++m_size;
    }
    string pop_front()
    {
        if (m_size >= 2)
        {
            int first = m_first;
            if (first != 0)
            {
                m_first = (int)(((tagList*)first)->next);
                string data = ((tagList*)first)->str;
                delete (tagList*)first;
                --m_size;
                return data;
            }
            return "";
        }
        return "";
    }
    int size()
    {
        return m_size;
    }
    bool empty()
    {
        return m_size == 0;
    }
private:
    atomic<int> m_size;
    atomic<int> m_first;
    atomic<int> m_last;
};

// CMessageTestDlg �Ի���
class CMessageTestDlg : public CDialogEx
{
// ����
public:
	CMessageTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MessageTest_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    enum
    {
        stringover
    };
public:
	afx_msg void OnBnClickedButton1();
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();

public:
    void WorkThread();

public:
    CEdit m_edit;
    CButton m_fileBtn;
    CEdit m_editToFile;

public:
    //��Ļ�ı���ʾ����
    CString windowtext;
    //������
    list<string> listCopyData;
    //������ת�������ַ���
    string showString;
    //�������Ƿ��б䶯�������Ǵ����ļ��������Ǵ�����Ļ��ʾ����
    atomic<bool> bListChangeAmc = false;
    //�����ַ����߳�
    thread* threadWork = nullptr;
    //�߳��Ƿ�����
    atomic<bool> bWorkThreadRunAmc = 0;
    
private:
    void AddListDataLock(const char* szData);
    void UpdateBufferSize();
    void UpdateScreenSize();
    int32_t GetListSizeLock();
    bool IsListEmptyLock();
    string GetPopFrontLock();
    void ShowStringInsertLock(const string& insertData);
    std::string TCHAR2STRING(TCHAR *STR);

private:
    char* szData = nullptr;
    int curDataSize = 0;
    std::mutex mu;
    atomic<int> linesAmc;
    atomic<bool> bToFileAmc = false;
    void* file;
    bool bChangeScreen = false;
public:
    CButton m_btnChange;
};
