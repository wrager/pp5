#pragma once
#include "MergeSorter.h"
#include <thread>

class CParallelMergeSorter: public CMergeSorter
{
public:
	CParallelMergeSorter(const std::vector<int> & data);

	void Sort(std::vector<int> & values) override;

private:
	void ParallelMergeSort(int low, int high, int level);

	void MergeSort(int low, int high) override;
	void Merge(int low, int middle, int high) override;
	
	std::vector<int> helper;
	int number;
	size_t m_threadsCount;
};