#pragma once

class CThreadPool
{
public:
	void AddThread(std::thread &&thread);
	void WaitForMultiplyObjects();

private:
	std::vector<std::thread> m_threads;
};