#pragma once

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void AddThread(std::thread &&thread);

	void WaitThread();

private:
	std::vector<std::thread> m_threads;
};

