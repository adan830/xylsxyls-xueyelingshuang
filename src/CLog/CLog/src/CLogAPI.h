#pragma once
#define _CLogAPI
#include "CLog.h"

#ifdef _DEBUG
#pragma comment(lib,"CLogd.lib")
#else
#pragma comment(lib,"CLog.lib")
#endif

extern CLog logFile;

//?��cpp�ж���
//?CLog logFile(DEBUGLOGLEVEL, "CLogEXE", 10 * 1024);