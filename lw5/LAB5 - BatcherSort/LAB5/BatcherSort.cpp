#include "stdafx.h"
#include "BatcherSort.h"
#include <iostream>


CBatcherSort::CBatcherSort(const std::vector<int>& inputMass)
	: m_mass(inputMass)
{
}


void CBatcherSort::OddEvenMerge(int leftOperand, int length, int rightOperand)
{
	int middle = rightOperand * 2;
	if (middle < length)
	{
		OddEvenMerge(leftOperand, length, middle);
		OddEvenMerge(leftOperand + rightOperand, length, middle);
		for (auto i = leftOperand + rightOperand; 
			i + rightOperand < (leftOperand + length); 
			i += middle
			)
		{
			Compare(i, i + rightOperand);
		}
	}
	else
	{
		Compare(leftOperand, leftOperand + rightOperand);
	}
}

void CBatcherSort::Compare(int i, int j)
{
	if (m_mass[i] > m_mass[j])
	{
		std::swap(m_mass[i], m_mass[j]);
	}
}

std::vector<int> CBatcherSort::GetMass() const
{
	return m_mass;
}

CBatcherSort::~CBatcherSort()
{
}
