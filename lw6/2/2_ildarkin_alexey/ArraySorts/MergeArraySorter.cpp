#include "stdafx.h"
#include "MergeArraySorter.h"

CMergeArraySorter::CMergeArraySorter(const SortableArray & vec, bool isParallelMode)
	: CBaseArraySorter(vec, isParallelMode)
{
}

ArraySorterPtr CMergeArraySorter::CreateSorter(const SortableArray & vec, bool isParallelMode)
{
	return std::make_unique<CMergeArraySorter>(CMergeArraySorter(vec, isParallelMode));
}

void CMergeArraySorter::Sort()
{
	MergeSort(0, m_result.size() - 1);
}

void CMergeArraySorter::MergeSort(size_t left, size_t right)
{
	if (left < right)
	{
		const auto middle = static_cast<size_t>((left + right) / 2);
		const auto hardwareThreadsContextsValid = (right - left + 1 == m_result.size() / std::thread::hardware_concurrency());
		if (m_isParallelMode && hardwareThreadsContextsValid)
		{
			CThreadPool threadPool;
			threadPool.AddThread(std::thread(&CMergeArraySorter::MergeSort, this, left, middle));
			threadPool.AddThread(std::thread(&CMergeArraySorter::MergeSort, this, middle + 1, right));
			threadPool.WaitForMultiplyObjects();
		}
		else
		{
			MergeSort(left, middle);
			MergeSort(middle + 1, right);
		}
		Merge(left, middle, right);
	}
}

void CMergeArraySorter::Merge(size_t left, size_t middle, size_t right)
{
	size_t start = middle + 1;
	size_t current = 0;
	size_t end = left;
	SortableArray sortedResult(right - left + 1);

	while (end <= middle && start <= right)
	{
		if (m_result[end] <= m_result[start])
		{
			sortedResult[current++] = m_result[end++];
		}
		else
		{
			sortedResult[current++] = m_result[start++];
		}
	}
	while (end <= middle || start <= end)
	{
		if (start <= end)
		{
			sortedResult[current++] = m_result[start++];
		}
		else if (end <= middle)
		{
			sortedResult[current++] = m_result[end++];
		}
	}
	while (--current < sortedResult.size())
	{
		m_result[current + left] = sortedResult[current];
	}
}
