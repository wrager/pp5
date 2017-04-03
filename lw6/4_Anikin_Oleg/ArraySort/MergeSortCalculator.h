#pragma once
#include "IMergeSortCalculator.h"

class CMergeSortCalculator : public IMergeSortCalculator
{
public:
    CMergeSortCalculator() = default;
    CMergeSortCalculator(const std::vector<int>& vec);

    void Sort(bool isParallel) override;
    std::vector<int> GetResult() const override;
    void Reset(const std::vector<int> & array) override;

private:
    void StartSort(size_t left, size_t right);
    void Merge(size_t left, size_t size, size_t right);
    void WaitForMultiplyObjects(std::vector<std::thread> & threads);

    std::vector<int> m_array;
    bool m_isParallelEnabled;
};