#pragma once
#include "BaseSortCalculator.h"

class CMergeSortCalculator : public CBaseSortCalculator
{
public:
    CMergeSortCalculator() = default;
    CMergeSortCalculator(const std::vector<int>& vec);

protected:
    void SortBehavior() override;

private:
    void StartSort(size_t left, size_t right);
    void Merge(size_t left, size_t size, size_t right);
};