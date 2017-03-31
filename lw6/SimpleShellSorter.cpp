#include "SimpleShellSorter.h"


CSimpleShellSorter::CSimpleShellSorter(const std::vector<int> & data)
	:CSorter(data)
{
	
}

std::string CSimpleShellSorter::ToString()
{
	return "Simple shellSorter";
}

void CSimpleShellSorter::Sort()
{
	ShellSort(m_data.size());
}

void CSimpleShellSorter::ShellSort(int n)
{
	for (int h = n; h /= 2;)
	{
		int t;
		for (int i = h; i < n; i++)
		{
			t = m_data[i];
			int j;
			for (j = i; j >= h && t < m_data[j - h]; j -= h)
			{
				m_data[j] = m_data[j - h];
			}
			m_data[j] = t;
		}
	}
}