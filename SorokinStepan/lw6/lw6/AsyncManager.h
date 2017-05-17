#pragma once
#include "IAsyncManager.h"

class AsyncManager : public IAsyncManager
{
public:
	static const int TASK_WEIGHT = 1;

	AsyncManager();
	~AsyncManager();

	void OnTaskAdd();
	void OnTaskDone();

	void Post(TaskBody const& task) override;

	void Run();
	void Stop();

	void SetThreadCount(int count);

private:
	void AddCallbackToTask(TaskBody const& task);
	void StartWork();

	void WorkThreadLoop();

	bool TryPopTask(TaskBody & task);

	std::atomic<int> m_threadCount;
	int m_maxThreadcount;

	std::vector<TaskBody> m_tasks;
	std::mutex m_taskMutex;

	std::atomic<bool> m_isWorking;

	std::vector<std::thread> m_threads;
};

