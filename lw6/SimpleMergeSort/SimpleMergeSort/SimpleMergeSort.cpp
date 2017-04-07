#include "stdafx.h"
#include "SimpleMergeSort.h"

CSimpleMergeSort::CSimpleMergeSort(std::string inputFilename, std::string outputFilename)
	: m_input(inputFilename), m_output(outputFilename)
{
}

void CSimpleMergeSort::Execute()
{
	WriteResult(SimpleMergeSort(ReadStart()));
}

std::vector<int> CSimpleMergeSort::MergeVectors(std::vector<int> vec1, std::vector<int> vec2)
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

std::vector<int> CSimpleMergeSort::ReadStart()
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

void CSimpleMergeSort::WriteResult(std::vector<int> result)
{
	std::ofstream out(m_output);
	for (auto num : result)
	{
		out << num << std::endl;
	}
	out.close();
}

std::vector<int> CSimpleMergeSort::SimpleMergeSort(std::vector<int> & source)
{
	std::vector<std::vector<int>> splitedStart;

	for (size_t i = 0; i < source.size(); i++)
	{
		splitedStart.push_back({ source[i] });
	}
	std::mutex mutex;
	while (splitedStart.size() > 1)
	{
		std::vector<std::vector<int>> temp;
		for (size_t i = 0; i < splitedStart.size() - 1; i += 2)
		{
			m_simpleThreadPool.emplace_back(std::thread([&] {
				size_t b = i;
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
