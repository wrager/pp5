#pragma once
#include <thread>

class CSorter
{
public:
	CSorter();
	~CSorter();

	void MergeSort(std::vector<int> & array, size_t begin, size_t end);
	void SortWithThreads(std::vector<int> & array, size_t threadCount);

private:
	void Sort(size_t begin, size_t end);
	void StartThreads(size_t count);
	void WaitThread();

	std::vector<int> m_array;
	std::vector<std::thread> m_threads;
};
