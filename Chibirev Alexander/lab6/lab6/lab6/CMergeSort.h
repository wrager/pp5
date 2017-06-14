#pragma once
#include "BaseSort.h"

class CMergeSort : public CBaseSort
{
public:
    CMergeSort() = default;
    CMergeSort(const std::vector<int>& vec);

protected:
    void SortArray() override;

private:
    void StartSort(size_t left, size_t right);
    void Merge(size_t left, size_t size, size_t right);
};