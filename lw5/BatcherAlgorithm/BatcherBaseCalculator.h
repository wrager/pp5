#pragma once
#include "IBatcherCalculator.h"
#include <functional>

typedef std::function<void(size_t left, size_t right)> SortFunc;

class CBatcherBaseCalculator : public IBatcherCalculator
{
public:
    CBatcherBaseCalculator() = default;
    CBatcherBaseCalculator(const std::vector<int>& vec);

    void Sort(bool isParallel) override;
    std::vector<int> GetResult() override;
    void Reset(const std::vector<int> &) override;

private:
    void StartSort(size_t left, size_t right);
    void Merge(size_t left, size_t size, size_t right);
    void Compare(int & left, int & right);

    std::vector<int> m_vec;
    bool m_isParallelEnabled = false;
};
