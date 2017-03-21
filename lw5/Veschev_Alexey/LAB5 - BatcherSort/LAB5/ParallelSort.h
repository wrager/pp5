#pragma once
#include "BatcherSort.h"

class CParallelSort : CBatcherSort
{
public:
	CParallelSort(const std::vector<int>& inputMass)
		: CBatcherSort(inputMass)
	{
	}

	void OddEvenMergeSort(int leftOperand, int length) override;
	void Sort() override;
};

