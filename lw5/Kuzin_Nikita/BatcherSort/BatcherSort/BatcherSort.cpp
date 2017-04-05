#include "stdafx.h"
#include "BatcherSort.h"


CBatcherSort::CBatcherSort(std::string inputFilename, std::string outputFilename)
	: m_input(inputFilename), m_output(outputFilename)
{
}

void CBatcherSort::Execute(SortType type)
{
	if (type == SortType::SIMPLE_MERGE)
	{
		WriteResult(SimpleMergeSort(ReadStart()));
	}
	else
	{
		BatcherSort(ReadStart());
		WriteResult(m_startVec);
	}
}

std::vector<int> CBatcherSort::MergeVectors(std::vector<int> vec1, std::vector<int> vec2)
{
	std::vector<int> resultVec;
	std::reverse(vec1.begin(), vec1.end());
	std::reverse(vec2.begin(), vec2.end());
	while (!vec1.empty() && !vec2.empty())
	{
		if (vec1.back() > vec2.back())
		{
			resultVec.push_back(vec2.back());
			vec2.pop_back();
		}
		else
		{
			resultVec.push_back(vec1.back());
			vec1.pop_back();
		}
	}
	while (!vec1.empty())
	{
		resultVec.push_back(vec1.back());
		vec1.pop_back();
	}
	while (!vec2.empty())
	{
		resultVec.push_back(vec2.back());
		vec2.pop_back();
	}
	return resultVec;
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

std::vector<int> CBatcherSort::SimpleMergeSort(std::vector<int> & source)
{
	std::vector<std::vector<int>> splitedStart;

	for (int i = 0; i < source.size(); i++)
	{
		splitedStart.push_back({ source[i] });
	}
	std::mutex mutex;
	while (splitedStart.size() > 1)
	{
		std::vector<std::vector<int>> temp;
		for (int i = 0; i < splitedStart.size() - 1; i += 2)
		{
			m_simpleThreadPool.emplace_back(std::thread([&] {
				int b = i;
				std::vector<std::vector<int>> result;
				if (b + 1 >= splitedStart.size())
				{
					result.push_back(splitedStart[b]);
				}
				else if (b + 1 < splitedStart.size())
				{
					result.push_back(MergeVectors(splitedStart[b], splitedStart[b + 1]));
				}

				mutex.lock();
				for (auto &it : result)
				{
					temp.push_back(it);
				}
				mutex.unlock();
				
			}));
		}
		for (auto & val : m_simpleThreadPool)
		{
			if (val.joinable())
			{
				val.join();
			}
		}
		splitedStart = temp;
	}
	return splitedStart[0];
}

void CBatcherSort::BatcherSort(std::vector<int> & source)
{
	m_startVec = source;
	OddEvenMergeSort(0, m_startVec.size());
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

