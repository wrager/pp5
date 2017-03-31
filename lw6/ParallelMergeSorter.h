#pragma once
#include "SimpleMergeSorter.h"
#include <thread>

class CParallelMergeSorter: public CSimpleMergeSorter
{
public:
	CParallelMergeSorter(const std::vector<int> & data);

public:
	void Sort() override;
	virtual std::string ToString() override;

private:
	void MergeSort(int low, int high) override;
	void Merge(int low, int middle, int high) override;


private:
	void ParallelMergeSort(int low, int high, int level);

private:
	size_t m_threadsCount;
};