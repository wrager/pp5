#pragma once
#include "stdafx.h"


class CMergesort
{
public:
	static void Sort(DoubleArray & arr);
	static DoubleArray MergeSort(DoubleArray const & leftPart, DoubleArray const & rightPart);
};