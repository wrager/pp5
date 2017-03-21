#include "stdafx.h"
#include "Application.h"
#include "Chronometer.h"


CApplication::CApplication(std::string const & inputPath, std::string const & outputPath)
	: m_array(Array())
	, m_outputPath(outputPath)
	, m_algoritm(CBatcherAlgoritm())
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

	double timeForParallelVersionAgloritm = GetCalculatedTime([&]() {m_algoritm.SortArray(m_array, 4); });
	std::cout << "Time parallel algoritm with 4 thread: " << timeForParallelVersionAgloritm << std::endl;

	double timeForSimpleVersionAgloritm = GetCalculatedTime([&]() {m_algoritm.SortArray(m_array, 1); });
	std::cout << "Time simple algoritm with 1 thread: " << timeForSimpleVersionAgloritm << std::endl;
}

void CApplication::OutputResults() const
{
	auto sortedArray = m_algoritm.GetSortedArray();
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

