#include "CSorter.h"


COddEvenMergeSorter::COddEvenMergeSorter(const std::vector<int> & data)
	: m_data(data)
	{}


void COddEvenMergeSorter::Sort()
{
	OddEvenMergeSort(0, m_data.size());
}

/** sorts a piece of length n of the array
*  starting at position lo
*/
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

/** lo is the starting position and
*  n is the length of the piece to be merged,
*  r is the distance of the elements to be compared
*/
void COddEvenMergeSorter::OddEvenMerge(int lo, int n, int r)
{
	int m = r * 2;
	if (m < n)
	{
		OddEvenMerge(lo, n, m);      // even subsequence
		OddEvenMerge(lo + r, n, m);    // odd subsequence
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
		Exchange(i, j);
}

void COddEvenMergeSorter::Exchange(int i, int j)
{
	int t = m_data[i];
	m_data[i] = m_data[j];
	m_data[j] = t;
}