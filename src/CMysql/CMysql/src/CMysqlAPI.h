#pragma once
#define _CMysqlAPI
#include "CMysql.h"

#ifdef _DEBUG
#pragma comment(lib,"CMysqld.lib")
#else
#pragma comment(lib,"CMysql.lib")
#endif