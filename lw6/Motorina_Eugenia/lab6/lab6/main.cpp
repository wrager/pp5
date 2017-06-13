#include "stdafx.h"
#include "Sorter.h"
#include <fstream>

int main()
{
	CSorter sorter;
	std::ifstream input("input.txt");
	std::vector<int> arr;
	while (!input.eof())
	{
		int num;
		input >> num;
		arr.push_back(num);
	}
	sorter.SortWithThreads(arr, 4);
	for (auto &it : arr)
	{
		std::cout << it << ", ";
	}
    return 0;
}

