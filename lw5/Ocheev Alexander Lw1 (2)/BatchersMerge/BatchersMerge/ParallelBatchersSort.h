#pragma once
#include <vector>
#include <algorithm>
#include <omp.h>
#include "AbstractBatchersMerge.h"

template <class T>
class ParallelBatchersSorter : public AbstractBatchersSorter<T>
{
protected:
    void OddEvenMergeSort(size_t lo, size_t n) override
    {
        if (n <= 1)
        {
            return;
        }

        size_t m = n / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                OddEvenMergeSort(lo, m);
            }
#pragma omp section
            {
                OddEvenMergeSort(lo + m, m);
            }
        }

        OddEvenMerge(lo, n, 1);
    }

    void OddEvenMerge(size_t lo, size_t n, size_t r) override
    {
        size_t m = r * 2;
        if (m < n)
        {
#pragma omp parallel
            {
#pragma omp sections
                {
#pragma omp section
                    {
                        OddEvenMerge(lo, n, m);      // even subsequence
                    }
#pragma omp section
                    {
                        OddEvenMerge(lo + r, n, m);    // odd subsequence
                    }
                }
#pragma omp for
                for (int i = lo + r; i < lo + n - r; i += m)
                {
                    Compare(i, i + r);
                }
            }
        }
        else
        {
            Compare(lo, lo + r);
        }
    }
};