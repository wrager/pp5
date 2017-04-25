#include "stdafx.h"
#include "Mergesort.h"


void CMergesort::Sort(DoubleArray & arr)
{
	if (arr.size() == 0)
	{
		return;
	}
	std::vector<DoubleArray> numbers;
	for (unsigned i = 0; i < arr.size(); ++i)
	{
		numbers.push_back({ arr[i] });
	}

	while (numbers.size() > 1)
	{
		std::vector<DoubleArray> temp;
		DoubleArray result;
		for (unsigned index = 0; index < numbers.size(); index += 2)
		{
			if (index == (numbers.size() - 1))
			{
				temp.push_back(numbers[index]);
				break;
			}
			auto leftPart = numbers[index];
			auto rightPart = numbers[index + 1];

			auto result = MergeSort(leftPart, rightPart);

			temp.push_back(result);
		}

		numbers = temp;
	}
	auto temp = *numbers.begin();
	arr.swap(temp);
}


DoubleArray CMergesort::MergeSort(DoubleArray const & leftPart, DoubleArray const & rightPart)
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