#include "stdafx.h"
#include "SortTestClass.h"
#include "LinearMergeSorter.h"
#include "LinearShellSorter.h"
#include "ParallelMergeSorter.h"
#include "ParallelShellSorter.h"
#include <numeric>
#include <algorithm>

using namespace std;

SortTestClass::SortTestClass()
{
    _increaseVector = vector<int>(16);
    iota(_increaseVector.begin(), _increaseVector.end(), 0);
    _decreaseVector = vector<int>(16);
    iota(_decreaseVector.rbegin(), _decreaseVector.rend(), 0);
    _randomOrderVector = { 8, 7, 5, 6, 10, 4, 1, 0, 2, 3, 9, 13, 15, 14, 12, 11 };
    _expectedVector = _increaseVector;
}

void SortTestClass::TestSort(AbstractSorter<int>& sorter)
{
    SortTestCase(_increaseVector, sorter);
    SortTestCase(_decreaseVector, sorter);
    SortTestCase(_randomOrderVector, sorter);
}

void SortTestClass::SortTestCase(const vector<int>& sourceVector, AbstractSorter<int>& sorter)
{
    sorter.SetVector(sourceVector);
    sorter.Sort();
    auto result = sorter.GetVector();
    assert(equal(_expectedVector.cbegin(), _expectedVector.cend(), result.cbegin(), result.cend()));
}

void SortTest()
{
    SortTestClass sortTestClass;

    sortTestClass.TestSort(LinearShellSorter<int>());
    sortTestClass.TestSort(LinearMergeSorter<int>());
    //sortTestClass.TestSort(ParallelShellSorter<int>());
    //sortTestClass.TestSort(ParallelMergeSorter<int>());
}
