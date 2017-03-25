#include "stdafx.h"
#include "BatchersAlgorithm.h"


CBatchersAlgorithm::CBatchersAlgorithm()
{
}

Vector CBatchersAlgorithm::BatchersMergeSort(Vector list)
{
	while (!IsUnit(list))
	{
		for (size_t i = 0; i != list.size(); ++i)
		{
			if (list.at(i).size() != 1)
			{
				Pair pair = GetBatchersRange(list.at(i));
				list.erase(list.begin() + i);
				list.insert(list.begin() + i, pair.first);
				list.insert(list.begin() + i + 1, pair.second);
			}
		}
	}
	return GetBatchersMerge(list);
}

Vector CBatchersAlgorithm::GetBatchersMerge(Vector & vec)
{
	Vector copyVec = vec;
	while (copyVec.size() != 1)
	{
		Vector resultVec;
		for (int k = 0; k < copyVec.size(); k += 2)
		{
			std::vector<int> interResult;
			auto vecFirst = copyVec.at(k);

			if (k + 1 >= copyVec.size())
			{
				interResult.resize(vecFirst.size());
				std::copy(vecFirst.begin(), vecFirst.end(), interResult.begin());

			}
			else
			{
				RecountingArray(resultVec, copyVec,	k, vecFirst, interResult);
			}
			resultVec.push_back(interResult);
		}
		copyVec = resultVec;
	}
	return copyVec;
}

void CBatchersAlgorithm::RecountingArray(Vector &resultVec, Vector &copyVec,
	int k, std::vector<int> &vecFirst, std::vector<int> &interResult)
{
	int j = 0;
	for (int i = 0; i != vecFirst.size(); ++i)
	{
		auto vecSecond = copyVec.at(k + 1);

		for (; j != vecSecond.size(); ++j)
		{
			int headFirst = vecFirst.at(i);
			int headSecond = vecSecond.at(j);
			if (headFirst <= headSecond)
			{
				interResult.push_back(headFirst);
				break;
			}
			else
				interResult.push_back(headSecond);
		}

		if (i + 1 == vecFirst.size())
			std::copy(vecSecond.begin() + j, vecSecond.end(), std::back_inserter(interResult));
		if (j + 1 > vecSecond.size())
		{
			std::copy(vecFirst.begin() + i, vecFirst.end(), std::back_inserter(interResult));
			break;
		}
	}
}

Pair CBatchersAlgorithm::GetBatchersRange(std::vector<int> const &list)
{
	size_t size = list.size() / 2;

	std::vector<int> left(size);
	std::vector<int> right(list.size() - size);

	std::copy(list.begin(), list.begin() + size, left.begin());
	std::copy(list.begin() + size, list.end(), right.begin());

	return{ left, right };
}



bool CBatchersAlgorithm::IsUnit(Vector const &vec)
{
	for (auto el : vec)
	{
		if (el.size() > 1)
			return false;
	}
	return true;
}
