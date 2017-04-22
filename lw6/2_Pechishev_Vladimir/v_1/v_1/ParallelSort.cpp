#include "stdafx.h"
#include "ParallelSort.h"
#include "Mergesort.h" 
#include <thread>


CParallelSort::CParallelSort()
	: m_array(std::vector<double>())
{
}


void CParallelSort::SetArray(std::vector<double> const & arr)
{
	m_array = arr;
}

void CParallelSort::Sort(size_t countThread)
{
	std::vector<std::vector<double>> sorted;
	auto size = m_array.size();
	for (size_t threadNumber = 0; threadNumber < countThread; ++threadNumber)
	{
		size_t leftRange = size / countThread * threadNumber;
		size_t rightRange = (threadNumber == (countThread - 1) ? size : leftRange + size / countThread);

		auto beginIterator = m_array.begin() + leftRange;
		std::vector<double> range;
		for (auto it = beginIterator; it != m_array.begin() + rightRange; ++it)
		{
			range.push_back(*it);
		}
		sorted.push_back(range);
	}

	while (sorted.size() > 1)
	{
		for (size_t i = 0; i < sorted.size(); ++i)
		{
			m_pool.AddThread(std::thread(CMergesort::Sort, std::ref(sorted[i])));
		}

		m_pool.WaitForMultiplyObjects();

		std::vector<std::vector<double>> temp;
		for (size_t i = 0, lenght = sorted.size(); i < lenght; i += 2)
		{
			auto leftPart = sorted[i];

			if (i < lenght - 1)
			{
				auto rightPart = sorted[i + 1];
				leftPart.insert(leftPart.end(), rightPart.begin(), rightPart.end());
			}
			
			temp.push_back(leftPart);
		}

		sorted.swap(temp);
	}

	m_array = *sorted.begin();
}
