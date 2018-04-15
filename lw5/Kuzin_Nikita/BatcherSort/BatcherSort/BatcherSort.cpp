#include "stdafx.h"
#include "BatcherSort.h"


CBatcherSort::CBatcherSort(std::string inputFilename, std::string outputFilename)
	: m_input(inputFilename), m_output(outputFilename)
{
}

void CBatcherSort::Execute()
{
	BatcherSort(ReadStart());
	WriteResult(m_startVec);
}

std::vector<int> CBatcherSort::ReadStart()
{
	std::ifstream in(m_input);
	std::vector<int> temp;
	int num;
	while (in >> num)
	{
		temp.push_back(num);
	}
	in.close();
	return temp;
}

void CBatcherSort::WriteResult(std::vector<int> result)
{
	std::ofstream out(m_output);
	for (auto num : result)
	{
		out << num << std::endl;
	}
	out.close();
}

void CBatcherSort::BatcherSort(std::vector<int> & source)
{
	m_startVec = source;
	OddEvenMergeSort(0, (int) m_startVec.size());
}

void  CBatcherSort::OddEvenMergeSort(int pos, int count)
{
	if (count > 1)
	{
		int half = count / 2;
#pragma omp parallel sections
		{
#pragma omp section
			OddEvenMergeSort(pos, half);
#pragma omp section
			OddEvenMergeSort(pos + half, half);
		}
		OddEvenMerge(pos, count, 1);
	}
}

void  CBatcherSort::OddEvenMerge(int pos, int count, int compareDistance)
{
	int counter = compareDistance * 2;
	if (counter < count)
	{
		OddEvenMerge(pos, count, counter);
		OddEvenMerge(pos + compareDistance, count, counter);
		for (int i = pos + compareDistance; i + compareDistance<pos + count; i += counter)
			Compare(i, i + compareDistance);
	}
	else
		Compare(pos, pos + compareDistance);
}

void  CBatcherSort::Compare(int i, int j)
{
	if (m_startVec[i] > m_startVec[j]) {
		std::swap(m_startVec[i], m_startVec[j]);
	}
}

