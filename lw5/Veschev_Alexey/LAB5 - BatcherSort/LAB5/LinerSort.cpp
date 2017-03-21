#include "stdafx.h"
#include "LinerSort.h"
#include <iostream>

void LinerSort::OddEvenMergeSort(int leftOperand, int length)
{
	if (length > 1)
	{
		int middle = length / 2;
		OddEvenMergeSort(leftOperand, middle);
		OddEvenMergeSort(leftOperand + middle, middle);
		OddEvenMerge(leftOperand, length, 1);
	}
}

void LinerSort::Sort()
{
	OddEvenMergeSort(0, m_mass.size());
}
