#include "stdafx.h"
#include "merge.cpp"

int main(int argc, char *argv[])
{
	Merge merge;
	ArrayManager array;
	
	if (argc > 1)
	{
		std::vector<int> v = array.FillArray(std::string(argv[1]));
		clock_t time = clock();
		merge.MergeSorting(v, 0, (v.size() - 1));
		time = clock();
		std::cout << "Manipulation time " << ((float)time) / CLOCKS_PER_SEC << " sec" << std::endl;

		for (const int &a : v) {
			std::cout << a << " ";
		}

		std::cout << std::endl;
	}
	else
	{
		std::cout << "not enough arguments. Example: mergesort.exe FileName.txt" << std::endl;
	}
	return 0;
}