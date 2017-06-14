#pragma once
#include <vector>
#include "Sorter.h"


class CSimpleMergeSorter: public CSorter
{
public:
	CSimpleMergeSorter() = default;
	CSimpleMergeSorter(const std::vector<int> & data);
	virtual void Sort() override;
	std::string ToString() override;
protected:
	void MergeSort(int low, int high);
	void Merge(int low, int middle, int high);
	std::vector<int> helper;
};