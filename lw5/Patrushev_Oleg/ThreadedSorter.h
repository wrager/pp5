#pragma once
#include <omp.h>
#include "BatchersMergeSorter.h"

template <typename T>
class CBatchersMergeSorterParallel : public CBatchersMergeSorter<T>
{
public:
	CBatchersMergeSorterParallel(const std::vector<T>& vec)
		: CBatchersMergeSorter<T>(vec)
	{

	}

	void BatchersMergeSort(size_t left, size_t right) override
	{
		if (right > 1)
		{
			size_t m = right / 2;

			#pragma omp parallel sections
			{
				#pragma omp section
				BatchersMergeSort(left, m);
				#pragma omp section
				BatchersMergeSort(left + m, m);
			}
			BatchersMerge(left, right, 1);
		}
	}
};
