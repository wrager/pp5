#include "stdafx.h"
#include "Sorter.h"

Sorter::Sorter(AsyncManager & manager)
	: m_manager(manager)
	, m_threadCount(1)
{
}

Sorter::~Sorter()
{
}

void Sorter::SetArray(std::vector<int> const & array)
{
	m_elements.clear();
	for (auto &it : array)
	{
		m_elements.push_back(std::vector<int>());
		m_elements.back().push_back(it);
	}
}

void Sorter::StartSort()
{
	m_manager.SetThreadCount(m_threadCount);
	m_manager.Run();
	size_t blockSize = size_t(ceil(double(m_elements.size()) / m_threadCount));
	size_t targetPos = 0;
	std::mutex resultVecMutex;
	std::vector<std::vector<int>> resultVec;
	while (targetPos < m_elements.size())
	{
		std::vector<std::vector<int>> tempVec;
		if (targetPos + blockSize < m_elements.size())
		{
			tempVec = std::vector<std::vector<int>>(m_elements.begin() + targetPos, m_elements.begin() + targetPos + blockSize);
		}
		else
		{
			tempVec = std::vector<std::vector<int>>(m_elements.begin() + targetPos, m_elements.end());
		}
		targetPos += blockSize;
		m_manager.Post(boost::bind(Sorter::SortVec, tempVec, std::ref(resultVec), &resultVecMutex));
	}

	while(resultVec.size() < size_t(m_threadCount))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	m_elements = std::move(resultVec);
	m_manager.Post(boost::bind(Sorter::SortVec, m_elements, std::ref(resultVec), &resultVecMutex));
	while (resultVec.empty())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	m_elements = std::move(resultVec);
	m_manager.Stop();
}

void Sorter::SetThreadCount(int count)
{
	if (m_threadCount < 0)
	{
		m_threadCount = 1;
	}
	m_threadCount = count;
	m_manager.SetThreadCount(m_threadCount);
}

void Sorter::SortVec(std::vector<std::vector<int>>& vecToSort, std::vector<std::vector<int>>& resultVec, std::mutex* vecMutex)
{
	std::mutex tempMutex;
	while (vecToSort.size() > 1)
	{
		std::vector<std::vector<int>>  tempVec;
		size_t targetSize = size_t(ceil(double(vecToSort.size()) / 2.0));
		while (tempVec.size() < targetSize)
		{
			if (!vecToSort.empty())
			{
				if (vecToSort.size() > 1)
				{
					auto vec1 = vecToSort.back();
					vecToSort.pop_back();
					auto vec2 = vecToSort.back();
					vecToSort.pop_back();
					MergeVectors(vec1, vec2, std::ref(tempVec), &tempMutex);
				}
				else
				{
					auto vec1 = vecToSort.back();
					vecToSort.pop_back();
					tempMutex.lock();
					tempVec.push_back(vec1);
					tempMutex.unlock();
				}
			}
		}
		vecToSort = tempVec;
	}
	while (!tempMutex.try_lock())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	tempMutex.unlock();

	vecMutex->lock();
	resultVec.push_back(vecToSort.front());
	vecMutex->unlock();
}

void Sorter::MergeVectors(std::vector<int> const& vec1, std::vector<int> const& vec2, std::vector<std::vector<int>> & mainVec, std::mutex * mutex)
{
	std::vector<int> resultVec;
	auto v1 = vec1;
	auto v2 = vec2;
	std::reverse(v1.begin(), v1.end());
	std::reverse(v2.begin(), v2.end());
	for (; !v1.empty() && !v2.empty();)
	{
		if (v1.back() > v2.back())
		{
			resultVec.push_back(v2.back());
			v2.pop_back();
		}
		else
		{
			resultVec.push_back(v1.back());
			v1.pop_back();
		}
	}
	while (!v1.empty())
	{
		resultVec.push_back(v1.back());
		v1.pop_back();
	}
	while (!v2.empty())
	{
		resultVec.push_back(v2.back());
		v2.pop_back();
	}
	mutex->lock();
	mainVec.push_back(std::move(resultVec));
	mutex->unlock();
}