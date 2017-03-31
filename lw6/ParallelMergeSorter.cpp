#include "ParallelMergeSorter.h"
#include <math.h>
#include <iostream>

CParallelMergeSorter::CParallelMergeSorter(const std::vector<int> & data)
	:CSimpleMergeSorter(data)
{
	m_threadsCount = std::thread::hardware_concurrency();
}

std::string CParallelMergeSorter::ToString()
{
	return "Parallel mergeSorter";
}

void CParallelMergeSorter::Sort()
{
	helper = std::vector<int>(m_data.size());
	ParallelSort(0, m_data.size() - 1, 0);
}

void CParallelMergeSorter::ParallelSort(int low, int high, int level)
{
	++level;
	if (low < high)
	{
		int minimalThreadCreatingLevel = (int)log2(m_threadsCount);
		if (level <= minimalThreadCreatingLevel)
		{
			int middle = low + (high - low) / 2;
			std::thread thLeft(&CParallelMergeSorter::ParallelSort, this, low, middle, level);
			std::thread thRight(&CParallelMergeSorter::ParallelSort, this, middle + 1, high, level);
			thLeft.join();
			thRight.join();

			Merge(low, middle, high);
		}
		else
		{
			MergeSort(low, high);
		}
	}
}