#include "stdafx.h"
#include "ThreadQueue.h"

void CThreadQueue::AddThread(std::thread && thread)
{
	m_threads.push_back(std::move(thread));
}

void CThreadQueue::WaitForMultiplyObjects()
{
	for (auto & thread : m_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}
