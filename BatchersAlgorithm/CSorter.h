#pragma once
#include <vector>

class COddEvenMergeSorter
{
public:
	COddEvenMergeSorter(const std::vector<int> & data);
	void Sort();

private:
	void OddEvenMergeSort(int lo, int n);
	void OddEvenMerge(int lo, int n, int r);
	void Compare(int i, int j);
	void Exchange(int i, int j);

private:
	std::vector<int> m_data;
};