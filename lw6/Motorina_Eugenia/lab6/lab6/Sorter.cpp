#include "stdafx.h"
#include "ThreadPool.h"
#include "Sorter.h"
#include <math.h>

CSorter::CSorter()
{
}


CSorter::~CSorter()
{
}

void CSorter::Sort(size_t begin, size_t end)
{
	if (begin != end)
	{
		if (end - begin != 1)
		{
			size_t half = (end + begin) / 2;
			Sort(begin, half);
			Sort(half + 1, end);
			std::vector<int> buf;
			buf.resize(m_array.size());
			size_t xl = begin;
			size_t xr = half + 1;
			size_t cur = 0;
			while (end - begin + 1 != cur)
			{
				if (xl > half)
				{
					buf[cur++] = m_array[xr++];
				}
				else if (xr > end)
				{
					buf[cur++] = m_array[xl++];
				}
				else if (m_array[xl] > m_array[xr])
				{
					buf[cur++] = m_array[xr++];
				}
				else
				{
					buf[cur++] = m_array[xl++];
				}
			}
			for (int i = 0; i < cur; i++)
			{
				m_array[i + begin] = buf[i];
			}
		}
		else if (m_array[end] < m_array[begin])
		{
			std::swap(m_array[end], m_array[begin]);
		}
	}
}

void CSorter::StartThreads(size_t count)
{
	ThreadPool threadPool;
	auto size = m_array.size();
	auto block = size_t(std::ceil(double(size) / count));
	size_t currentPos = 0;
	for (size_t threadId = 0; threadId < count; ++threadId)
	{
		if (currentPos + block >= size)
		{
			threadPool.AddThread(std::thread(boost::bind(&CSorter::Sort, this, currentPos, size - 1)));
			break;
		}
		threadPool.AddThread(std::thread(boost::bind(&CSorter::Sort, this, currentPos, currentPos + block)));
		currentPos += block + 1;
	}
	threadPool.WaitThread();
}

void CSorter::MergeSort(std::vector<int> & array)
{
	m_array = array;
	Sort(0, m_array.size() - 1);
	array = m_array;
}

void CSorter::MergeSortWithThreads(std::vector<int>& array, size_t threadCount)
{
	m_array = array;
	StartThreads(threadCount);
	Sort(0, m_array.size() - 1);
	array = m_array;
}
