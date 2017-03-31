#pragma once
#include "ShellSorter.h"

class CParallelShellSorter : public CShellSorter
{
public:
	CParallelShellSorter(const std::vector<int> & data);
	void ShellSort(int n) override;
	void ParallelSort(int h, int n, int i, int nElements);
protected:
	size_t m_threadsCount;
};