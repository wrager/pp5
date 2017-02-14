#pragma once
#include "CSorter.h"


class CParallelSorter : public COddEvenMergeSorter
{
public:
	CParallelSorter(const std::vector<int> & data);

	void OddEvenMergeSort(int lo, int n) override;
	void OddEvenMerge(int lo, int n, int r) override;
};