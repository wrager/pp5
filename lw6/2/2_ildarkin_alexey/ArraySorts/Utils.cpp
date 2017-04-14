#include "stdafx.h"
#include "Utils.h"

namespace utils
{

std::vector<int> ReadVectorFromFile(const std::string & fileName)
{
	std::ifstream inputFile(fileName);
	std::vector<int> outputVec;
	int element;
	while (!inputFile.eof())
	{
		inputFile >> element;
		outputVec.push_back(element);
	}
	return outputVec;
}

void PrintVector(const std::vector<int>& vec)
{
	for (auto element : vec)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

double NotifyExecutionTime(const std::function<void()> &fn)
{
	auto begin = clock();
	fn();
	auto end = clock();

	return double(end - begin) / CLOCKS_PER_SEC;
}

}