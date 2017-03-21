#pragma once
#include "stdafx.h"

class CBatcherAlgoritm
{
public:
	CBatcherAlgoritm();
	void SortArray(DoubleArray const & arr, unsigned countThread);
	DoubleArray GetSortedArray() const;

private:
	DoubleArray MergeSort(DoubleArray const & leftPart, DoubleArray const & rightPart) const;

private:
	DoubleArray m_array;
};