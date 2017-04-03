#pragma once
#include "IMegreSortCalculator.h"

class CMegreSortCalculator : public IMergeSortCalculator
{
public:
    CMegreSortCalculator(const std::vector<int>& vec);

    void Sort(bool isParallel) override;
    std::vector<int> GetResult() const override;
    void Reset(const std::vector<int> & array) override;

protected:
    void StartSort(size_t left, size_t right);
    void Merge(size_t left, size_t size, size_t right);

    std::vector<int> m_array;
    bool m_isParallelEnabled;
};