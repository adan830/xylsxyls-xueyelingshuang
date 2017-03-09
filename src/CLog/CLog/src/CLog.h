#pragma once
#include <string>
#include <mutex>
#include <atomic>
#include "CLogMacro.h"
using namespace std;

#define LOGINFO(format, ...) ((CLog*)(static_cast<int>(logFile)))->Print(CLog::logLevel::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGDEBUG(format, ...) ((CLog*)(static_cast<int>(logFile)))->Print(CLog::logLevel::DBG, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGWARNING(format, ...) ((CLog*)(static_cast<int>(logFile)))->Print(CLog::logLevel::WARNING, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGERROR(format, ...) ((CLog*)(static_cast<int>(logFile)))->Print(CLog::logLevel::ERR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGFATAL(format, ...) ((CLog*)(static_cast<int>(logFile)))->Print(CLog::logLevel::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define LOGINFOEX(log, format, ...) (log)->Print(CLog::logLevel::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGDEBUGEX(log, format, ...) (log)->Print(CLog::logLevel::DBG, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGWARNINGEX(log, format, ...) (log)->Print(CLog::logLevel::WARNING, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGERROREX(log, format, ...) (log)->Print(CLog::logLevel::ERR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGFATALEX(log, format, ...) (log)->Print(CLog::logLevel::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

class CLogAPI CLog{
public:
	static int PrivateCreateLogApi(int loglevel, const string& moduleName, int sizekb);
private:
	//?��һ��Ϊ��ӡ����־���𣬵ڶ���Ϊ��־��ǰ׺��һ������һ��ǰ׺��������Ϊ��־�ļ���С���ޣ������������ޣ����Ǹ���־�಻����Ϊ��־�����ӡ����
	CLog(int loglevel, const string& moduleName, int sizekb);
public:
	//?���Ҫ�Զ�����־·��������ڵ����ļ��ж���һ��CLog��
	CLog(const string& logPath, int loglevel);

	int loglevel;
	int sizekb;
	void* log;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string strPathPre;
	atomic<int> fileNumber;
	std::mutex mutex;
	string fileName;
	//ֻ���Զ������־�Ż���filePath
	string filePath;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	enum logLevel{
		INFO = 0x00000001,
		DBG = 0x00000010,
		WARNING = 0x00000100,
		ERR = 0x00001000,
		FATAL = 0x00010000
	};
	void SaveLogLevel(int loglevel);
	void SaveModuleName(const string& moduleName);
	void SaveSizekb(int sizekb);
	string ChooseLogFile();
	void CheckAndChangeLogFile(const string& strPath);
	void Print(logLevel flag, const string& fileMacro, int lineMacro, const char* format, ...);
};