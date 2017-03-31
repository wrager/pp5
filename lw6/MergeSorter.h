#pragma once
#include <vector>

class CMergeSorter
{
public:
	CMergeSorter(const std::vector<int> & data);
	virtual void Sort(std::vector<int> & values);
	std::vector<int> GetData() const;
protected:
	std::vector<int> m_data;

	virtual void MergeSort(int low, int high);
	virtual void Merge(int low, int middle, int high);
	std::vector<int> helper;
	int number;
};