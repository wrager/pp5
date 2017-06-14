// Lab5MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sorter.h"

int main(int argc, char * argv[])
{

	if (argc < 2)
		return 1;
	std::ifstream input(argv[1]);

	std::vector<int> numVec;

	for (; !input.eof();)
	{
		int num;
		input >> num;
		numVec.push_back(num);
	}

	std::vector<std::vector<int>> myVec;
	for (auto &elem : numVec)
	{
		myVec.push_back(std::vector<int>());
		myVec.back().push_back(elem);
	}
	auto start = std::chrono::system_clock::now();
	auto result = Sorter::MergeSort(myVec);
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> dif = end - start;
	std::cout << "Time " << dif.count() << std::endl;
    return 0;
}

