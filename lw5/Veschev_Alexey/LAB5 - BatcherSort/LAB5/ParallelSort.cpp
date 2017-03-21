#include "stdafx.h"
#include "ParallelSort.h"
#include <iostream>


void CParallelSort::OddEvenMergeSort(int leftOperand, int length)
{
	if (length > 1)
	{
		int middle = length / 2;
		#pragma omp parallel sections
		{
			#pragma omp section
			OddEvenMergeSort(leftOperand, middle);
			#pragma omp section
			OddEvenMergeSort(leftOperand + middle, middle);
		}
		
		OddEvenMerge(leftOperand, length, 1);
	}

}

void CParallelSort::Sort()
{
	OddEvenMergeSort(0, m_mass.size());
}