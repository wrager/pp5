#pragma once

class CShellSorter
{
public:
	CShellSorter();
	~CShellSorter();

	void ShellSort(std::vector<int> & array);
	void ShellSortWithThreads(std::vector<int> & array);

private: 
	void Sort(size_t increment);

	std::vector<int> m_array;
};
