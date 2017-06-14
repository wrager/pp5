#include "stdafx.h"
#include <thread>
#include "ThreadPool.h"


ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::AddThread(std::thread &&thread)
{
	m_threads.push_back(std::move(thread));
}

void ThreadPool::WaitThread()
{
	for (auto &thread : m_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}