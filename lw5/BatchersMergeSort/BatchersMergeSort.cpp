// BatchersMergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CalculateAlgorithm.h"

void PrintVector(const std::vector<int>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

int main()
{
	CCalculateAlgorithm calc({ 6,2,7,1 });
	calc.BatchersMergeSort(0, 4);
	PrintVector(calc.GetVec());
    return EXIT_SUCCESS;
}

