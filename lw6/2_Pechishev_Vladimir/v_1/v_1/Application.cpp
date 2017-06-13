#include "stdafx.h"
#include "Application.h"
#include "Chronometer.h"


CApplication::CApplication(std::string const & inputPath, std::string const & outputPath)
	: m_array(DoubleArray())
	, m_outputPath(outputPath)
	
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
	m_sorted.SetArray(m_array);
	double timeForParallelVersionAglorithm = GetCalculatedTime([&]() {m_sorted.Sort(true); });
	std::cout << "Time parallel algorithm: " << timeForParallelVersionAglorithm << std::endl;

	m_sorted.SetArray(m_array);
	double timeForSimpleVersionAglorithm = GetCalculatedTime([&]() {m_sorted.Sort(false); });
	std::cout << "Time simple algorithm: " << timeForSimpleVersionAglorithm << std::endl;
}

void CApplication::OutputResults() const
{
	auto sortedArray = m_sorted.GetSortedArray();
	std::ofstream fOut(m_outputPath);
	for (auto const & element : sortedArray)
	{
		fOut << element << " ";
	}
}

void CApplication::ReadArrayFromFile()
{
	while (!(m_inputFile->eof()))
	{
		double value;
		*m_inputFile >> value;
		m_array.push_back(value);
	}
}