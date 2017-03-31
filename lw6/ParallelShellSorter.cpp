#include "ParallelShellSorter.h"
#include "stdafx.h"

CParallelShellSorter::CParallelShellSorter(const std::vector<int> & data)
	:CSimpleShellSorter(data)
{
	m_threadsCount = std::thread::hardware_concurrency();
}


std::string CParallelShellSorter::ToString()
{
	return "Parallel shellSorter";
}

void CParallelShellSorter::ShellSort(int n)
{
	int h, i, j, t;

	for (h = n; h /= 2;)
	{
		std::vector<std::thread> activeThreads;
		int t;
		int numberOfElementsPerThread = ceil(float(n - h) / m_threadsCount);
		
		for (int i = h; i < n; i+= numberOfElementsPerThread)
		{
			activeThreads.push_back(std::thread(&CParallelShellSorter::ParallelSort, this, h, n, i, numberOfElementsPerThread));	
		}
		for (size_t i = 0; i < activeThreads.size(); ++i)
		{
			activeThreads[i].join();
		}
	}

}

void CParallelShellSorter::ParallelSort(int h, int n, int i, int nElements)
{
	for (int currentItemId = i; currentItemId < n && currentItemId - i < nElements; ++currentItemId)
	{
		int t = m_data[currentItemId];
		int j;
		for (j = currentItemId; j >= h && t < m_data[j - h]; j -= h)
		{
			m_data[j] = m_data[j - h];
		}
		m_data[j] = t;
	}
}