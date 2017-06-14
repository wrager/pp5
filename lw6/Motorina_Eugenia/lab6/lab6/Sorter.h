#pragma once
#include <thread>

class CSorter
{
public:
	CSorter();
	~CSorter();

	void MergeSort(std::vector<int> & array);
	void MergeSortWithThreads(std::vector<int> & array, size_t threadCount);

private:
	void Sort(size_t begin, size_t end);
	void StartThreads(size_t count);

	std::vector<int> m_array;

};
