// pp2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SortTestClass.h"
#include "AbstractSortWriter.h"
#include "LinearMergeWriter.h"
#include "LinearShellWriter.h"
#include "ParallelMergeWriter.h"
#include "ParallelShellWriter.h"
#include "SortRunner.h"

using namespace std;

enum class SortType { Shell, Merge };

void RunSort(string inputFileName, SortType sortType);
int Run(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    SortTest();

    //return Run(argc, argv);
}

void RunSort(string inputFileName, SortType sortType)
{
    ifstream file(inputFileName);
    SortRunner<int> runner(file);

    unique_ptr<AbstractSortWriter<int>> sortWriterPtr;
    switch (sortType)
    {
        case SortType::Shell:
            sortWriterPtr.reset(new LinearShellWriter<int>());
            runner.SetWriter(sortWriterPtr.get());
            runner.Run();
            sortWriterPtr.reset(new ParallelShellWriter<int>());
            runner.SetWriter(sortWriterPtr.get());
            runner.Run();
            break;
        case SortType::Merge:
            sortWriterPtr.reset(new LinearMergerWriter<int>());
            runner.SetWriter(sortWriterPtr.get());
            runner.Run();
            sortWriterPtr.reset(new ParallelMergeWriter<int>());
            runner.SetWriter(sortWriterPtr.get());
            runner.Run();
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