#include "stdafx.h"
#include "BatcherAlgoritm.h"
#include <omp.h>


CBatcherAlgoritm::CBatcherAlgoritm()
	: m_array(DoubleArray())
{

}

void CBatcherAlgoritm::SortArray(DoubleArray const & arr, unsigned countThread)
{
	std::vector<DoubleArray> numbers;

	#pragma omp parallel for num_threads(countThread) 
	for (int i = 0; i < int(arr.size()); ++i)
	{
		auto num = arr[i];
		#pragma omp critical
		{
			numbers.push_back({ num });
		}
	}
	

	while (numbers.size() > 1)
	{
		std::vector<DoubleArray> temp;
		DoubleArray result;
		#pragma omp parallel for num_threads(countThread) 
		for (int index = 0; index < int(numbers.size()); index += 2)
		{
			if (index == (numbers.size() - 1))
			{
				#pragma omp critical
				{
					temp.push_back(numbers[index]);
				}
				break;
			}
			auto leftPart = numbers[index];
			auto rightPart = numbers[index + 1];

			auto result = MergeSort(leftPart, rightPart);

			#pragma omp critical
			{
				temp.push_back(result);
			}
		}

		numbers = temp;
	}
	m_array = *numbers.begin();
}


DoubleArray CBatcherAlgoritm::GetSortedArray() const
{
	return m_array;
}

DoubleArray CBatcherAlgoritm::MergeSort(DoubleArray const & leftPart, DoubleArray const & rightPart) const
{
	auto leftIterator = leftPart.begin();
	auto rightIterator = rightPart.begin();
	DoubleArray mergedParts;
	while (leftIterator != leftPart.end() || rightIterator != rightPart.end())
	{
		if (rightIterator == rightPart.end())
		{
			mergedParts.push_back(*leftIterator);
			++leftIterator;
		}
		else if (leftIterator == leftPart.end())
		{
			mergedParts.push_back(*rightIterator);
			++rightIterator;
		}
		else if (*leftIterator < *rightIterator)
		{
			mergedParts.push_back(*leftIterator);
			++leftIterator;
		}
		else
		{
			mergedParts.push_back(*rightIterator);
			++rightIterator;
		}
	}
	return mergedParts;
}