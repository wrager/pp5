#pragma once
class CCalculateAlgorithm
{
public:
	CCalculateAlgorithm(const std::vector<int>& vec);
	~CCalculateAlgorithm();
	
	void Sort(bool parallel);
	std::vector<int> GetVec();
private:
	void BatchersMergeSort(size_t left, size_t right);
	void BatchersMerge(size_t left, size_t size, size_t right);
	void CompareAndSwap(size_t i, size_t j);

	std::vector<int> m_vec;
	bool m_parallel = false;
};

