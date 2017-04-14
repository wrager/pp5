#include "stdafx.h"
#include "AsyncManager.h"


AsyncManager::AsyncManager()
	: m_maxThreadcount(4)
	, m_threadCount(0)
	, m_isWorking(false)
{
}


AsyncManager::~AsyncManager()
{
	Stop();
}

void AsyncManager::OnTaskAdd()
{
	m_threadCount.fetch_add(TASK_WEIGHT);
}

void AsyncManager::OnTaskDone()
{
	m_threadCount.fetch_sub(TASK_WEIGHT);
}

void AsyncManager::Post(TaskBody const& task)
{
	AddCallbackToTask(task);
}

void AsyncManager::Run()
{
	if (!m_isWorking.load())
	{
		m_isWorking.exchange(true);
		StartWork();
	}
}

void AsyncManager::Stop()
{
	m_isWorking.exchange(false);
	for (auto& it : m_threads)
	{
		if (it.joinable())
		{
			it.join();
		}
	}
}

void AsyncManager::AddCallbackToTask(TaskBody const & task)
{
	OnTaskAdd();
	std::function<void()> callbackTask = [this, task]() 
	{
		try
		{
			task();
		}
		catch (...)
		{
		}
		OnTaskDone();
	};
	m_taskMutex.lock();
	m_tasks.push_back(callbackTask);
	m_taskMutex.unlock();
}

void AsyncManager::StartWork()
{
	m_threads.clear();
	m_threads.resize(m_maxThreadcount);
	for (size_t i = 0; i < size_t(m_maxThreadcount); ++i)
	{
		m_threads[i] = std::thread(boost::bind(&AsyncManager::WorkThreadLoop, this));
	}
}

void AsyncManager::WorkThreadLoop()
{
	while (m_isWorking.load())
	{
		TaskBody task;
		if (TryPopTask(task))
		{
			task();
		}
	}
}

bool AsyncManager::TryPopTask(TaskBody & task)
{
	bool result = false;
	m_taskMutex.lock();
	if (!m_tasks.empty())
	{
		task = m_tasks.back();
		m_tasks.pop_back();
		result = true;
	}
	m_taskMutex.unlock();
	return result;
}
