#pragma once
#include "BaseArraySorter.h"

class CMergeArraySorter
	: public CBaseArraySorter
{
public:
	static ArraySorterPtr CreateSorter(const SortableArray &vec, bool isParallelMode);
	void Sort()override;

private:
	CMergeArraySorter(const SortableArray &vec, bool isParallelMode);

	void MergeSort(size_t left, size_t right);
	void Merge(size_t left, size_t middle, size_t right);
};
