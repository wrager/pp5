#pragma once
#include "ISortCalculator.h"

class CBaseSort : public ISortCalculator
{
public:
    void Sort(bool isParallel) override;
    std::vector<int> GetResult() const override;
    void Reset(const std::vector<int> & array) override;

protected:
    CBaseSort() = default;
    CBaseSort(const std::vector<int>& vec);

    virtual void SortArray() = 0;

    void WaitForMultiplyObjects(std::vector<std::thread>& threads);

    std::vector<int> m_array;
    bool m_isParallelEnabled;
};

