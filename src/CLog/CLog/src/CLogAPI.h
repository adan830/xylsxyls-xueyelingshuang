#pragma once
#define _CLogAPI
#include "CLog.h"

#ifdef _DEBUG
#pragma comment(lib,"CLogd.lib")
#else
#pragma comment(lib,"CLog.lib")
#endif

const string moduleName = "";
const int sizekb = -1;

#ifdef _DEBUG
const int LOGLEVEL = CLog::logLevel::INFO | CLog::logLevel::DBG | CLog::logLevel::WARNING | CLog::logLevel::ERR | CLog::logLevel::FATAL;
#else
const int LOGLEVEL = CLog::logLevel::INFO | CLog::logLevel::ERR | CLog::logLevel::FATAL;
#endif

//?���ܷ��ڿ��.h�г�ʼ������Ϊ������ͷ�ļ��ж����ȫ�ֱ����������뵽��̬����ȥ�ˣ�֮���ٸ�ͷ�ļ�������Ч
const int logFile = CLog::PrivateCreateLogApi(LOGLEVEL, moduleName, sizekb);