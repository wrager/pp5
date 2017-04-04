#pragma once
#include "ISortCalculator.h"

class CBaseSortCalculator : public ISortCalculator
{
public:
    void Sort(bool isParallel) override;
    std::vector<int> GetResult() const override;
    void Reset(const std::vector<int> & array) override;

protected:
    CBaseSortCalculator() = default;
    CBaseSortCalculator(const std::vector<int>& vec);

    void WaitForMultiplyObjects(std::vector<std::thread>& threads);

    std::vector<int> m_array;
    bool m_isParallelEnabled;
};

