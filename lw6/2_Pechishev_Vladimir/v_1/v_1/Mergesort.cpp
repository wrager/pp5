#include "stdafx.h"
#include "MergeSort.h"
#include <thread>


CMergeSort::CMergeSort()
	: m_array(std::vector<double>())
{
}


std::vector<double> CMergeSort::GetSortedArray() const
{
	return m_array;
}

void CMergeSort::SetArray(std::vector<double> const & arr)
{
	m_array = arr;
}

void CMergeSort::Sort(bool isParallelMode)
{
	m_isParallelMode = isParallelMode;
	MergeSort(0, m_array.size() - 1);
}

void CMergeSort::MergeSort(size_t left, size_t right)
{
	if (left < right)
	{
		const auto middle = static_cast<size_t>((left + right) / 2);
		const auto hardwareThreadsContextsValid = (right - left + 1 == m_array.size() / std::thread::hardware_concurrency());
		if (m_isParallelMode && hardwareThreadsContextsValid)
		{
			CThreadQueue threadQueue;
			threadQueue.AddThread(std::thread(&CMergeSort::MergeSort, this, left, middle));
			threadQueue.AddThread(std::thread(&CMergeSort::MergeSort, this, middle + 1, right));
			threadQueue.WaitForMultiplyObjects();
		}
		else
		{
			MergeSort(left, middle);
			MergeSort(middle + 1, right);
		}
		Merge(left, middle, right);
	}
}


void CMergeSort::Merge(size_t left, size_t middle, size_t right)
{
	size_t start = middle + 1;
	size_t current = 0;
	size_t end = left;
	std::vector<double> sortedResult(right - left + 1);

	while (end <= middle && start <= right)
	{
		if (m_array[end] <= m_array[start])
		{
			sortedResult[current++] = m_array[end++];
		}
		else
		{
			sortedResult[current++] = m_array[start++];
		}
	}
	while (end <= middle || start <= end)
	{
		if (start <= end)
		{
			sortedResult[current++] = m_array[start++];
		}
		else if (end <= middle)
		{
			sortedResult[current++] = m_array[end++];
		}
	}
	while (--current < sortedResult.size())
	{
		m_array[current + left] = sortedResult[current];
	}
}

