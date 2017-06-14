// pp2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SortTestClass.h"
#include "AbstractSortWriter.h"
#include "LinearMergeSorter.h"
#include "LinearShellSorter.h"
#include "ParallelMergeSorter.h"
#include "ParallelShellSorter.h"
#include "SortRunner.h"

using namespace std;

enum class SortType { Shell, Merge };

void RunSort(string inputFileName, SortType sortType);
int Run(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    //SortTest();

    return Run(argc, argv);
}

void RunSort(string inputFileName, SortType sortType)
{
    ifstream file(inputFileName);
    SortRunner<int> runner(file);

    switch (sortType)
    {
        case SortType::Shell:
            runner.Run(LinearShellSorter<int>(), "Linear Shell time: ", "linear_shell.txt");
            runner.Run(ParallelShellSorter<int>(), "Parallel Shell time: ", "parallel_shell.txt");
            break;
        case SortType::Merge:
            runner.Run(LinearMergeSorter<int>(), "Linear Merge time: ", "linear_merge.txt");
            runner.Run(ParallelMergeSorter<int>(), "Parallel Merge time: ", "parallel_merge.txt");
            break;
    }

}

int Run(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "enter <input_file_name> <sort_type>";
        return 1;
    }

    string inputFileName = argv[1];
    string sortTypeString = argv[2];

    SortType sortType;
    if (sortTypeString == "shell")
    {
        sortType = SortType::Shell;
    }
    else if (sortTypeString == "merge")
    {
        sortType = SortType::Merge;
    }
    else
    {
        cout << "sort_type must be shell or merge";
        return 1;
    }

    RunSort(inputFileName, sortType);

    return 0;
}