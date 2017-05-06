#pragma once
#include "AbstractSorter.h"
#include <algorithm>

template <class T>
class LinearShellSorter : public AbstractSorter<T>
{
public:
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

protected:
    void SortByIntervals(int gap, int start)
    {
        for (int i = start; i < vector.size(); i += gap)
        {
            for (int j = start; j < i ; j += gap)
            {
                if (vector[i] < vector[j])
                {
                    CycleShift(i, j, gap);
                    continue;
                }
            }
        }
    }

    void CycleShift(int from, int to, int gap)
    {
        auto t = vector[from];
        for (int i = from; i > to; i -= gap)
        {
            vector[i] = vector[i - gap];
        }
        vector[to] = t;
    }
};