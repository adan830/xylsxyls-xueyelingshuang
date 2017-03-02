#pragma once
#include <string>
#include <mutex>
#include "CLogMacro.h"
using namespace std;

#define DEBUGLOGLEVEL CLog::logLevel::INFO | CLog::logLevel::DBG | CLog::logLevel::WARNING | CLog::logLevel::ERR | CLog::logLevel::FATAL
#define RELEASELOGLEVEL CLog::logLevel::INFO | CLog::logLevel::ERR | CLog::logLevel::FATAL

#ifdef _DEBUG
#define LOGINIT(moduleName) CLog logFile(DEBUGLOGLEVEL, moduleName);
#define LOGINITKB(moduleName, sizekb) CLog logFile(DEBUGLOGLEVEL, moduleName, sizekb);
#define LOGINITFILE(moduleName) CLog logFile(moduleName, DEBUGLOGLEVEL);
#else
#define LOGINIT(moduleName) CLog logFile(RELEASELOGLEVEL, moduleName);
#define LOGINITKB(moduleName, sizekb) CLog logFile(RELEASELOGLEVEL, moduleName, sizekb);
#define LOGINITFILE(moduleName) CLog logFile(moduleName, RELEASELOGLEVEL);
#endif

#define LOGINFO(format, ...) logFile.Print(CLog::logLevel::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGERROR(format, ...) logFile.Print(CLog::logLevel::ERR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGFATAL(format, ...) logFile.Print(CLog::logLevel::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

class CLogAPI CLog{
public:
	//?��һ��Ϊ��ӡ����־���𣬵ڶ���Ϊ��־��ǰ׺��һ������һ��ǰ׺��������Ϊ��־�ļ���С���ޣ������������ޣ����Ǹ���־�಻����Ϊ��־�����ӡ����
	CLog(int loglevel, const string& moduleName, int sizekb = -1);
	CLog(const string& logPath, int loglevel);

	int loglevel;
	int sizekb;
	int fileNumber;
	void* log;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	std::mutex mutex;
	string fileName;
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
	string ChooseLogFile();
	void Print(logLevel flag, const string& fileMacro, int lineMacro, const char* format, ...);
};