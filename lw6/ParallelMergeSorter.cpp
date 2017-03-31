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
	ParallelMergeSort(0, m_data.size() - 1, 0);
}

void CParallelMergeSorter::ParallelMergeSort(int low, int high, int level)
{
	++level;
	if (low < high)
	{
		int minimalThreadCreatingLevel = (int)log2(m_threadsCount);
		if (level <= minimalThreadCreatingLevel)
		{
			int middle = low + (high - low) / 2;
			std::thread thLeft(&CParallelMergeSorter::ParallelMergeSort, this, low, middle, level);
			std::thread thRight(&CParallelMergeSorter::ParallelMergeSort, this, middle + 1, high, level);
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

void CParallelMergeSorter::MergeSort(int low, int high)
{
	if (low < high) 
	{
		int middle = low + (high - low) / 2;
		MergeSort(low, middle);
		MergeSort(middle + 1, high);
		Merge(low, middle, high);
	}
}

void CParallelMergeSorter::Merge(int low, int middle, int high) 
{
	for (int i = low; i <= high; i++) 
	{
		helper[i] = m_data[i];
	}

	int i = low;
	int j = middle + 1;
	int k = low;
	while (i <= middle && j <= high)
	{
		if (helper[i] <= helper[j]) 
		{
			m_data[k] = helper[i];
			i++;
		}
		else 
		{
			m_data[k] = helper[j];
			j++;
		}
		k++;
	}
	while (i <= middle) 
	{
		m_data[k] = helper[i];
		k++;
		i++;
	}
}