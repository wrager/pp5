#include "ParallelShellSorter.h"
#include "stdafx.h"

CParallelShellSorter::CParallelShellSorter(const std::vector<int> & data)
	:CShellSorter(data)
{
	m_threadsCount = std::thread::hardware_concurrency();
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
		int t = data[currentItemId];
		int j;
		for (j = currentItemId; j >= h && t < data[j - h]; j -= h)
		{
			data[j] = data[j - h];
		}
		data[j] = t;
	}
}