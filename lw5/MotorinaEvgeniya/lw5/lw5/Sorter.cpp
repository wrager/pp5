#include "stdafx.h"
#include "Sorter.h"
#include <math.h>
#include <boost\bind.hpp>
#include <iostream>

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
				int cur = 0;
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
#pragma omp parallel
				{
#pragma omp for
				for (int i = 0; i < cur; i++)
				{
					m_array[i + begin] = buf[i];
				}
			}
		}
		else if (m_array[end] < m_array[begin])
		{
			std::swap(m_array[end], m_array[begin]);
		}
	}
}

void CSorter::MergeSort(std::vector<int> & array, size_t begin, size_t end)
{
	m_array = array;
	Sort(begin, end);
	array = m_array;
}

