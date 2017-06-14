#include "DataWriter.h"
#include "stdafx.h"


void DataWriter::WriteToFile(const std::vector<int> & data, const std::string & outputFileName)
{
	std::ofstream outputFile(outputFileName);
	for (auto el : data)
	{
		outputFile << el << " ";
	}
	outputFile.flush();
}