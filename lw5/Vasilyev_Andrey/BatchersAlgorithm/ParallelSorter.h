#pragma once
#include "Sorter.h"


class ParallelSorter : public COddEvenMergeSorter
{
public:
    ParallelSorter(const std::vector<int> & data);

    void OddEvenMergeSort(int lo, int n) override;
    void OddEvenMerge(int lo, int n, int r) override;
};