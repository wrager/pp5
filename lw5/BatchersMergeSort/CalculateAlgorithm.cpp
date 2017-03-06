#include "stdafx.h"
#include "CalculateAlgorithm.h"

CCalculateAlgorithm::CCalculateAlgorithm(const std::vector<int> & vec)
	:m_vec(vec)
{
}

CCalculateAlgorithm::~CCalculateAlgorithm()
{
}

void CCalculateAlgorithm::BatchersMergeSort(size_t left, size_t right)
{
	if (right > 1)
	{
		size_t middle = (right - left) / 2;

		BatchersMergeSort(left, middle);
		BatchersMergeSort(left + middle, middle);

		BatchersMerge(left, right, 1);
	}
}

void CCalculateAlgorithm::BatchersMerge(size_t left, size_t size, size_t right)
{
	size_t middle = right * 2;
	if (middle < size)
	{
		BatchersMerge(left, size, middle);
		BatchersMerge(left + right, size, middle);
		for (size_t i = left + right; i + right < left + size; i += middle)
			CompareAndSwap(i, i + right);
	}
	else
	{
		CompareAndSwap(left, left + right);
	}
}

std::vector<int> CCalculateAlgorithm::GetVec()
{
	return m_vec;
}

void CCalculateAlgorithm::CompareAndSwap(size_t i, size_t j)
{
	if (m_vec[i] > m_vec[j])
		std::swap(m_vec[i], m_vec[j]);
}
