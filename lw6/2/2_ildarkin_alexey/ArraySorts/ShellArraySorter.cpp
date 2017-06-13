#include "stdafx.h"
#include "ShellArraySorter.h"

CShellArraySorter::CShellArraySorter(const SortableArray & vec, bool isParallelMode)
	: CBaseArraySorter(vec, isParallelMode)
{
}

void CShellArraySorter::ShellIteration(size_t increment)
{
	size_t j = 0;
	for (size_t i = increment; i < m_result.size(); i++)
	{
		int temp = m_result[i];
		for (j = i; j >= increment
			&& temp < m_result[j - increment]; j -= increment)
		{
			m_result[j] = m_result[j - increment];
		}
		m_result[j] = temp;
	}
}

ArraySorterPtr CShellArraySorter::CreateSorter(const SortableArray & vec, bool isParallelMode)
{
	return std::make_unique<CShellArraySorter>(CShellArraySorter(vec, isParallelMode));
}

void CShellArraySorter::Sort()
{
	CThreadPool threadPool;
	for (size_t increment = m_result.size() / 2; increment > 0; increment /= 2)
	{
		if (m_isParallelMode)
		{
			threadPool.AddThread(std::thread(&CShellArraySorter::ShellIteration, this, increment));
		}
		else
		{
			ShellIteration(increment);
		}
	}
	threadPool.WaitForMultiplyObjects();
}
