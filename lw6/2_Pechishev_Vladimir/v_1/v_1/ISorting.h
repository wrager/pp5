#pragma once
#include "stdafx.h"

struct ISorting
{
	virtual void Sort(size_t countThread) = 0;
	virtual DoubleArray GetSortedArray() const = 0;
};
