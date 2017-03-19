#pragma once
#include "stdafx.h"
#include "BatcherAlgoritm.h"


class CApplication
{
public:
	CApplication() = default;
	CApplication(std::string && inputPath);
	
	void SortArray();
	void OutputResults() const;

private:
	void ReadArrayFromFile();

private:
	std::shared_ptr<std::ifstream> m_inputFile;
	Array m_array;

	CBatcherAlgoritm m_algoritm;
};

