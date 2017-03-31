#include "DataReader.h"
#include "stdafx.h"

std::vector<int> DataReader::ReadFromFile(const std::string & inputFileName /*= "input.txt"*/)
{
	std::ifstream inputFile(inputFileName);
	int val;

	std::vector<int> result;
	while (inputFile >> val)
	{
		result.push_back(val);
	}
	return result;
}