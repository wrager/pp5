#pragma once
#include <vector>

class ISortCalculator
{
public:
    virtual void Sort(bool isParallel) = 0;
    virtual std::vector<int> GetResult() const = 0;
    virtual void Reset(const std::vector<int> & array) = 0;

    virtual ~ISortCalculator() = default;
};