#include "stdafx.h"
#include "MergeArraySorter.h"
#include "Utils.h"

int main()
{
	auto sorter = CMergeArraySorter::CreateSorter({ 5, 6, 7, 1, 3, 2, 4, 8, 9, 11, 10, 12, -5, -4, -1 }, true);
	sorter->Sort();

	utils::PrintVector(sorter->GetResult());

    return 0;
}

