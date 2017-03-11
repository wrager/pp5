#include "stdafx.h"
#include "Utils.h"

std::vector<int> CUtils::ReadNumbersFromStrm(std::istream & strm)
{
	if (!strm)
	{
		throw std::invalid_argument("Error in CUtils::ReadNumbersFromStrm. Input stream is not valid.");
	}

	std::string buffer;
	std::vector<int> outputVec;

	while (strm >> buffer)
	{
		outputVec.push_back(atoi(buffer.c_str()));
	}

	return outputVec;
}

void CUtils::PrintNumbersArray(const std::vector<int>& vec)
{
	for (int element : vec)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

void CUtils::TryToOpenFileStream(std::ifstream &strm, const std::string & filePath)
{
	strm.open(filePath);
	if (!strm)
	{
		throw std::invalid_argument("Error in CUtils::TryToOpenFileStream. File path \"" + filePath + "\" is not correct.");
	}
}

bool CUtils::StringParallelStatusArgToBool(const std::string & arg)
{
	if (arg == "yes")
	{
		return true;
	}
	else if (arg == "no")
	{
		return false;
	}
	throw std::invalid_argument("Error in CUtils::StringParallelStatusArgToBool. Argument \"" + arg + "\" is not correct.");
}
