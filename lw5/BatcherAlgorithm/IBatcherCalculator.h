#pragma once
#include <vector>

class IBatcherCalculator
{
public:
    virtual void Sort(bool isParallel) = 0;
    virtual std::vector<int> GetResult() = 0;
    virtual void Reset(const std::vector<int> & vec) = 0;
};