#pragma once
#include <vector>
#include <algorithm>
#include "AbstractBatchersMerge.h"

template <class T>
class LinearBatchersSorter : public AbstractBatchersSorter<T>
{
protected:
    void OddEvenMergeSort(size_t lo, size_t n) override
    {
        if (n <= 1)
        {
            return;
        }

        size_t m = n / 2;
        OddEvenMergeSort(lo, m);
        OddEvenMergeSort(lo + m, m);
        OddEvenMerge(lo, n, 1);
    }

    void OddEvenMerge(size_t lo, size_t n, size_t r) override
    {
        size_t m = r * 2;
        if (m < n)
        {
            OddEvenMerge(lo, n, m); // even subsequence
            OddEvenMerge(lo + r, n, m); // odd subsequence
            for (size_t i = lo + r; i + r < lo + n; i += m)
            {
                Compare(i, i + r);
            }
        }
        else
        {
            Compare(lo, lo + r);
        }
    }
};