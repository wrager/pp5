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
	void ParallelSort(int low, int high, int level);

private:
	size_t m_threadsCount;
};