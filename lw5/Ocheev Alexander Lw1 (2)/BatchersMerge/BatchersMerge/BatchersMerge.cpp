// BatchersMerge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LinearBatchersSorter.h"
#include "ParallelBatchersSort.h"

using namespace std;

vector<int> GetVector(istream &stream);
void PutVector(const vector<int> &vect, ostream &stream);
void RunTests();

template <class T>
struct SortUtil
{
    clock_t time;
    vector<T> result;

    void Sort(AbstractBatchersSorter<T> &sorter, const vector<T> &source)
    {
        time = clock();
        result = sorter.Sort(source);
        time = clock() - time;
    }
};

int main(int argc, char *argv[])
{
    ifstream input(argv[1]);
    auto source = GetVector(input);
    SortUtil<int> util;

    ofstream linearOut("linear.txt");
    LinearBatchersSorter<int> linear;
    util.Sort(linear, source);
    PutVector(util.result, linearOut);
    cout << "linear time: " << util.time << endl;

    ofstream parallelOut("parallel.txt");
    ParallelBatchersSorter<int> parallel;
    util.Sort(parallel, source);
    PutVector(util.result, parallelOut);
    cout << "parallel time: " << util.time << endl;

    return 0;
}


vector<int> GetVector(istream &stream)
{
    vector<int> result;
    int number;
    while (stream >> number)
    {
        result.push_back(number);
    }

    return result;
}

void PutVector(const vector<int> &vect, ostream &stream)
{
    for (const auto &item : vect)
    {
        stream << item << " ";
    }
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
