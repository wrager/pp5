// LAB5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "BatcherSort.h"
#include "LinerSort.h"
#include "ParallelSort.h"
#include <ctime>


namespace
{
	std::vector<int> ReadFromFile(const std::string & fileName)
	{
		std::vector<int> mass;
		std::ifstream file(fileName);
		int elem;
		while (!file.eof())
		{
			file >> elem;
			mass.push_back(elem);
		}
		return mass;
	}

	void Sort(const std::string & fileName)
	{
		std::vector<int> mass = ReadFromFile(fileName);
		clock_t begin = clock();
		CParallelSort parallelSort(mass);
		parallelSort.Sort();
		clock_t end = clock();
		double elapsedSecsParallel = double(end - begin) / CLOCKS_PER_SEC;
		
		begin = clock();
		LinerSort linerSort(mass);
		linerSort.Sort();
		end = clock();
		double elapsedSecsLiner = double(end - begin) / CLOCKS_PER_SEC;

		std::cout << "Liner sort: " << elapsedSecsLiner << std::endl;
		std::cout << "Parallel sort: " << elapsedSecsParallel << std::endl;
	}
}
int main()
{
	Sort("array.txt");
    return 0;
}

