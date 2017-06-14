#pragma once
#include "AbstractSorter.h"
#include <algorithm>

template <class T>
class AbstractShellSorter : public AbstractSorter<T>
{
protected:
    void SortByIntervals(int gap, int start)
    {
        for (int i = start; i < vector.size(); i += gap)
        {
            for (int j = start; j < i; j += gap)
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