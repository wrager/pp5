#include "CParallelSorter.h"

CParallelSorter::CParallelSorter(const std::vector<int> & data)
	:COddEvenMergeSorter(data)
	{}

void CParallelSorter::OddEvenMergeSort(int lo, int n)
{
	if (n > 1)
	{
		int m = n / 2;

#pragma omp parallel
		{
#pragma omp sections
			{
#pragma omp section
				{
					OddEvenMergeSort(lo, m);
				}
#pragma omp section
				{
					OddEvenMergeSort(lo + m, m);
				}
			}
		}			

		OddEvenMerge(lo, n, 1);
	}
}

void CParallelSorter::OddEvenMerge(int lo, int n, int r)
{
	int m = r * 2;
	if (m < n)
	{
		int maxI = lo + n - r;
#pragma omp parallel
		{
#pragma omp sections
			{
#pragma omp section
				{
					OddEvenMerge(lo, n, m);
				}
#pragma omp section
				{
					OddEvenMerge(lo + r, n, m);
				}
			}
#pragma omp for
			for (int i = lo + r; i < maxI; i += m)
			{
				Compare(i, i + r);
			}
		}
	}
	else
	{
		Compare(lo, lo + r);
	}
}