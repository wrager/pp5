#pragma once
#include <vector>

class DataWriter
{
public:
	static void WriteToFile(const std::vector<int> & data, const std::string & outputFileName = "output.txt");
};