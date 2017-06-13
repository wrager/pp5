#pragma once
#include <vector>
#include <thread>

class CThreadQueue
{
public:
	CThreadQueue() = default;
	void AddThread(std::thread &&thread);
	void WaitForMultiplyObjects();

private:
	std::vector<std::thread> m_threads;
};

