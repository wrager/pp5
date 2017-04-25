#pragma once
#include <vector>
#include "ThreadQueue.h"


class CParallelSort
{
public:
	CParallelSort();
	~CParallelSort() = default;

	std::vector<double> GetSortedArray() const;
	void SetArray(std::vector<double> const & arr);
	void Sort(size_t countThread);
private:
	std::vector<double> m_array;
	CThreadQueue m_threadQueue;
};

