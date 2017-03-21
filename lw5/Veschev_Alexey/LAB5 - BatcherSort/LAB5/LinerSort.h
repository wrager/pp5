#pragma once
#include "BatcherSort.h"

class  LinerSort : CBatcherSort
{
public:
	LinerSort(const std::vector<int>& inputMass)
		: CBatcherSort(inputMass)
	{
	}

private:
	void OddEvenMergeSort(int leftOperand, int length) override;
public:
	void Sort() override;
};
