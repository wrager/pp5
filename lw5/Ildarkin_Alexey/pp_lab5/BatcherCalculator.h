#pragma once

class CBatcherCalculator
{
public:
	CBatcherCalculator(const std::vector<int> &vec);
	CBatcherCalculator(const CBatcherCalculator &) = delete;
	CBatcherCalculator(CBatcherCalculator &&) = delete;
		 
	void Sort(bool isParallel = false);
	std::vector<int> GetResultVec()const;

private:
	void StartSort(size_t left, size_t right);
	void Merge(size_t left, size_t size, size_t right);

private:
	std::vector<int> m_numbersArray;
	bool m_isParallelSorting = false;
};