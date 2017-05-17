// lw6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sorter.h"

int main(int argc, char * argv[])
{

	if (argc < 2)
		return 1;
	std::ifstream input(argv[1]);

	std::vector<int> numVec;

	while (!input.eof())
	{
		int num;
		input >> num;
		numVec.push_back(num);
	}

	AsyncManager manager;
	Sorter sorter(manager);
	sorter.SetThreadCount(4);

	sorter.SetArray(numVec);
	auto start = std::chrono::system_clock::now();
	sorter.StartSort();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> dif = end - start;
	std::cout << "Time " << dif.count() << std::endl;
    return 0;
}

