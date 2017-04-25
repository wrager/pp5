#pragma once
#include <vector>
#include <thread>

class CThreadPool
{
public:
	CThreadPool() = default;
	void AddThread(std::thread &&thread);
	void WaitForMultiplyObjects();

private:
	std::vector<std::thread> m_threads;
};

