#pragma once
#include "IArraySorter_fwd.h"

class IArraySorter
{
public:
	virtual ~IArraySorter() = default;
	virtual void Sort() = 0;
	virtual SortableArray GetResult()const = 0;
};