#include "dtwsAccount2.h"
#include <stdint.h>
#include "CTaskThreadManager/CTaskThreadManagerAPI.h"
#include "CTaskFactory.h"



int32_t main()
{
    // ���������̣߳�һ���ǹ����̣߳�һ���Ǽ����߳�
	CTaskThreadManager::Instance().Init(WORK_THREAD);
	CTaskThreadManager::Instance().Init(MONITORING_THREAD);
	
	auto taskThread = CTaskThreadManager::Instance().GetThreadInterface(WORK_THREAD);
	std::shared_ptr<CTask> spTask;
	spTask.reset(new CLoginTask);
	taskThread->PostTask(spTask, 1);

	getchar();
	CTaskThreadManager::Instance().UninitAll();
	return 0;
}