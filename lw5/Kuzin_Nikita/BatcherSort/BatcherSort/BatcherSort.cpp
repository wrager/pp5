#include "stdafx.h"
#include "BatcherSort.h"


CBatcherSort::CBatcherSort(std::string inputFilename, std::string outputFilename)
	: m_input(inputFilename), m_output(outputFilename)
{
}

void CBatcherSort::Execute()
{
	WriteResult(Sort(ReadStart()));
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

std::vector<std::vector<int>> CBatcherSort::ReadStart()
{
	std::ifstream in(m_input);
	std::vector<std::vector<int>> temp;
	int num;
	while (in >> num)
	{
		temp.push_back(std::vector<int>());
		temp.back().push_back(num);
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

std::vector<int> CBatcherSort::Sort(std::vector<std::vector<int>> & start)
{
	while (start.size() > 1)
	{
		std::vector<std::vector<int>> temp;
#pragma omp parallel for
		for (int i = 0; i < int(start.size()); i += 2)
		{
			std::vector<std::vector<int>> result;
			if (i + 1 >= start.size())
			{
				result.push_back(start[i]);
			}
			else if (i + 1 < start.size())
			{
				result.push_back(MergeVectors(start[i], start[i + 1]));
			}
#pragma omp critical
			{
				for (auto &it : result)
				{
					temp.push_back(it);
				}
			}
		}
		start = temp;
	}
	return start[0];
}
