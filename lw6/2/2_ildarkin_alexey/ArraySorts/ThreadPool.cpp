#include "stdafx.h"
#include "ThreadPool.h"

void CThreadPool::AddThread(std::thread &&thread)
{
	m_threads.push_back(std::move(thread));
}

void CThreadPool::WaitForMultiplyObjects()
{
	for (auto &thread : m_threads)
	{
		thread.join();
	}
}
