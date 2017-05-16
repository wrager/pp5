#include "SortBatcher.h"
#include <omp.h>


CSortBatcher::CSortBatcher()
{
}


CSortBatcher::~CSortBatcher()
{
}

std::vector<unsigned> CSortBatcher::sortBatcher(const std::vector<unsigned>& num)
{
	
	if (num.size() > 1)
	{
		std::vector<unsigned> firstArr;
		std::vector<unsigned> secondArr;
		int nElems = num.size() / 2;
		for (auto it : num)
		{
			if (nElems < 1)
			{
				secondArr.push_back(it);
			}
			else
			{
				firstArr.push_back(it);
				nElems--;
			}
		}
		std::vector<unsigned> sortedFirstArr;
		std::vector<unsigned> sortedSecArr;
		 
		///////////////////
		//// Parallel
		//#pragma omp parallel sections
		//{
		//	#pragma omp section
		//	sortedFirstArr = sortBatcher(firstArr);
		//	#pragma omp section
		//	sortedSecArr = sortBatcher(secondArr);
		//}
		///////////////////

		/////////////////
		// Sequence
		sortedFirstArr = sortBatcher(firstArr);
		sortedSecArr = sortBatcher(secondArr);
		/////////////////

		std::vector<unsigned> resultArr;
		int firstIndex = 0;
		int secIndex = 0;
		while (resultArr.size() < sortedFirstArr.size() + sortedSecArr.size())
		{
			if (firstIndex >= sortedFirstArr.size())
			{
				for (size_t it = secIndex; it < sortedSecArr.size(); it++)
				{
					resultArr.push_back(sortedSecArr[it]);
				}
			}
			else if (secIndex >= sortedSecArr.size())
			{
				for (size_t it = firstIndex; it < sortedFirstArr.size(); it++)
				{
					resultArr.push_back(sortedFirstArr[it]);
				}
			}
			else
			{
				if (sortedFirstArr[firstIndex] <= sortedSecArr[secIndex])
				{
					resultArr.push_back(sortedFirstArr[firstIndex]);
					firstIndex++;
				}
				else
				{
					resultArr.push_back(sortedSecArr[secIndex]);
					secIndex++;
				}
			}
		}

		return resultArr;
	}
	else
	{
		return num;
	}
}
