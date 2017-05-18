#pragma once
#include "BatchersMergeSorter.h"


template <typename T>
class CBatchersMergeSorterLinear : public CBatchersMergeSorter<T>
{
public: 
	CBatchersMergeSorterLinear(const std::vector<T>& vec)
		: CBatchersMergeSorter<T>(vec)
	{

	}

	void BatchersMergeSort(size_t left, size_t right) override
	{
		if (right > 1)
		{
			size_t m = right / 2;

			BatchersMergeSort(left, m);
			BatchersMergeSort(left + m, m);
			BatchersMerge(left, right, 1);
		}
	}
};
