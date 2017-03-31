#include "MergeSorter.h"

CMergeSorter::CMergeSorter(const std::vector<int> & data)
	:m_data(data)
{

}

std::vector<int> CMergeSorter::GetData() const
{
	return m_data;
}

void CMergeSorter::Sort(std::vector<int> & values)
{
	m_data = values;
	number = values.size();
	helper = std::vector<int>(number);
	MergeSort(0, number - 1);
}

void CMergeSorter::MergeSort(int low, int high)
{
	if (low < high)
	{
		int middle = low + (high - low) / 2;
		MergeSort(low, middle);
		MergeSort(middle + 1, high);
		Merge(low, middle, high);
	}
}

void CMergeSorter::Merge(int low, int middle, int high) 
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