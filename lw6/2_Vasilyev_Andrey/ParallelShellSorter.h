#pragma once
#include "SimpleShellSorter.h"

class CParallelShellSorter : public CSimpleShellSorter
{
public:
	CParallelShellSorter() = default;
	CParallelShellSorter(const std::vector<int> & data);	

public:
	void Sort() override;
	std::string ToString() override;

private:
	void ParallelSort(int h, int n, int i, int nElements);
	size_t m_threadsCount;
};