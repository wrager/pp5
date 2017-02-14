#include "CSorter.h"


COddEvenMergeSorter::COddEvenMergeSorter(const std::vector<int> & data)
	: m_data(data)
	{}



void COddEvenMergeSorter::CheckCalculatingTime()
{
	float firstTime = float(clock());
	auto v = CUtils::InitializeVector(4096 * 16);
	Sort();
	float newTime = clock();
	std::cout << "Calculation time: " << (float(clock()) - firstTime) / (double)CLOCKS_PER_SEC << std::endl;
}

void COddEvenMergeSorter::Sort()
{
	OddEvenMergeSort(0, m_data.size());
}

void COddEvenMergeSorter::OddEvenMergeSort(int lo, int n)
{
	if (n > 1)
	{
		int m = n / 2;
		OddEvenMergeSort(lo, m);
		OddEvenMergeSort(lo + m, m);
		OddEvenMerge(lo, n, 1);
	}
}

void COddEvenMergeSorter::OddEvenMerge(int lo, int n, int r)
{
	int m = r * 2;
	if (m < n)
	{
		OddEvenMerge(lo, n, m);
		OddEvenMerge(lo + r, n, m);
		for (int i = lo + r; i + r < lo + n; i += m)
		{
			Compare(i, i + r);
		}
	}
	else
	{
		Compare(lo, lo + r);
	}
}

void COddEvenMergeSorter::Compare(int i, int j)
{
	if (m_data[i] > m_data[j])
	{
		Exchange(i, j);
	}
}

void COddEvenMergeSorter::Exchange(int i, int j)
{
	int t = m_data[i];
	m_data[i] = m_data[j];
	m_data[j] = t;
}