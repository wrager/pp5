#include "stdafx.h"
#include "Application.h"


CApplication::CApplication(std::string && inputPath)
{
	m_inputFile = std::make_shared<std::ifstream>(inputPath);
	if (!m_inputFile)
	{
		std::cerr << "Input file not found" << std::endl;
		throw std::runtime_error("file not found");
	}
	ReadArrayFromFile();
}

void CApplication::SortArray()
{
	m_algoritm.SortArray(m_array);
}

void CApplication::OutputResults() const
{
	auto sortedArray = m_algoritm.GetSortedArray();
}

void CApplication::ReadArrayFromFile()
{
	while (!(m_inputFile->eof()))
	{
		float value;
		*m_inputFile >> value;
		m_array.push_back(value);
	}
}

