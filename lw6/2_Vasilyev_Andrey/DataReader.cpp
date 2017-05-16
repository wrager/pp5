#include "DataReader.h"
#include "stdafx.h"

std::vector<int> DataReader::ReadFromFile(const std::string & inputFileName /*= "input.txt"*/)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::ios_base::failure("file not found");
	}

	int val;

	std::vector<int> result;
	while (inputFile >> val)
	{
		result.push_back(val);
	}
	return result;
}