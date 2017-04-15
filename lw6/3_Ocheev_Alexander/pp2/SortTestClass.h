#pragma once
#include "AbstractSorter.h"
#include <vector>

class SortTestClass
{
public:
    SortTestClass();
    void TestSort(AbstractSorter<int> &sorter);

private:
    void SortTestCase(const std::vector<int> &sourceVector, AbstractSorter<int> &sorter);

    std::vector<int> _increaseVector;
    std::vector<int> _decreaseVector;
    std::vector<int> _randomOrderVector;
    std::vector<int> _expectedVector;
};

void SortTest();