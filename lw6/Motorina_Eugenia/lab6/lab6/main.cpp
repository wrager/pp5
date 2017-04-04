#include "stdafx.h"
#include "Sorter.h"


int main()
{
	CSorter sorter;
	std::vector<int> a = {9, 8, 6, 4, 7, 2, 3, 1, 54};
	sorter.MergeSort(a, 0, a.size() - 1);

	for (auto &it : a)
	{
		std::cout << it << ", ";
	}
    return 0;
}

