#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include "Sorter.h"
#include "Utils.h"
#include "ParallelSorter.h"


int main()
{
    std::vector<int> vec = CUtils::ReadDataFromFile();
    COddEvenMergeSorter sorter(vec);
    sorter.CheckCalculatingTime();

    ParallelSorter parallelSorter(vec);
    parallelSorter.CheckCalculatingTime();

    return 0;
}