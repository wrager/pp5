#include "stdafx.h"
#include "BatcherCalculator.h"


CBatcherCalculator::CBatcherCalculator(const std::vector<int>& vec)
	: m_numbersArray(vec)
{
}

void CBatcherCalculator::Sort(bool isParallel)
{
	m_isParallelSorting = isParallel;
	StartSort(0, m_numbersArray.size());
}

std::vector<int> CBatcherCalculator::GetResultVec() const
{
	return m_numbersArray;
}

void CBatcherCalculator::Merge(size_t left, size_t size, size_t right)
{
	const auto comparator = [](int &leftValue, int &rightValue) {
		if (leftValue > rightValue)
		{
			std::swap(leftValue, rightValue);
		}
	};

	size_t m = right * 2;
	if (m < size)
	{
		Merge(left, size, m);
		Merge(left + right, size, m);
		for (size_t i = left + right; i + right < left + size; i += m)
		{
			comparator(m_numbersArray[i], m_numbersArray[i + right]);
		}
	}
	else
	{
		comparator(m_numbersArray[left], m_numbersArray[left + right]);
	}
}

void CBatcherCalculator::StartSort(size_t left, size_t right)
{
	if (right > 1)
	{
		size_t m = right / 2;
#pragma omp parallel sections if (m_isParallelSorting)
		{
#pragma omp section
			StartSort(left, m);
#pragma omp section
			StartSort(left + m, m);
		}
		Merge(left, right, 1);
	}
}