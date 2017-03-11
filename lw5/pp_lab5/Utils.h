#pragma once

class CUtils
{
public:
	CUtils() = delete;
	CUtils(const CUtils&) = delete;
	CUtils(CUtils&&) = delete;
	CUtils &operator=(const CUtils&) = delete;
	CUtils &operator=(CUtils&&) = delete;

	static std::vector<int> ReadNumbersFromStrm(std::istream & strm);
	static void PrintNumbersArray(const std::vector<int> & vec);
	static void TryToOpenFileStream(std::ifstream &strm, const std::string & filePath);
	static bool StringParallelStatusArgToBool(const std::string &arg);
};