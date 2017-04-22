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
	m_array = { 10, 9, 8,7,6,5,4,3,2,1 };
	m_mergesort.SetArray(m_array);
	auto fourThread = 4;
	double timeForParallelVersionAglorithm = GetCalculatedTime([&]() {m_mergesort.Sort(fourThread); });
	std::cout << "Time parallel algorithm with " << fourThread << " thread: " << timeForParallelVersionAglorithm << std::endl;

	/*auto oneThread = 1;
	double timeForSimpleVersionAglorithm = GetCalculatedTime([&]() {m_mergesort.Sort(oneThread); });
	std::cout << "Time simple algorithm with " << oneThread << " thread: " << timeForSimpleVersionAglorithm << std::endl;*/
}

void CApplication::OutputResults() const
{
	/*auto sortedArray = m_mergesort.GetSortedArray();
	std::ofstream fOut(m_outputPath);
	for (auto const & element : sortedArray)
	{
		fOut << element << " ";
	}*/
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