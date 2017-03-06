#pragma once
class CCalculateAlgorithm
{
public:
	CCalculateAlgorithm(const std::vector<int>& vec);
	~CCalculateAlgorithm();
	void  BatchersMergeSort(size_t left, size_t right);
	void BatchersMerge(size_t left, size_t size, size_t right);
	std::vector<int> GetVec();
private:
	void CompareAndSwap(size_t i, size_t j);
	std::vector<int> m_vec;
};

