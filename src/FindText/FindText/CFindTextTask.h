#pragma once
#include "CTaskThreadManager/CTaskThreadManagerAPI.h"
#include <string>

class CFindTextDlg;

class CFindTextTask : public CTask
{
public:
	CFindTextTask(const std::string& path, const std::string& key, CFindTextDlg* pFindTextDlg);
public:
	virtual void DoTask();

	void PostToClient();

	//?����·��һ�β���
	void FindFromPath(const std::string& path, const std::string& key);

	//? �����ļ���
	//? path [in] ���ļ���·��
	//? key [in] �����Ĺؼ���
	//? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
	void FindFromFileName(const std::string& path, const std::string& key, bool& bAddFileName);

	//? ���ļ�����
	//? path [in] ���ļ���·��
	//? key [in] �����Ĺؼ���
	//? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
	void OpenFileFind(const std::string& path, const std::string& key, bool& bAddFileName);

	//?��������
	//? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
	void FindEnd(bool& bAddFileName);

	//?��ȡutf-8��ÿ��ƫ��λ��
	//? line [in] �кţ���0��ʼ
	//? oneLine [in] ÿ������
	int GetUtf8Offset(int line, const std::string& oneLine);
	//?��ȡunicode��ÿ��ƫ��λ��
	//? line [in] �кţ���0��ʼ
	//? oneLine [in][out] ÿ�����ݣ�����stringĩβ���һ��\0
	int GetUnicodeOffset(int line, const std::string& oneLine);

	//?���ղ�ͬ�����ʽ����һ�в����
	//? oneLine [in] ��������һ�У�gbk��ʽ
	//? path [in] ���ļ���·��
	//? key [in] �����Ĺؼ���
	//? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
	//? line [in] �к�
	//? addstring [out] Ҫ��ӵ��ַ���
	//? format [in] �������ַ�����ʲô��ʽ��
	//? �����ҵ���λ�ã�0��ʼ
	int FindAdd(const std::string& oneLine, const std::string& path, const std::string& key, bool& bAddFileName, int line, std::string& addstring, const std::string& format);

	//?�ԱȲ�����ַ���
	//? addOffset [in] ��Ҫ��ӵ��ַ����йؼ���ƫ����
	//? addstring [in] ��Ҫ��ӵ��ַ���
	//? showOffset [in] ��Ҫչʾ���ַ�����Ӧ���ҵ��ؼ��ʵ�ƫ����
	//? path [in] ���ļ���·��
	//? bAddFileName [in][out] ��ǰ���������Ƿ��Ѿ�������ļ���һ��
	//? ifCurAdd [in][out] ��ǰ�Ƿ��Ѿ����
	void CompareShowAdd(int addOffset, const std::string& addstring, int showOffset, const std::string& path, bool& bAddFileName, bool& ifCurAdd);

private:
	std::string m_path;
	std::string m_key;
	std::string m_strFind;
	CFindTextDlg* m_pFindTextDlg = nullptr;

};