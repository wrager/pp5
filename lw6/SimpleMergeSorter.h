#pragma once
#include <vector>
#include "Sorter.h"


class CSimpleMergeSorter: public CSorter
{
public:
	CSimpleMergeSorter(const std::vector<int> & data);
	virtual void Sort() override;
	virtual std::string ToString() override;

	std::vector<int> GetData() const;
protected:
	virtual void MergeSort(int low, int high);
	virtual void Merge(int low, int middle, int high);
	std::vector<int> helper;
};