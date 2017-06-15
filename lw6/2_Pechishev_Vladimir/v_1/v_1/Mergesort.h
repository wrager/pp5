#pragma once
#include <vector>
#include "ThreadQueue.h"


class CMergeSort
{
public:
	CMergeSort();
	~CMergeSort() = default;

	std::vector<double> GetSortedArray() const;
	void SetArray(std::vector<double> const & arr);
	void Sort(bool isParallelMode);
private:
	void MergeSort(size_t left, size_t right);
	void Merge(size_t left, size_t middle, size_t right);

	std::vector<double> m_array;
	bool m_isParallelMode;
};

