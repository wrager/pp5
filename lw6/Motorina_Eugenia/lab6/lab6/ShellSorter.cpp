#include "stdafx.h"
#include "ThreadPool.h"
#include "ShellSorter.h"

CShellSorter::CShellSorter()
{
}

CShellSorter::~CShellSorter()
{
}

void CShellSorter::ShellSort(std::vector<int> & array)
{
	m_array = array;
	for (size_t i = m_array.size() / 2; i > 0; i /= 2)
	{
		Sort(i);
	}
	array = m_array;
}

void CShellSorter::ShellSortWithThreads(std::vector<int> & array)
{
	m_array = array;
	ThreadPool threadPool;
	for (size_t i = m_array.size() / 2; i > 0; i /= 2)
	{
		threadPool.AddThread(std::thread(boost::bind(&CShellSorter::Sort, this, i)));
	}
	threadPool.WaitThread();
	array = m_array;
}

void CShellSorter::Sort(size_t increment)
{
	size_t j = 0;
	int temp = 0;
	for (size_t i = increment; i < m_array.size(); i++)
	{
		temp = m_array[i];
		for (j = i; j >= increment && temp < m_array[j - increment]; j -= increment)
		{
			m_array[j] = m_array[j - increment];
		}
		m_array[j] = temp;
	}
}
