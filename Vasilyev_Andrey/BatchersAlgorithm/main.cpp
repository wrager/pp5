#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include "CSorter.h"
#include "CUtils.h"
#include "CParallelSorter.h"


int main()
{
	std::vector<int> vec = CUtils::InitializeVector(32768);
	COddEvenMergeSorter sorter(vec);
	sorter.CheckCalculatingTime();

	CParallelSorter sorter2(vec);
	sorter2.CheckCalculatingTime();

	return 0;
}