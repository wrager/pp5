#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "AbstractSorter.h"
#include "LinearMergeSorter.h"
#include "LinearShellSorter.h"
#include "ParallelMergeSorter.h"
#include "ParallelShellSorter.h"

template<class T>
struct SortRunnerResult
{
    clock_t time;
    std::vector<T> vector;
};

template<class T>
class SortRunner
{
public:
    static void Sort(std::ifstream &input)
    {
        auto source = GetVector(input);
        SortRunnerResult<T> result;

        LinearShellSorter<int> linearShell;
        result = Sort(linearShell, source);
        std::ofstream linearShellOutput("linear_shell.txt");
        PutVector(result.vector, linearShellOutput);
        std::cout << "Linear Shell time: " << result.time << std::endl;

        ParallelShellSorter<int> parallelShell;
        result = Sort(parallelShell, source);
        std::ofstream parallelShellOutput("parallel_shell.txt");
        PutVector(result.vector, parallelShellOutput);
        std::cout << "Parallel Shell time: " << result.time << std::endl;
    }

private:
    static SortRunnerResult<T> Sort(AbstractSorter<T> &sorter, const std::vector<T> &source)
    {
        SortRunnerResult<T> result;
        sorter.SetVector(source);
        result.time = clock();
        sorter.Sort();
        result.vector = sorter.GetVector();
        result.time = clock() - result.time;

        return result;
    }

    static std::vector<T> GetVector(std::istream &stream)
    {
        std::vector<T> result;
        int number;
        while (stream >> number)
        {
            result.push_back(number);
        }

        return result;
    }

    static void PutVector(const std::vector<T> &vect, std::ostream &stream)
    {
        for (const auto &item : vect)
        {
            stream << item << " ";
        }
    }
};