#pragma once
#include "BaseSortCalculator.h"

class CShellSortCalculator : public CBaseSortCalculator
{
public:
    CShellSortCalculator() = default;
    CShellSortCalculator(const std::vector<int>& vec);

    void Sort(bool isParallel) override;

private:
    void ShellIteration(size_t i, size_t half);
};
