#pragma once
#include <vector>

class DataReader
{
public:
	static std::vector<int> ReadFromFile(const std::string & inputFileName = "input.txt");
};