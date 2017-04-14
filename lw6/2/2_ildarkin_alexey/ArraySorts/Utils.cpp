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

}