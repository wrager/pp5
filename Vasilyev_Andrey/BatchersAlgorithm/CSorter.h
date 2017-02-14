#pragma once
#include <vector>
#include <time.h>
#include <iostream>
#include "CUtils.h"

class COddEvenMergeSorter
{
public:
	COddEvenMergeSorter(const std::vector<int> & data);
	virtual void Sort();
	void CheckCalculatingTime();

protected:
	virtual void OddEvenMergeSort(int lo, int n);
	virtual void OddEvenMerge(int lo, int n, int r);
	void Compare(int i, int j);
	void Exchange(int i, int j);

protected:
	std::vector<int> m_data;
};