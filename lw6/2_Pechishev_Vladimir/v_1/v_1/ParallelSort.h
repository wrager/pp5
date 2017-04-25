#pragma once
#include <vector>
#include "ThreadPool.h"


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
	CThreadPool m_pool;
};

