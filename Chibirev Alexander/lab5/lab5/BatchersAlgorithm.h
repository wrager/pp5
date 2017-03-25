#pragma once
typedef std::pair<std::vector<int>, std::vector<int>> Pair;
typedef std::vector<std::vector<int>> Vector;

class CBatchersAlgorithm
{
public:
	CBatchersAlgorithm();
	Vector BatchersMergeSort(Vector list);

private:
	Vector GetBatchersMerge(Vector & vec);
	void RecountingArray(Vector &resultVec,	Vector &copyVec, 
		int k,	std::vector<int> &vecFirst, std::vector<int> &interResult);
	bool IsUnit(Vector const &vec);
	Pair GetBatchersRange(std::vector<int> const &list);
};

