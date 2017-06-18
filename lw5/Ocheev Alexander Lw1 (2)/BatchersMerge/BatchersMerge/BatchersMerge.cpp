// BatchersMerge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileHandler.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "enter <input file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    FileHandler<int>::Sort(input);

    return 0;
}

template <class T>
void AssertSortVector(AbstractBatchersSorter<T> &sorter, const vector<T> &expected, const vector<T> &source)
{
    vector<T> sortedVector = sorter.Sort(source);
    assert(equal(expected.begin(), expected.end(), sortedVector.begin(), sortedVector.end()));
}

void RunTests()
{
    vector<int> increaseVector = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    vector<int> decreaseVector = increaseVector;
    reverse(decreaseVector.begin(), decreaseVector.end());
    vector<int> unorderedVector = { 3, 7, 8, 15, 4, 2, 14, 1, 0, 11, 10, 9, 12, 13, 5, 6 };

    LinearBatchersSorter<int> linearSorter;
    AssertSortVector(linearSorter, increaseVector, increaseVector);
    AssertSortVector(linearSorter, increaseVector, decreaseVector);
    AssertSortVector(linearSorter, increaseVector, unorderedVector);

    ParallelBatchersSorter<int>  parallelSorter;
    AssertSortVector(parallelSorter, increaseVector, increaseVector);
    AssertSortVector(parallelSorter, increaseVector, decreaseVector);
    AssertSortVector(parallelSorter, increaseVector, unorderedVector);
}
