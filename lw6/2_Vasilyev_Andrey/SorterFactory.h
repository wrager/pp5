#pragma once
#include <memory>
#include "ParallelMergeSorter.h"
#include "ParallelShellSorter.h"

class CSorterFactory
{
public:
	static std::unique_ptr<CSorter> CreateSorter(CSorter::Type type, bool isParallel);
};