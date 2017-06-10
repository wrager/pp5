#pragma once
#include <iostream>
#include <vector>
#include <thread>

class CMergeSort
{
public:
	CMergeSort();
	~CMergeSort();
	std::vector<unsigned> MergeTwoArray(const std::vector<unsigned>& firstArr, const std::vector<unsigned>& secondArr);
	void StartMergeSort(std::vector<unsigned>& num);
	std::vector<unsigned> MergeSortParallel(const std::vector<unsigned> & num);
	std::vector<unsigned> MergeSortSequence(const std::vector<unsigned> & num);
};

void StartCalcRank(CMergeSort * mat, std::vector<unsigned>& num);
