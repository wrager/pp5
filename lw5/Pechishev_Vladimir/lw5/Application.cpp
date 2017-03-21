#include "stdafx.h"
#include "Application.h"
#include "Chronometer.h"


CApplication::CApplication(std::string const & inputPath)
	: m_array(Array())
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
	m_array = { 5,4,3,5,8,6,4,5,8,9,2,3,4,648,4,5,564,6,3,26,4,16,54,89,6,1,8,974,64,67,8,6,498,464,9,516 };
	double timeForParallelVersionAgloritm = GetCalculatedTime([&]() {m_algoritm.SortArray(m_array, 4); });
	std::cout << "Time parallel algoritm with 4 thread: " << timeForParallelVersionAgloritm << std::endl;

	double timeForSimpleVersionAgloritm = GetCalculatedTime([&]() {m_algoritm.SortArray(m_array, 1); });
	std::cout << "Time simple algoritm with 1 thread: " << timeForSimpleVersionAgloritm << std::endl;
}

void CApplication::OutputResults() const
{
	auto sortedArray = m_algoritm.GetSortedArray();
	for (auto elem : sortedArray)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
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

