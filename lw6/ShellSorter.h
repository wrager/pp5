#pragma once
#include <vector>

class CShellSorter
{
public:
	CShellSorter(const std::vector<int> & data);

	void Sort();
	virtual void ShellSort(int n);
	std::vector<int> GetData() const;

protected:
	std::vector<int> data;
};