#pragma once
#include "stdafx.h"

class CBatcherAlgoritm
{
public:
	CBatcherAlgoritm();
	void SortArray(Array const & arr);
	Array GetSortedArray() const;

private:
	Array MergeSort(Array const & leftPart, Array const & rightPart) const;

private:
	Array m_array;
};

