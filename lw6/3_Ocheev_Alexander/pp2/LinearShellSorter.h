#pragma once
#include "AbstractShellSorter.h"

template <class T>
class LinearShellSorter : public AbstractShellSorter<T>
{
public:
    LinearShellSorter() = default;

    void Sort() override
    {
        for (int gap = vector.size() / 2; gap > 0; gap /= 2)
        {
            for (int start = 0; start < gap; start++)
            {
                SortByIntervals(gap, start);
            }
        }
    }
};