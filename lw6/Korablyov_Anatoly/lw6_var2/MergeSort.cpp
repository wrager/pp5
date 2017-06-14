#include "MergeSort.h"


CMergeSort::CMergeSort()
{
}


CMergeSort::~CMergeSort()
{
}
void StartCalcRank(CMergeSort * mat, std::vector<unsigned> & num)
{
	mat->StartMergeSort(num);
}

void ReplaceArrToTwoArr(const std::vector<unsigned> & nums, std::vector<unsigned> & firstArr, std::vector<unsigned> & secondArr)
{
	int nElems = nums.size() / 2;
	for (auto it : nums)
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
}

std::vector<unsigned> CMergeSort::MergeTwoArray(const std::vector<unsigned> & firstArr, const std::vector<unsigned> & secondArr)
{
	std::vector<unsigned> resultArr;
	int firstIndex = 0;
	int secIndex = 0;
	while (resultArr.size() < firstArr.size() + secondArr.size())
	{
		if (firstIndex >= int(firstArr.size()))
		{
			for (size_t it = secIndex; it < secondArr.size(); it++)
			{
				resultArr.push_back(secondArr[it]);
			}
		}
		else if (secIndex >= int(secondArr.size()))
		{
			for (size_t it = firstIndex; it < firstArr.size(); it++)
			{
				resultArr.push_back(firstArr[it]);
			}
		}
		else
		{
			if (firstArr[firstIndex] <= secondArr[secIndex])
			{
				resultArr.push_back(firstArr[firstIndex]);
				firstIndex++;
			}
			else
			{
				resultArr.push_back(secondArr[secIndex]);
				secIndex++;
			}
		}
	}
	return resultArr;
}

void CMergeSort::StartMergeSort(std::vector<unsigned>& num)
{
	if (num.size() > 1)
	{
		std::vector<unsigned> firstArr;
		std::vector<unsigned> secondArr;
		ReplaceArrToTwoArr(num, firstArr, secondArr);

		StartMergeSort(firstArr);
		StartMergeSort(secondArr);

		std::vector<unsigned> resultArr = MergeTwoArray(firstArr, secondArr);

		num.clear();
		for (auto i : resultArr)
		{
			num.push_back(i);
		}
	}
}

std::vector<unsigned> CMergeSort::MergeSortParallel(const std::vector<unsigned>& num)
{
	if (num.size() > 1)
	{
		std::vector<unsigned> firstArr;
		std::vector<unsigned> secondArr;
		ReplaceArrToTwoArr(num, firstArr, secondArr);

		std::thread firstThread(StartCalcRank, this, firstArr);
		std::thread secThread(StartCalcRank, this, secondArr);
		firstThread.join();
		secThread.join();

		std::vector<unsigned> resultArr = MergeTwoArray(firstArr, secondArr);

		return resultArr;
	}
	else
	{
		return num;
	}
}

std::vector<unsigned> CMergeSort::MergeSortSequence(const std::vector<unsigned>& num)
{
	if (num.size() > 1)
	{
		std::vector<unsigned> firstArr;
		std::vector<unsigned> secondArr;
		ReplaceArrToTwoArr(num, firstArr, secondArr);

		StartMergeSort(firstArr);
		StartMergeSort(secondArr);

		std::vector<unsigned> resultArr = MergeTwoArray(firstArr, secondArr);

		return resultArr;
	}
	else
	{
		return num;
	}
}
