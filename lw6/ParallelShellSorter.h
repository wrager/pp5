#pragma once
#include "SimpleShellSorter.h"

class CParallelShellSorter : public CSimpleShellSorter
{
public:
	CParallelShellSorter(const std::vector<int> & data);	
	void ParallelSort(int h, int n, int i, int nElements);
	virtual std::string ToString() override;
public:
	void ShellSort(int n) override;

protected:
	size_t m_threadsCount;
};