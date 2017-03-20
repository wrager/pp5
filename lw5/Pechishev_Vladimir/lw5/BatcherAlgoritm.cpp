#include "stdafx.h"
#include "BatcherAlgoritm.h"
#include <omp.h>


CBatcherAlgoritm::CBatcherAlgoritm()
	: m_array(Array())
{

}

void CBatcherAlgoritm::SortArray(Array const & arr)
{
	std::vector<Array> numbers;

	//#pragma omp parallel for 
	for (int i = 0; i < arr.size(); ++i)
	{
		numbers.push_back({ arr[i] });
	}
	

	while (numbers.size() > 1)
	{
		std::vector<Array> temp;
		#pragma omp parallel for
		for (int index = 0; index < numbers.size(); index += 2)
		{
			if (index == (numbers.size() - 1))
			{
				temp.push_back(numbers[index]);
				break;
			}
			auto leftPart = numbers[index];
			auto rightPart = numbers[index + 1];

			temp.push_back(MergeSort(leftPart, rightPart));
		}

		numbers = temp;
	}
	m_array = *numbers.begin();
}


Array CBatcherAlgoritm::GetSortedArray() const
{
	return m_array;
}

Array CBatcherAlgoritm::MergeSort(Array const & leftPart, Array const & rightPart) const
{
	auto leftIterator = leftPart.begin();
	auto rightIterator = rightPart.begin();
	Array mergedParts;
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
