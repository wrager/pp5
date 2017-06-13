#include "stdafx.h"
#include "Sorter.h"
#include <fstream>
#include <cstdio>
#include <ctime>

int main()
{
	CSorter sorter;
	std::ifstream input("input.txt");
	std::vector<int> arr;
	std::clock_t startTime;
	double resultTime = 0.0;

	while (!input.eof())
	{
		int num;
		input >> num;
		arr.push_back(num);
	}
	startTime = std::clock();
	sorter.SortWithThreads(arr, 4);
	resultTime = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	std::cout << "Time: " << resultTime << '\n';
    return 0;
}

