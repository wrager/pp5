#pragma once
#include <vector>

class ISorter
{
public:
    virtual std::vector<int> GetSortedResult() const = 0;
    virtual ~ISorter() = default;
};

