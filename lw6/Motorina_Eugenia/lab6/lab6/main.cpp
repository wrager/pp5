#include "stdafx.h"
#include "Sorter.h"
#include "ShellSorter.h"
#include <fstream>
#include <cstdio>
#include <ctime>



int main()
{
	CSorter sorter;
	CShellSorter shellSorter;
	std::ifstream input("input.txt");
	std::vector<int> sourceArr;
	std::vector<int> arr;

	std::clock_t startTime;
	double resultTime = 0.0;

	while (!input.eof())
	{
		int num;
		input >> num;
		sourceArr.push_back(num);
	}
	std::cout << "Array size: " << sourceArr.size() << '\n';
	arr = sourceArr;
	startTime = std::clock();
	shellSorter.ShellSortWithThreads(arr);
	resultTime = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	std::cout << "Shell sort with threads time: " << resultTime << '\n';

	arr = sourceArr;
	startTime = std::clock();
	shellSorter.ShellSort(arr);
	resultTime = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	std::cout << "Shell sort time: " << resultTime << '\n';

	arr = sourceArr;
	startTime = std::clock();
	sorter.MergeSort(arr);
	resultTime = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	std::cout << "Merge sort time: " << resultTime << '\n';

	arr = sourceArr;
	startTime = std::clock();
	sorter.MergeSortWithThreads(arr, 4);
	resultTime = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	std::cout << "Merge sort with threads time: " << resultTime << '\n';
    return 0;
}

