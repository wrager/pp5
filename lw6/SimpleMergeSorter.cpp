#include "SimpleMergeSorter.h"

CSimpleMergeSorter::CSimpleMergeSorter(const std::vector<int> & data)
	:CSorter(data)
{

}

std::string CSimpleMergeSorter::ToString()
{
	return "Simple mergeSorter";
}


void CSimpleMergeSorter::Sort()
{
	helper = std::vector<int>(m_data.size());
	MergeSort(0, m_data.size() - 1);
}

void CSimpleMergeSorter::MergeSort(int low, int high)
{
	if (low < high)
	{
		int middle = low + (high - low) / 2;
		MergeSort(low, middle);
		MergeSort(middle + 1, high);
		Merge(low, middle, high);
	}
}

void CSimpleMergeSorter::Merge(int low, int middle, int high) 
{
	for (int i = low; i <= high; i++) 
	{
		helper[i] = m_data[i];
	}

	int i = low;
	int j = middle + 1;
	int k = low;

	while (i <= middle && j <= high)
	{
		if (helper[i] <= helper[j]) 
		{
				m_data[k] = helper[i];
				i++;
		}
		else 
		{
			m_data[k] = helper[j];
			j++;
		}
		k++;
	}

	while (i <= middle) 
	{
		m_data[k] = helper[i];
		k++;
		i++;
	}
}