#pragma once
#include "stdafx.h"
#include "ParallelSort.h"


class CApplication
{
public:
	CApplication() = default;
	CApplication(std::string const & inputPath, std::string const & outputPath);
	
	void SortArray();
	void OutputResults() const;

private:
	void ReadArrayFromFile();

private:
	std::string m_outputPath;
	std::shared_ptr<std::ifstream> m_inputFile;
	DoubleArray m_array;

	CParallelSort m_mergesort;
};

