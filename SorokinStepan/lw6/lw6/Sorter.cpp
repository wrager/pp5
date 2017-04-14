#include "stdafx.h"
#include "Sorter.h"

Sorter::Sorter(AsyncManager & manager)
	: m_manager(manager)
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
	m_manager.Run();
	while (m_elements.size() > 1)
	{
		std::vector<std::vector<int>>  tempVec;
		std::mutex tempMutex;
		size_t targetSize = size_t(ceil(double(m_elements.size()) / 2.0));
		while (tempVec.size() < targetSize)
		{
			if (!m_elements.empty())
			{
				if (m_elements.size() > 1)
				{
					auto vec1 = m_elements.back();
					m_elements.pop_back();
					auto vec2 = m_elements.back();
					m_elements.pop_back();
					m_manager.Post(boost::bind(&Sorter::MergeVectors, vec1, vec2, std::ref(tempVec), &tempMutex));
				}
				else
				{
					auto vec1 = m_elements.back();
					m_elements.pop_back();
					tempMutex.lock();
					tempVec.push_back(vec1);
					tempMutex.unlock();
				}
			}
		}
		m_elements = tempVec;
	}
	m_manager.Stop();
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
	mainVec.push_back(resultVec);
	mutex->unlock();
}