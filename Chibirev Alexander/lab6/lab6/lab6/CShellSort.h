#pragma once
#include "BaseSort.h"

class CShellSort : public CBaseSort
{
public:
    CShellSort() = default;
    CShellSort(const std::vector<int>& vec);

protected:
    void SortArray() override;

private:
    void ShellIteration(size_t i, size_t half);
};
