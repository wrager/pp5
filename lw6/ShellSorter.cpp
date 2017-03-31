#include "ShellSorter.h"


CShellSorter::CShellSorter(const std::vector<int> & data)
	:data(data)
{

}

void CShellSorter::Sort()
{
	ShellSort(data.size());
}

void CShellSorter::ShellSort(int n)
{
	for (int h = n; h /= 2;)
	{
		int t;
		for (int i = h; i < n; i++)
		{
			t = data[i];
			int j;
			for (j = i; j >= h && t < data[j - h]; j -= h)
			{
				data[j] = data[j - h];
			}
			data[j] = t;
		}
	}
}

std::vector<int> CShellSorter::GetData() const
{
	return data;
}
